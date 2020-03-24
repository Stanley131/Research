from d_salt_runner import Runner
from ax.service.ax_client import AxClient
from ax.utils.measurement.synthetic_functions import hartmann6
from ax.plot.slice import plot_slice
from ax.plot.scatter import(
    interact_fitted,
    plot_objective_vs_constraints,
    tile_fitted,
)

from pathlib import Path
import cdf_gen_lib_v2
import os
import argparse


parser = argparse.ArgumentParser(description='Process some integers.')

parser.add_argument('-a', action='store_true', default=False,
                    dest='aware',
                    help='Optimize for aware.')
parser.add_argument('-b', action='store_true', default=False,
                    dest='blind',
                    help='Optimize for blind.')
parser.add_argument('-w', action='append', dest='worknums',
                    default=[],
                    help='Workloads as ints one at a time ex."-w 1 -w 2 ..."',
                    )


args = parser.parse_args()
print(args)

# select pramaters
workloads = [f'W{num}' for num in args.worknums]
awares= []
if args.aware:
    awares.append(True)
if args.blind:
    awares.append(False)

assert len(awares) > 0
assert len(workloads) > 0

batch_size = 4
epocs = 25

for workload in workloads:
    for aware in awares:
        if aware:
            awareness = 'aware'
        else :
            awareness = 'blind'
        
        ax_client = AxClient()
        runner = Runner(workload, aware)
        ax_client.create_experiment(
            name=f"{workload}_{awareness}_experiment",
            parameters=[
                {
                    "name": "alpha",
                    "type": "range",
                    "bounds": [0.01, 100],
                    "value_type": "float",  # Optional, defaults to inference from type of "bounds".
                    "log_scale": True,  
                }
            ],
            objective_name="p99",
            minimize=True  # Optional, defaults to False.
        )

        # pretrain on earlier results - These are commented out below, down to the "run the opti loop"
        
        #results_dir = Path('.')
        #exp_params = [ cdf_gen_lib_v2.getExperimentParamaters(os.path.join(results_dir, exp), quiet=True) for exp in os.listdir(results_dir)]
        #exp_params = list(filter(None, exp_params))
        #exp_params = list(filter(lambda exp_param: exp_param.is_dsalt and f'W{exp_param.workload}' == workload and exp_param.is_aware == aware, exp_params))

        #batch_params = {}
        #for exp_param in exp_params:
        #    parameters, trial_index = ax_client.attach_trial(parameters={"alpha": exp_param.alpha})
        #    batch_params[trial_index] = parameters.get('alpha')
        
        # run 
        #trial_index_to_results =runner.run_exp(batch_params)
        #print(trial_index_to_results)

        #for trial_index in batch_params.keys():
        #    results = trial_index_to_results[trial_index]
        #    ax_client.complete_trial(trial_index=trial_index, raw_data=results)

        # run the opti loop
        for i in range(epocs):
            batch_params = {}
            for j in range(batch_size):
                parameters, trial_index = ax_client.get_next_trial()
                batch_params[trial_index] = parameters.get('alpha')
            # run 
            trial_index_to_results =runner.run_exp(batch_params)

            for trial_index in batch_params.keys():
                results = trial_index_to_results[trial_index]
                ax_client.complete_trial(trial_index=trial_index, raw_data=results)
        
        # save the results
        opti_dir = Path('.')
        filePaht = opti_dir/f'{workload}_{awareness}_bo.json'
        ax_client.save_to_json_file(filepath=filePaht)
