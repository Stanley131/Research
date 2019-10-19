#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ns3/string.h"
#include "ns3/simulator.h"
#include "ns3/queue-disc.h"
#include "homaTag.h"

namespace ns3 {

	NS_OBJECT_ENSURE_REGISTERED (homaTag);
    
    TypeId homaTag::GetTypeId (void)
	{
   		static TypeId tid = TypeId ("ns3::homaTag")
     			.SetParent<Tag> ()
     			.AddConstructor<homaTag> ()
     			.AddAttribute ("prio",
                    		"A priority value",
                    		EmptyAttributeValue (),
                    		MakeUintegerAccessor (&homaTag::GetPrio),
                    		MakeUintegerChecker<uint8_t> ())
     			.AddAttribute ("grant",
                    		"A Grant value",
                    		EmptyAttributeValue (),
                    		MakeUintegerAccessor (&homaTag::GetGrant),
                    		MakeUintegerChecker<uint16_t> ())
     			.AddAttribute ("flowId",
                    		"A FlowId value",
                    		EmptyAttributeValue (),
                    		MakeUintegerAccessor (&homaTag::GetFlowId),
                    		MakeUintegerChecker<uint32_t> ());
  	 	return tid;
 	}

    TypeId homaTag::GetInstanceTypeId (void) const
    {
        return GetTypeId ();
    }

    void homaTag::Print (std::ostream &os) const
    {
        os << "m_prio=" << (uint32_t)m_prio<< "  m_grant="<<(u_int32_t)m_grant
        << " m_FlowId="<< (u_int32_t)m_FlowId;
    }


    void homaTag::Serialize (TagBuffer i) const
    {
        i.WriteU8 (m_prio);
        i.WriteU8 (m_grant);
        i.WriteU8 (m_FlowId);
    }


    void homaTag::Deserialize (TagBuffer i)
    {
        m_prio = i.ReadU8();
        m_grant = i.ReadU8();
        m_FlowId = i.ReadU8();
    }

    uint32_t homaTag::GetSerializedSize (void) const
    {
        return 1;
    }

    void homaTag::SetPrio (uint8_t value)
    {
        m_prio = value;
    }

    void homaTag::SetGrant (uint16_t value)
    {
        m_grant = value;
    }

    void homaTag::SetFlowId (uint32_t value)
    {
        m_FlowId = value;
    }

    uint8_t homaTag::GetPrio (void) const
    {
        return m_prio;
    }

    uint16_t homaTag::GetGrant (void) const
    {
        return m_grant;
    }


    uint32_t homaTag::GetFlowId (void) const
    {
        return m_FlowId;
    }

} //namespace ns3 
