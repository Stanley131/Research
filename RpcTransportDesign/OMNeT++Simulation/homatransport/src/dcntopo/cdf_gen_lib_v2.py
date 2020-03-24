from dataclasses import dataclass
import os
import re
import numpy as np
import pandas as pd
import shutil
import gzip
from tqdm.auto import tqdm

@dataclass
class Packet:
    fid: int
    age_of_flow: float
    bytes_sent: int
    bytes_remaining: int
    prio: float

@dataclass
class Flow:
    flow_size: int
    flow_completion_time: float

@dataclass
class ExpermentParamaters:
    workload: int
    load: int
    flow_file: str
    packet_file: str
    is_pfabric: bool = False
    is_aware: bool = False
    is_equal: bool = False
    is_dsalt: bool = False
    alpha: float = None
    is_homa: bool = False

def _getExpermentParamatersFromDsaltOnPfabric(root_dir: str) -> ExpermentParamaters:
    experiment_dir = _getExperimentDir(root_dir)
    re_is_pbs_matcher = re.compile(r"^w(\d)_pfabric(\w*)_a([\d.eE+-]+)_(\d\d)")
    experimentInfoMatchers = re_is_pbs_matcher.match(experiment_dir)
    return ExpermentParamaters(
        workload = int(experimentInfoMatchers.group(1)),
        load = int(experimentInfoMatchers.group(4)),
        flow_file = os.path.join(root_dir, 'flow.tr.gz'),
        packet_file = os.path.join(root_dir, 'logFile.tr.gz'),
        is_pfabric = True,
        is_dsalt = True,
        is_aware = 'aware' in experiment_dir,
        alpha = float(experimentInfoMatchers.group(3))
    )
    
def _getExpermentParamatersFromPfabric(root_dir: str) -> ExpermentParamaters:
    experiment_dir = _getExperimentDir(root_dir)
    if 'equal' in experiment_dir :
        return _getExpermentParamatersEqualPrioOnPfabric(root_dir)
    else :
        re_experimentInfoMatcher = re.compile(r"^w(\d)_pfabric(\w*)_(\d\d)")
        experimentInfoMatchers = re_experimentInfoMatcher.match(experiment_dir)

        return ExpermentParamaters(
            workload = int(experimentInfoMatchers.group(1)),
            load = int(experimentInfoMatchers.group(3)),
            flow_file = os.path.join(root_dir, 'flow.tr.gz'),
            packet_file = os.path.join(root_dir, 'logFile.tr.gz'),
            is_pfabric = True,
            is_aware = 'aware' in experiment_dir
        )

def _getExpermentParamatersEqualPrioOnPfabric(root_dir: str) -> ExpermentParamaters:
    experiment_dir = _getExperimentDir(root_dir)
    re_experimentInfoMatcher = re.compile(r"^w(\d)_pfabric(\w*)_(\d\d)")
    experimentInfoMatchers = re_experimentInfoMatcher.match(experiment_dir)

    return ExpermentParamaters(
        workload = int(experimentInfoMatchers.group(1)),
        load = int(experimentInfoMatchers.group(3)),
        flow_file = os.path.join(root_dir, 'flow.tr.gz'),
        packet_file = os.path.join(root_dir, 'logFile.tr.gz'),
        is_pfabric = True,
        is_equal = True
    )

def _getExperimentDir(root_dir: str) -> str :
    return root_dir.split('/')[-1]

def getExperimentParamaters(root_dir: str, quiet: bool = False) -> ExpermentParamaters:
    experiment_dir = _getExperimentDir(root_dir)
    re_isPfabricExperiment = re.compile(r"^w(\d)_pfabric_")

    pfabric_matched = re_isPfabricExperiment.match(experiment_dir)
    if pfabric_matched == None :
        if quiet :
            return None
        raise Exception(f'"{experiment_dir}" is not an experiment')
    if 'pbs' in experiment_dir :
        return _getExpermentParamatersFromDsaltOnPfabric(root_dir)
    else :
        return _getExpermentParamatersFromPfabric(root_dir)

def _get_workload_int(workload_str_caps):
    workloadToType = { 
        'FACEBOOK_KEY_VALUE':1, 
        'GOOGLE_SEARCH_RPC':2, 
        'GOOGLE_ALL_RPC':3, 
        'FACEBOOK_HADOOP_ALL':4, 
        'DCTCP':5 
        }
    
    return workloadToType[workload_str_caps]

