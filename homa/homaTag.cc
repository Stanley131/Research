#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ns3/string.h"
#include "ns3/simulator.h"
#include "ns3/queue-disc.h"
#include "prioTag.h"

namespace ns3 {

	NS_OBJECT_ENSURE_REGISTERED (homaTag);

    TypeId 
    homaMetadata::GetInstanceTypeId (void) const
    {
        return GetTypeId ();
    }

    homaMetadata::Print (std::ostream &os) const
    {
        os << "m_prio=" << (uint32_t)m_prio<< "  m_grant="<<(u_int32_t)m_grant
        << " m_FlowId="<< (u_int32_t)m_FlowId;
    }


    void 
    homaMetadata::Serialize (TagBuffer i) const
    {
        i.WriteU8 (m_prio);
        i.WriteU8 (m_grant);
        i.WriteU8 (m_FlowId);
    }


    void 
    homaMetadata::Deserialize (TagBuffer i)
    {
        m_prio = i.ReadU8();
        m_grant = i.ReadU8();
        m_FlowId = i.ReadU8();
    }


    void 
    homaMetadata::SetPrio (uint8_t value)
    {
        m_prio = value;
    }

    void
    homaMetadata::SetGrant (uint8_t value)
    {
        m_grant = value;
    }

    void
    homaMetadata::SetGrant (uint8_t value)
    {
        m_FlowId = value;
    }


    int
    homaMetadata::GetPrio ()
    {
        return m_grant;
    }


    int
    homaMetadata::GetGrant ()
    {
        return m_grant;
    }


    int
    homaMetadata::GetFlowId ()
    {
        return m_FlowId;
    }

} //namespace ns3 
