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
#include "homaGrantTag.h"

using namespace ns3; 

namespace ns3 {
    NS_OBJECT_ENSURE_REGISTERED (homaGrantTag);
    TypeId homaGrantTag::GetTypeId (void)
    {
   		static TypeId tid = TypeId ("ns3::homaGrantTag")
     			.SetParent<Tag> ()
     			.AddConstructor<homaGrantTag> ()
     			.AddAttribute ("grant",
                    		"A grant value",
                    		EmptyAttributeValue (),
                    		MakeUintegerAccessor (&homaGrantTag::GetGrant),
                      		MakeUintegerChecker<uint16_t> ())
                ;
  	 	return tid;
    }

    TypeId homaGrantTag::GetInstanceTypeId (void) const
    {
        return GetTypeId ();
    }

    void homaGrantTag::Print (std::ostream &os) const
    {
        os << "m_grant=" << (uint32_t)m_grant;
    }


    void homaGrantTag::Serialize (TagBuffer i) const
    {
        i.WriteU8 (m_grant);
    }


    void homaGrantTag::Deserialize (TagBuffer i)
    {
        m_grant = i.ReadU8();
    }

    uint32_t homaGrantTag::GetSerializedSize (void) const
    {
        return 1;
    }

    void homaGrantTag::SetGrant (uint16_t value)
    {
        m_grant = value;
    }


    uint16_t homaGrantTag::GetGrant (void) const
    {
        return m_grant;
    }
}
