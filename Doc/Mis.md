Install R 
1. Fix reshape system.time(install.packages(c("plyr","reshape2","stringr"), type = "source"))
2. Line 62 changed the 4 arguments  to 3 
msgBytesOnWire(parsedStats parsedStats.generalInfo, xmlParsedDic, msgBytesOnWireDigest)

def msgBytesOnWire(parsedStats, xmlParsedDic, msgBytesOnWireDigest):


../homatransport -u Cmdenv -c WorkloadHadoop -r 1 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig.ini


python PlotDigester.py --plotType StretchVsUnsched --resultDir /users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1


/users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/changeUnschedBytes/ver2 



--outputFile 

/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1


/users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1

~/Research/RpcTransportDesign/OMNeT++Simulation/analysis


tail nohup.out

nohup ../homatransport -u Cmdenv -c WorkloadHadoop -r 1 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig.ini &



python analysis/MetricsDashBoard.py homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1/WorkloadHadoop-1.sca



python PlotDigester.py --plotType StretchVsUnsched --resultDir /users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1/test_dir/


scp -p22 mkunal@hp033.utah.cloudlab.us:/users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/plots/PBS_Graph/TailStretchVsUnschedBytes_rho0.2.pdf .





scp -p22 mkunal@hp177.utah.cloudlab.us:/users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/stretchVsUnsched.txt 



~/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1


python PlotDigester.py --plotType StretchVsUnsched --resultDir /users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1



~/Research/RpcTransportDesign/OMNeT++Simulation/analysis/PlotScripts/plots/changeUnschedBytes


In pbs plot: 

Line 112: 
<>  plot.title = element_text(hjust = 0.5),

110 > hjust = 0.5


1. Number of samples 
   2. StretchVsTransport.r   multiple lines 
3. Prio
    1. 0, 
    2. LINE 2460 
    3. HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/homaTransportConfig.ini
		CONFIG TIME 
  4. HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/transport/HomaTransport.cc
	  change prio to 0 

~/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src 

Push popd


### 1. Change Homa Cogfig time to 500ms 
File changed: 
. HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/homaTransportConfig.ini


### 2. Modify grant to be 0 in homa algo 
File changed: 
. HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/transport/HomaTransport.cc
At line: 2469 
  Comment out:   return grantPrio;
  Add new line:  return 0; 
  
### 3. Recompile transport 
  Follow the instructions: 
  https://github.com/kvm2116/homa_replicate
  

### 4. Run different configTypes of homa
 ../homatransport -u Cmdenv -c "configTypes"  -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig.ini
 
"configTypes" is lcoated in 
~/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/homaTransportConfig.ini


### Currently running 3 configs 
  WorkloadKeyValue
  WorkloadGoogleSearchRpc
  WorkloadHadoop



    sp = ScalarParser(scalarResultFile)
    parsedStats = AttrDict()
    parsedStats.hosts = sp.hosts
    parsedStats.tors = sp.tors
    parsedStats.aggrs = sp.aggrs
    parsedStats.cores = sp.cores
    parsedStats.generalInfo = sp.generalInfo
    parsedStats.globalListener = sp.globalListener


StretchVsPrioCutoff
StretchVsUnschedPrioMode

StretchVsTransport StretchVsUnsched
StretchVsSize



python PlotDigester.py --plotType StretchVsPrioCutoff  --resultDir /users/mkunal/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/results/manyReceivers/comparison/linkCheckBytes__-1  --outputFile  StretchVsUnschedPrioMode.txt



1. Grant
2. Loadfactor 
3. ggplot  

Bytes remaining + 

Age of flow: acurrent _packet - rrive_time  ; 


