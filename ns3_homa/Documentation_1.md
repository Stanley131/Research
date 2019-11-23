### 1. Change Homa Cogfig time to 1000ms 
File changed: 
. HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/dcntopo/homaTransportConfig.ini


### 2. Modify grant to be 0 in homa algo 
File changed: 
. HomaSimulation/RpcTransportDesign/OMNeT++Simulation/homatransport/src/transport/HomaTransport.cc
At line: 2469 
  Comment out:   return grantPrio;
  Add new line:  return 0; 
  
### 3. Recompile transport 


### 4. transfer my file to linux server
scp /Users/stanleyye/Downloads/omnetpp-4.6-src.tgz yy2922@34.68.42.166:/home/yy2922/
omnetpp-4.6-src.tgz

