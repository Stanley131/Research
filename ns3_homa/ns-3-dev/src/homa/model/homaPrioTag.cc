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
#include "homaPrioTag.h"

using namespace ns3; 

namespace ns3 {
    NS_OBJECT_ENSURE_REGISTERED (homaPrioTag);
 
    TypeId homaPrioTag::GetTypeId (void)
	{
   		static TypeId tid = TypeId ("ns3::homaPrioTag")
     			.SetParent<Tag> ()
     			.AddConstructor<homaPrioTag> ()
     			.AddAttribute ("prio",
                    		"A priority value",
                    		EmptyAttributeValue (),
                    		MakeUintegerAccessor (&homaPrioTag::GetPrio),
                      		MakeUintegerChecker<uint16_t> ())
                ;
  	 	return tid;
    }

    //homaPrioTag::homaPrioTag(){}
    //homaPrioTag::~homaPrioTag(){}

    TypeId homaPrioTag::GetInstanceTypeId (void) const
    {
        return GetTypeId ();
    }

    void homaPrioTag::Print (std::ostream &os) const
    {
   	os << "m_prio=" << (uint32_t)m_prio;
    }


    void homaPrioTag::Serialize (TagBuffer i) const
    {
        i.WriteU8 (m_prio);
    }


    void homaPrioTag::Deserialize (TagBuffer i)
    {
        m_prio = i.ReadU8();
    }

    uint32_t homaPrioTag::GetSerializedSize (void) const
    {
        return 1;
    }

    void homaPrioTag::SetPrio (uint16_t value)
    {
        m_prio = value;
    }


    uint16_t homaPrioTag::GetPrio (void) const
    {
        return m_prio;
    }
    
}

