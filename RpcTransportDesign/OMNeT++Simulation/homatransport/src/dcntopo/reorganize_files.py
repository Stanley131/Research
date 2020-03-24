"""
Reogranize files to make data analysis easier
Usage: python reorganize_files.py <exp_type>
Execute this file from dcntopo folder
<exp_type> : 1/2/3/4/5

Author: Kunal Mahajan
mkunal@cs.columbia.edu
"""

import os
import sys

RESULTS_FOLDER = "results/"

def create_file_list(workload):
	new_directory = 'plot_' + workload
	os.system('mkdir ' + new_directory)
	folder = RESULTS_FOLDER + workload + '/'
	os.system('find ./' + folder + ' -name "*.sca" -type f -exec cp {} ./' + new_directory + ' \;')
	with open(new_directory + '/fileList.txt', 'w') as fd:
		for _,_,filenames in os.walk(new_directory):
			for file in filenames:
				if '.sca' in file:
					fd.write(file[:-4].split('15-')[1] + '/' + file)
					fd.write('\n')
	return new_directory

def create_directory_structure(plot_folder):
	for _,_,filenames in os.walk(plot_folder):
		for file in filenames:
			if '.sca' in file:
				dir = file[:-4].split('15-')[1]
				os.system('mkdir ' + plot_folder + '/' + dir)
				os.system('mv ' + plot_folder + '/' + file + ' ' + plot_folder + '/' + dir)
		break

def main():
	if len(sys.argv) != 2:
		print "USAGE: python reorganize_files.py <exp_type>"
		print "<exp_type>: 1/2/3/4/5"
	workload_num = int(sys.argv[1])

	workloads = {
			1:'WorkloadKeyValue',
			2:'WorkloadGoogleSearchRpc',
			3:'WorkloadGoogleAllRpc',
			4:'WorkloadHadoop',
			5:'WorkloadDCTCP'
		    }
	plot_folder = create_file_list(workloads[workload_num])
	create_directory_structure(plot_folder)

if __name__ == '__main__':
	main()
