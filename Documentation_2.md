Start Date: 11/23/2019 -- End Date:  

1. Homa Simulation 
  time limit: 1000ms 
  . WorkloadHadoop
  . WorkloadGoogleSearchRpc
  . WorkloadFabricatedHeavyHead
  . WorkloadDCTCP
  
  output files : all files with - 1 
  
2. grant = 0 
  ~/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/transport/HomaTransport.cc
  line: 2470
  Modify the grant to be 0
  
  Recompile the homa implementation
  
  time limit: 1000ms 
  . WorkloadHadoop
  . WorkloadGoogleSearchRpc
  . WorkloadFabricatedHeavyHead
  . WorkloadDCTCP
  
  output files : all files with - 2

3. run from Python (Not getting what we want)
python PlotDigester.py --plotType StretchVsPrioCutoff  --resultDir /users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1  --outputFile  StretchVsUnschedPrioMode.txt
 
Potential Script with different transpot data 
PlotStretchVsUnsched_stepPlot_pbs.r

4. Copy pdf to local machines 
scp -p22 mkunal@hp033.utah.cloudlab.us:/users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/plots/PBS_Graph/*.pdf .


