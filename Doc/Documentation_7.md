Running location: 

~/Research/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo

../homatransport -u Cmdenv -c WorkloadHadoop --r_alpha=2 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs.ini 




~/Research/Research/RpcTransportDesign/OMNeT++Simulation/analysis


 ../homatransport -u Cmdenv -c WorkloadHadoop --r_alpha=2 --r_mode=blind -r 1 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs.ini 
 
 
 
 WorkloadKeyValue  
 WorkloadFabricatedHeavyHead  
 WorkloadGoogleSearchRpc 
 WorkloadFabricatedHeavyMiddle  
 WorkloadGoogleAllRpc  
 WorkloadWebServer  
 WorkloadHadoop  
 WorkloadCacheFollower  
 WorkloadDCTCP  

### Simulation logging Alpha = 2

nohup ../homatransport -u Cmdenv -c WorkloadFabricatedHeavyMiddle  --r_alpha=2 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs.ini &


nohup ../homatransport -u Cmdenv -c WorkloadHadoop  --r_alpha=2 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs_aware.ini &


nohup ../homatransport -u Cmdenv -c WorkloadGoogleAllRpc  --r_alpha=2 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_homa.ini &

nohup ../homatransport -u Cmdenv -c WorkloadFabricatedHeavyHead  --r_alpha=2 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs_blind.ini &


nohup ../homatransport -u Cmdenv -c WorkloadDCTCP  --r_alpha=2 --r_mode=blind -r 6 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig_pbs_blind.ini &











