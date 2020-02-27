  ## ggplot 
  1. The output files are specified in the ini confige file.   
    - result-dir (parameter in the config file)
    - example: result-dir = results/manyReceivers/comparison/linkCheckBytes__${linkCheckBytes}

  2. Create the stretchvstransport.txt file as follows:
  
     - python PlotDigester.py --plotType StretchVsTransport --resultDir /users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/homa/rlf
  3. Generate graphs with PBS_Transport.r: 
     - example: Rscript PBS_Transport.r stretchVsUnsched.txt  
     - graphs will be in Plots directoy 
     - Note, we can change the R scipt file name in the PlotDigester.py to generate graph. And no need to run step 3. 
         
  4. command for specifying output filenames:    
     - ../homatransport -u Cmdenv --output-vector-file="WorkloadHadoop-15-homa-2.vec" --output-scalar-file="WorkloadHadoop-15-homa-2.sca" -c WorkloadHadoop  --r_alpha=2 --r_mode=homa -r 15 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_homa_rlf.ini 
     - Notes: 
         - we only need ".sca" file so far, and the vetor file can be ignored. 
         - ".sca" will be generated when the simulation ends. 
  
  
 
