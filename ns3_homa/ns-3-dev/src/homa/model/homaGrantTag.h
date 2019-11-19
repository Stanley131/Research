#ifndef HOMAGRANTTAG_H
#define HOMAGRANTTAG_H


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include <iostream>
#include <string>
#include "ns3/tag.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"

using namespace ns3;

namespace ns3{
	class homaGrantTag : public Tag 
	{
        public:
            static TypeId GetTypeId (void);
            virtual TypeId GetInstanceTypeId (void) const;
            virtual uint32_t GetSerializedSize (void) const;
            virtual void Serialize (TagBuffer i) const;
            virtual void Deserialize (TagBuffer i);
            virtual void Print (std::ostream &os) const;
            
            // these are our accessors to our tag structure
        
            void SetGrant (uint16_t value);
            uint16_t GetGrant (void) const;
        
        private:
            uint16_t m_grant;
            //uint32_t m_FlowId; 
	};
}
#endif
