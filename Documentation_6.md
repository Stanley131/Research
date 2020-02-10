- Stanley, 1/30 Thursday 

1. Set up the enviroment. Source code compiled and tested. 

### Verify Parameters
  - UNFINISHED CODE
  - Add one parameter  in SenderState class , NOOO
  
### Best place to place our algorithm 
  - HomaTransport::ReceiveScheduler::processReceivedPkt(HomaPkt* rxPkt) .  line 1262 
  - HomaTransport::ReceiveScheduler::SchedSenders::insPoint(SenderState* s)
    - inet::IPv4Address srcIp = rxPkt->getSrcAddr().toIPv4();


### Changes to HOMA FILES
  - Homatransport.h
    - line 577: uint64_t msgId;    //add mesgId property to class SchedState
    - line 580: setVar function to set all values of SchedState, including msgId. 
  - Homatransport.cc
    - add megId parameter for setVar funtion at line 1372, 1385, (2428, 2444), last two lines (I used 0, since this paramameter is never used.)
    
