# Guide
  -1. Setup 
  - 2. Simuation Instructions  
  - 3. Plotting Instructions

## 1. Setup
### 1. Source
  - Download [omnet++ version 4.6](https://omnetpp.org/download/old.html)
  - Download [Homa Source](https://github.com/PlatformLab/HomaSimulation/tree/omnet_simulations/RpcTransportDesign/OMNeT%2B%2BSimulation)
### 2. Compile omnettpp-4.6 
  - 1. Get into the omnettpp-4.6 directory
      - cd omnetpp-4.6 
  - 2. set enviroment
      -  .setenv
  - 3. open ~/.bash_profile and add the following line 
      - export PATH=$PATH:$HOME/omnetpp-4.6/bin 
  - 4. use .bash_profile 
      - source ~/.bash_profile
  - 5. Run the configuriation 
      -  NO_TCL=1 ./configure
  - 6. compile omnettpp-4.6
      - make MODE=release
  - 7. Copy the diff patch below into a file (eg. patch.diff) and apply
      it to OMNeT++ directory and rebuild OMNeT++ from the directory
      (.../omnetpp-4.6$ patch -p1 < patch.diff). 
  - 8. Since the source code is changed, the code needs to be 
      recompiled. So, repeat step 5 and 6. 
### 2. Compile INET
  - 1. change to init directory. 
      - cd inet 
  - 2. Generate makefiles
      - make makefiles 
  - 3. Build the release version. 
      - make MODE=release 
  - (Note:If you get the error: "In file included from 
    inet/common/serializer/sctp/SCTPSerializer.cc:28:0: 
    ./inet/common/serializer/sctp/headers/sctphdr.h:415:22: 
    error: flexible array member in union uint8_t info[];", 
    you have just to modify the code in the sctphdr.h and make it:
    #uint8_t info [128];#
    More details here: [stack overflow](https://stackoverflow.com/questions/37969272/error-compiling-inet-framework-for-omnet:)) 
      
