import threading
import os
import queue
import cdf_gen_lib_v2
#from cdf_gen_lib_v2 import Experiment
#import graph_lib
from pathlib import Path
import logging
import pandas as pd

class Runner:
    def __init__(self, 
    workload: str, 
    aware: bool, 
    parellel = True, 
    timeout: str = '1h', 
    n_flows = 100_000, 
    min_flows = 90_000, 
    threads = None,
    log_prio = False
    ):
        self.workLoad = workload
        self.aware = aware
        self.parellel = parellel
        self.timeout = timeout
        self.n_flows = n_flows
        self.min_flows = min_flows
        self.threads = threads
        self.log_prio = log_prio


    def _getNs2Command(self, alpha):
        link_rate = 10
        mean_link_delay = 0.0000002
        host_delay = 0.000020
        queueSize = 140
        load = 0.8
        connections_per_pair = 1
        meanFlowSize = 1138*1460
        paretoShape = 1.05

        workLoadToMeanFlowSize = { 
            'WTest':524800,
            'W1':188,
            'W2':441,
            'W3':2927,
            'W4':127797,
            'W5':1744704 
        }
        workLoadFile = {
            'WTest':'WTest_CDF.tcl',
            'W1':'W1_CDF.tcl',
            'W2':'W2_CDF.tcl',
            'W3':'W3_CDF.tcl',
            'W4':'W4_CDF.tcl',
            'W5':'W5_CDF.tcl' 
        }

        enableMultiPath = 1
        perflowMP = 0

        sourceAlg = 'DCTCP-Sack'
        initWindow = 70
        ackRatio = 1
        slowstartrestart = 'true'
        DCTCP_g = 0.0625
        min_rto = 0.000250
        prob_cap_ = 5

        switchAlg = 'DropTail'
        DCTCP_K = 65.0
        drop_prio_ = 'true'
        prio_scheme_ = 0
        deque_prio_ = 'true'
        keep_order_ = 'true'
        prio_num_ = 0 # 2019-12-14 tried 0 vs 1 and it didnt matter.
        ECN_scheme_ = 2 #Per-port ECN marking
        pias_thresh_0 = 46*1460
        pias_thresh_1 = 1084*1460
        pias_thresh_2 = 1717*1460
        pias_thresh_3 = 1943*1460
        pias_thresh_4 = 1989*1460
        pias_thresh_5 = 1999*1460
        pias_thresh_6 = 2001*1460

        log_prio = self.log_prio

        topology_spt = 16
        topology_tors = 9
        topology_spines = 4
        topology_x = 1

        ns_path = '/home/sysadmin/ns-allinone-2.34/ns-2.34/ns'
        sim_script = 'spine_empirical.tcl'

        meanFlowSize = workLoadToMeanFlowSize[self.workLoad]
        flow_cdf = workLoadFile[self.workLoad]

        enable_dsalt = True
        is_omniscient = self.aware
        equal_prio = False

        protocol = 'unknown'
        if self.aware :
            protocol = 'dsalt_aware'
        else :
            protocol = 'dsalt_blind'

        scheme = 'pfabric_PBS_' + protocol.split(sep='_')[1] + f'_a{alpha}'

        #Directory name: workload_scheme_load_[load]
        directory_name = '%s_%s_%d' % (self.workLoad, scheme, int(load*100))
        directory_name = directory_name.lower()
        #Simulation command
        cmd = ns_path+' '+sim_script+' '\
            +str(self.n_flows)+' '\
            +str(link_rate)+' '\
            +str(mean_link_delay)+' '\
            +str(host_delay)+' '\
            +str(queueSize)+' '\
            +str(load)+' '\
            +str(connections_per_pair)+' '\
            +str(meanFlowSize)+' '\
            +str(paretoShape)+' '\
            +str(flow_cdf)+' '\
            +str(enableMultiPath)+' '\
            +str(perflowMP)+' '\
            +str(sourceAlg)+' '\
            +str(initWindow)+' '\
            +str(ackRatio)+' '\
            +str(slowstartrestart)+' '\
            +str(DCTCP_g)+' '\
            +str(min_rto)+' '\
            +str(prob_cap_)+' '\
            +str(switchAlg)+' '\
            +str(DCTCP_K)+' '\
            +str(drop_prio_)+' '\
            +str(prio_scheme_)+' '\
            +str(deque_prio_)+' '\
            +str(keep_order_)+' '\
            +str(prio_num_)+' '\
            +str(ECN_scheme_)+' '\
            +str(pias_thresh_0)+' '\
            +str(pias_thresh_1)+' '\
            +str(pias_thresh_2)+' '\
            +str(pias_thresh_3)+' '\
            +str(pias_thresh_4)+' '\
            +str(pias_thresh_5)+' '\
            +str(pias_thresh_6)+' '\
            +str(topology_spt)+' '\
            +str(topology_tors)+' '\
            +str(topology_spines)+' '\
            +str(topology_x)+' '\
            +str('./'+directory_name+'/flow.tr')+' '\
            +str(enable_dsalt)+' '\
            +str(alpha)+' '\
            +str(is_omniscient)+' '\
            +str(log_prio)+' '\
            +str(equal_prio)+'  >'\
            +str('./'+directory_name+'/logFile.tr')

        return [cmd, directory_name]
    def _nearEqual(self, a, b, thresh=0.001):
        return (a - b) < thresh

    def _getHomaCommand(self, alpha):
        workloadToName = { 
            'W1':'WorkloadKeyValue',
            'W2':'WorkloadGoogleSearchRpc',
            'W3':'WorkloadGoogleAllRpc',
            'W4':'WorkloadHadoop',
            'W5':'WorkloadDCTCP' 
        }
        workloadToConfigFile = { 
            'W1':'keyvalueTransportConfig.ini',
            'W2':'searchTransportConfig.ini',
            'W3':'allrpcTransportConfig.ini',
            'W4':'hadoopTransportconfig.ini',
            'W5':'dctcpTransportConfig.ini' 
        }
        workload_name = workloadToName[self.workLoad]
        config_file = workloadToConfigFile[self.workLoad]
        mode = 'aware' if self.aware else 'blind'
        scalar_file_name = 'results/optimization/' + workload_name + '-15-' + mode + '-' + str(alpha) + '.sca'
        cmd = '../homatransport -u Cmdenv ' \
            +'--output-scalar-file=' + scalar_file_name \
            +' -c ' + workload_name \
            +' --r_alpha=' + str(alpha)\
            +' --r_mode=' + mode\
            +' -r 15 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET '\
            +config_file
        directory_name = '.'
        return [cmd, directory_name]

    def run_exp(self, trial_index_to_alphas):
        number_worker_threads = self.threads
        if number_worker_threads == None :
            if self.parellel:
                number_worker_threads = len(trial_index_to_alphas)
            else :
                number_worker_threads = 1
        
        # Setup the thread processors
        q = queue.Queue()
        allow_overwrite = False
        def worker():
            while True:
                try:
                    j = q.get(block = 0)
                except queue.Empty:
                    return

                results_dir = os.path.join(os.getcwd(), 'Results')

                results_already_exist = os.path.isdir(os.path.join(results_dir, j[1]))

                if results_already_exist :
                    logging.warning('Results already exist: '+j[1])
                    if not allow_overwrite:
                        continue
                
                #Make directory to save results
                #os.system('mkdir '+j[1])
                timeout_str = 'timeout '+self.timeout+' time '
                
                # run the simulation
                os.system(timeout_str+j[0])

                # zip the file and move 
                #os.system('gzip -r9 '+j[1])
                #os.system('mv '+j[1]+' Results')
                
        for index, alpha in trial_index_to_alphas.items():
            #cmd, directory_name = self._getNs2Command(alpha)
            cmd, directory_name = self._getHomaCommand(alpha)
            q.put([cmd, directory_name])
        
        threads = []
        for i in range(number_worker_threads):
            t = threading.Thread(target = worker)
            threads.append(t)
            t.start()

        #Join all completed threads
        for t in threads:
            t.join()
        logging.info('finished experments')

        mode = 'aware' if self.aware else 'blind'
        workloadToType = { 'W1':'FACEBOOK_KEY_VALUE', 'W2':'GOOGLE_SEARCH_RPC', 'W3':'GOOGLE_ALL_RPC', 'W4':'FACEBOOK_HADOOP_ALL', 'W5':'DCTCP' }

        index_to_results = {}
        results_dir = Path('./Results')
        for index, alpha in trial_index_to_alphas.items():
            #_, directory_name = self._getNs2Command(alpha)
            _, directory_name = self._getHomaCommand(alpha)
            logging.info(f'reading from: {str(results_dir/directory_name)}')
            #exp_params = cdf_gen_lib_v2.getExperimentParamaters(str(results_dir/directory_name), quiet=True)
            #exp = Experiment(exp_params)
            #name = graph_lib.getInWorkloadCompairsonName(exp)
            #workload = exp.params.workload
            results_file_name = mode + '_' + workloadToType[self.workLoad] + '_' + str(alpha) + '.csv'
            #print('Trying to find: ' + results_file_name)
            result_files = Path('.').glob('*')
            exp_params = [cdf_gen_lib_v2.getHomaExperimentParamaters(str(exp_file), quiet = True) for exp_file in result_files]
            exp_params = list(filter(None, exp_params))
            #print(exp_params)
            aware = True
            if not ('aware' == mode):
                aware = False

            matching_exp = None
            for exp_param in exp_params:
                if exp_param.is_homa and f'W{exp_param.workload}' == self.workLoad and self._nearEqual(exp_param.alpha, alpha) and exp_param.is_aware == aware :
                    matching_exp = exp_param 


            #print("MATCHING: " + matching_exp.flow_file)
            flows = pd.read_csv(matching_exp.flow_file, sep=' ', header=None, names=['flow_size','flow_completion_time'])
            #print(flows.head())

            flows = flows.dropna()
            flows = flows[['flow_size', 'flow_completion_time']]
            mean = flows.flow_completion_time.mean()
            p50 = flows.flow_completion_time.quantile(0.5)
            p75 = flows.flow_completion_time.quantile(0.75)
            p90 = flows.flow_completion_time.quantile(0.90)
            p99 = flows.flow_completion_time.quantile(0.99)
            logging.info(f'exp({index} a{alpha}) got p99: {p99}')

            flows['slow_down'] = flows.flow_size / flows.flow_completion_time
            sd_mean = flows.slow_down.mean()
            sd_p50 = flows.slow_down.quantile(0.5)
            sd_p75 = flows.slow_down.quantile(0.75)
            sd_p90 = flows.slow_down.quantile(0.90)
            sd_p99 = flows.slow_down.quantile(0.99)

            results = {'workload': [matching_exp.workload, 0.0], 'mean': [mean, 0.0], 'median': [p50, 0.0], 'p75': [p75, 0.0], 'p90': [p90, 0.0], 'p99': [p99, 0.0],
                'sd_mean': [sd_mean, 0.0], 'sd_median': [sd_p50, 0.0], 'sd_p75': [sd_p75, 0.0], 'sd_p90': [sd_p90, 0.0], 'sd_p99': [sd_p99, 0.0]}

            index_to_results[index] = results
        
        return index_to_results
        
