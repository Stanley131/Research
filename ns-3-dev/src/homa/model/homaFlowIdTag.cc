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
#include "homaFlowIdTag.h"

using namespace ns3; 

namespace ns3 {
    NS_OBJECT_ENSURE_REGISTERED (homaFlowIdTag);
    TypeId homaFlowIdTag::GetTypeId (void)
    {
   		static TypeId tid = TypeId ("ns3::homaFlowIdTag")
     			.SetParent<Tag> ()
     			.AddConstructor<homaFlowIdTag> ()
     			.AddAttribute ("FlowId",
                    		"A FlowId value",
                    		EmptyAttributeValue (),
                    		MakeUintegerAccessor (&homaFlowIdTag::GetFlowId),
                      		MakeUintegerChecker<uint32_t> ())
                ;
  	 	return tid;
    }

    TypeId homaFlowIdTag::GetInstanceTypeId (void) const
    {
        return GetTypeId ();
    }

    void homaFlowIdTag::Print (std::ostream &os) const
    {
        os << "m_FlowId=" << (uint32_t)m_FlowId;
    }


    void homaFlowIdTag::Serialize (TagBuffer i) const
    {
        i.WriteU8 (m_FlowId);
    }


    void homaFlowIdTag::Deserialize (TagBuffer i)
    {
        m_FlowId = i.ReadU8();
    }

    uint32_t homaFlowIdTag::GetSerializedSize (void) const
    {
        return 1;
    }

    void homaFlowIdTag::SetFlowId (uint32_t value)
    {
        m_FlowId = value;
    }

    uint32_t homaFlowIdTag::GetFlowId (void) const
    {
        return m_FlowId;
    }
}