def _getExpermentParamatersHomaOnly(root_dir):
    experiment_dir = _getExperimentDir(root_dir)
    re_isHomaExperiment = re.compile(r"^(blind|aware|homa)_([A-Z_]+)_([\d.eE+-]+)")
    homa_matched = re_isHomaExperiment.match(experiment_dir)
    
    workload_str = homa_matched.group(2)
    alpha = float(homa_matched.group(3))

    return ExpermentParamaters(
        workload = int(_get_workload_int(workload_str)),
        load = 80,
        flow_file = os.path.join(root_dir),
        packet_file = None,
        is_homa= True,
        is_aware= True
    )

def _getExpermentParamatersFromDsaltOnHoma(root_dir):
    experiment_dir = _getExperimentDir(root_dir)
    re_isHomaExperiment = re.compile(r"^(blind|aware|homa)_([A-Z_]+)_([\d.eE+-]+)")
    homa_matched = re_isHomaExperiment.match(experiment_dir)
    
    aware = homa_matched.group(1)
    if aware == 'aware' :
        aware = True
    else:
        aware = False
    workload_str = homa_matched.group(2)
    alpha = float(homa_matched.group(3))

    return ExpermentParamaters(
        workload = int(_get_workload_int(workload_str)),
        flow_file = os.path.join(root_dir),
        load = 80,
        packet_file = None,
        is_homa= True,
        is_dsalt= True,
        is_aware= aware,
        alpha= alpha
    )

def getHomaExperimentParamaters(root_dir: str, quiet: bool = False) -> ExpermentParamaters:
    experiment_dir = _getExperimentDir(root_dir)
    re_isHomaExperiment = re.compile(r"^(blind|aware|homa)_([A-Z_]+)_([\d.eE+-]+)")
    homa_matched = re_isHomaExperiment.match(experiment_dir)

    if homa_matched == None :
        if quiet :
            return None
        raise Exception(f'"{experiment_dir}" is not an experiment')
    if 'homa' == homa_matched.group(1) :
        return _getExpermentParamatersHomaOnly(root_dir)
    else :
        return _getExpermentParamatersFromDsaltOnHoma(root_dir)


def cleanPacketFile(exp: ExpermentParamaters) -> None:  
    # open the unzipped file with flie handler inp_f
    with gzip.open(exp.packet_file,"rb") as inp_f:
        last_warmup_line = 0
        for i, line in enumerate(tqdm(inp_f)):
            line_str = line.decode("utf-8")  
            if 'warm-up' in line_str :
                last_warmup_line = i + 100   

    with gzip.open(exp.packet_file,"rb") as inp_f:
        # open the output zipped file with file handler out_f
        with gzip.open("tmp.txt.gz","wb") as out_f:
            for i, line in enumerate(tqdm(inp_f)): 
                if i < last_warmup_line :
                    continue
                line_str = line.decode("utf-8")  
                if 'HISTO' in line_str and i == 0:
                    return
                if i % 10000 == 0:
                    out_f.flush()
                if 'HISTO' in line_str and len(line_str.split()) == 6:
                    if exp.workload == 5 and np.random.binomial(1, 0.005, 1)[0] == 0:
                        # skip 499 out of 500
                        continue
                    out_f.write(line)
 
    shutil.move("tmp.txt.gz",exp.packet_file)

class Experiment:
    def __init__(self, params: ExpermentParamaters, lazy_loading: bool = True, keep_data: bool = True):
        self.params = params
        self.lazy_loading = lazy_loading
        self.keep_data = lazy_loading or keep_data
        self._flows_df = None
        self._packets_df = None
        
        if not self.lazy_loading :
            self.get_flows_df()
            self.get_packets_df()
    
    # a function that returns the packet data of an experment, 
    # data is returned in a pandas data frame, 
    # w/ cols=['flow_id', 'age', 'bytes_sent', 'bytes_remaining', 'prio']
    @property
    def packets_df(self):
        if self._packets_df is None :
            print('loading packet file')
            cleanPacketFile(self.params)
            packets = pd.read_csv(self.params.packet_file, sep='\t', header=None, names=['histo', 'flow_id', 'age', 'bytes_sent', 'bytes_remaining', 'prio'], usecols=['flow_id', 'age', 'bytes_sent', 'bytes_remaining', 'prio'])
            if self.keep_data :
                self._packets_df = packets
            
            return packets
        else : 
            return self._packets_df

    # a function that returns the flows data of an experment, 
    # data is returned in a pandas data frame, 
    # w/ cols=['flow_size','flow_completion_time']
    @property
    def flows_df(self):
        if self._flows_df is None :
            flows = pd.read_csv(self.params.flow_file, sep=' ', header=None, names=['flow_size','flow_completion_time','num_rtt','group_id_1','group_id_2'])
            flows = flows.dropna()
            flows = flows[['flow_size', 'flow_completion_time']]
            if self.keep_data :
                self._flows_df = flows
            
            return flows
        else : 
            return self._flows_df



        




        


    
