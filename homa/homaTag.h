#ifndef HOMATAG_H
#define HOMATAG_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ns3/nstime.h"
#include "ns3/queue-disc.h"
#include "ns3/packet-filter.h"

#include "ns3/tag.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"

namespace ns3 {

    class homaMetadata : : public Tag 
    {
        public:
           static TypeId GetTypeId (void);
           virtual TypeId GetInstanceTypeId (void) const;
           virtual uint32_t GetSerializedSize (void) const;
           virtual void Serialize (TagBuffer i) const;
           virtual void Deserialize (TagBuffer i);
           virtual void Print (std::ostream &os) const;
            
           // these are our accessors to our tag structure
           void SetPrio (uint8_t value);
           uint8_t GePrio (void) const;
           
           void SetGrant (uint8_t value);
           uint8_t GetGrant (void) const;

           void SetFlowId (uint8_t value);
           uint8_t GetFlowId (void) const;
        private:
            uint16_t m_prio;    
            uint16_t m_grant;
            uint32_t m_FlowId; 
    };
    
}

#endif
