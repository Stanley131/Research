### 1. Change Homa Cogfig time to 1000ms 
File changed: 
. HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/homaTransportConfig.ini


### 2. Modify grant to be 0 in homa algo 
File changed: 
. HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/transport/HomaTransport.cc
At line: 2469 
  Comment out:   return grantPrio;
  Add new line:  return 0; 
  
### 2. Recompile transport 

