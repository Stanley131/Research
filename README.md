# Guide
  - 1. Setup 
  - 2. Simuation Instructions  
  - 3. Plotting Instructions

## 1. Setup
### 1. Source
  - Download [omnet++ version 4.6](https://omnetpp.org/download/old.html)
  - Download [Homa Source](https://github.com/PlatformLab/HomaSimulation/tree/omnet_simulations/RpcTransportDesign/OMNeT%2B%2BSimulation)
  - Implement PBS based on above two sources. 

### 2. Compile omnettpp-4.6 
1. Get into the omnettpp-4.6 directory
  
    ``cd omnetpp-4.6`` 

2. set enviroment
    
    ``.setenv``

3. open ``~/.bash_profile`` and add the following line 

    ``export PATH=$PATH:$HOME/omnetpp-4.6/bin`` 

4. use ``.bash_profile``
    
    ``source ~/.bash_profile``

5. Run the configuriation 
    
    ``NO_TCL=1 ./configure``

6. compile omnettpp-4.6

    ``make MODE=release``

7. Copy the diff patch below into a file (eg. patch.diff) and apply
    it to OMNeT++ directory and rebuild OMNeT++ from the directory
    (.../omnetpp-4.6$ patch -p1 < patch.diff). 
8. Since the source code is changed, the code needs to be 
    recompiled. So, repeat step 5 and 6. 

### 3. Compile INET
1. change to init directory. 
  
  ``cd inet`` 

2. Generate makefiles

  ``make makefiles`` 

3. Build the release version. 
  
  ``make MODE=release`` 

(Note:If you get the error: "In file included from 
inet/common/serializer/sctp/SCTPSerializer.cc:28:0: 
./inet/common/serializer/sctp/headers/sctphdr.h:415:22: 
error: flexible array member in union uint8_t info[];", 
you have just to modify the code in the sctphdr.h and make it:  

  ``*uint8_t info [128];*``
  More details here: [stack overflow](https://stackoverflow.com/questions/37969272/error-compiling-inet-framework-for-omnet:)) 

4. (Optional) Run some specific examples by changing into 
the example's directory and executing ``./run``

### 4. Compile INET  
1. Change to homatranport directoty. (Note: Default home directory should Research 
  becuase some problem require the path name to Start with Research. So, if you 
  copy from the repository, you can move the Research folder within home directory.) 
  
   ``~/Research/RpcTransportDesign/OMNeT++Simulation/homatransport``

2. Generate makefiles.
    
    ``make makefiles`` 

3. Build the release version, and the executablle name is homatransport under
    ``~/Research/RpcTransportDesign/OMNeT++Simulation/homatransport/src``
  
    ``make MODE=release``

- 4. Run some examples. Get into dcntop folder and run the following command:  
  
  ``../homatransport -u Cmdenv -c WorkloadHadoop --r_alpha=100 --r_mode=homa -r 15 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET homaTransportConfig.ini``

- 5. Notes: 
  
  - homatransport: executable name 
  - -u Cmdenv: using command line argument 
  - -c WorkloadHadoop: workload type which is defined in config file
  - --r_alpha=100: config PBS alpha number (Used by PBS schuding policy)
  - --r_mode=homa: transport type (homa, aware, blind (Note: aware, and blind are used by PBS))
  - -r 15: running number to specify loading factor(more details in config file)
  - -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET: 
    using inet 
  - homaTransportConfig.ini: specified config file, users can defined their own config file by following
    OMNET++ documentation. 

## 2. Simuation Instructions  

## 3. Plotting Instructions   
      
