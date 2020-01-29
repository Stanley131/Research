### Find Start time, sent bytes, and total bytes
  - Research_PBS_HOMA/OMNet++_HOMA/RpcTransportDesign/OMNeT++Simulation/homatransport/src/transport/HomaConfigDepot.h
    - class HomaConfigDepot : All other classes will get a pointer to this class and can read params from this
    - int localPort;
    - int destPort;
  - Research_PBS_HOMA/OMNet++_HOMA/RpcTransportDesign/OMNeT++Simulation/homatransport/src/transport/HomaTransport.h
    - /**  
      * A grant based, receiver driven, congection control transport protocol over  
      * UDP datagrams. For every message transmission, the sender side sends a req.  
      * pkt defining the length of the message. The reciever on the other side sends  
      * a grant every packet time for the shortest remaining outstanding message  
      * among all outstanding messages.  
      */  
    - uint64_t msgId;
    - uint32_t msgSize;
    - uint32_t bytesToSched;
    - uint32_t bytesLeft;
    - uint32_t unschedBytesLeft;
    - inet::L3Address destAddr;  //IpAddress of destination host for this outbound msg.
    - inet::L3Address srcAddr;   // IpAddress of sender host (local host).
    - simtime_t msgCreationTime;  // message start time ????? 
    
    - class ReceiveScheduler: 
      - /**  
        * Manages reception of messages that are being sent to this host through 
        * this transport. Keeps a list of all incomplete rx messages and sends  
        * grants for them based on SRPT policy. At the completion of each message,  
        * it will be handed off to the application.  
        */
    - class CompareBytesToGrant:
        - inet::L3Address srcAddr;
        - inet::L3Address destAddr;
        - uint64_t msgIdAtSender;
        - uint32_t bytesToGrant;
        -  uint32_t offset;
        - uint32_t bytesGrantedInFlight;
        - uint32_t totalBytesInFlight;
        - uint32_t bytesToReceive；
        - uint32_t msgSize;
    -  class SchedSenders： 
        - class SchedState
        
### Change Prio
  - Research_PBS_HOMA/OMNet++_HOMA/RpcTransportDesign/OMNeT++Simulation/homatransport/src/transport/HomaTransport.c   
     - HomaTransport::ReceiveScheduler::SchedSenders::getPrioForMesg(SchedState& st)
     - line:  2471
 
  
  
  
  
