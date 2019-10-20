/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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

/*
class homaPrioTag : public Tag 
{
        public:
            static TypeId GetTypeId (void);
            virtual TypeId GetInstanceTypeId (void) const;
            virtual uint32_t GetSerializedSize (void) const;
            virtual void Serialize (TagBuffer i) const;
            virtual void Deserialize (TagBuffer i);
            virtual void Print (std::ostream &os) const;
            
            // these are our accessors to our tag structure
            void SetPrio (uint16_t value);
            uint16_t GetPrio (void) const;
           
        private:
            uint16_t m_prio;    
};
*/

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


class homaFlowIdTag : public Tag 
{
        public:
            static TypeId GetTypeId (void);
            virtual TypeId GetInstanceTypeId (void) const;
            virtual uint32_t GetSerializedSize (void) const;
            virtual void Serialize (TagBuffer i) const;
            virtual void Deserialize (TagBuffer i);
            virtual void Print (std::ostream &os) const;
            
            // these are our accessors to our tag structure
            void SetFlowId (uint32_t value);
            uint32_t GetFlowId (void) const;
        
        private:
            uint32_t m_FlowId; 
};


int
main (int argc, char *argv[])
{

  homaPrioTag prio_tag;
  homaGrantTag grant_tag;
  homaFlowIdTag flowId_tag;

  //Add some simple date for testing
  prio_tag.SetPrio(1);
  grant_tag.SetGrant(2);
  flowId_tag.SetFlowId(3);

  
  std::cout<< "==========Client Sent Data==========\n"
    <<"Prio: "<< prio_tag.GetPrio()<< "   "
    <<"Grant: "<< grant_tag.GetGrant()<< "   "
    <<"FlowId: "<< flowId_tag.GetFlowId()<< "   "<<"\n";
  
  
  //Create a packet
  Ptr<Packet> pkt_send = Create<Packet> ();
  pkt_send -> AddPacketTag(prio_tag);
  pkt_send -> AddPacketTag(grant_tag);
  pkt_send -> AddPacketTag(flowId_tag);

  //Create a copy of the packet
  Ptr<Packet> p_copy = pkt_send->Copy ();
  
  //Read the tag
  homaPrioTag tagCopy1;
  homaGrantTag tagCopy2;
  homaFlowIdTag tagCopy3;
  
  p_copy->PeekPacketTag (tagCopy1);
  p_copy->PeekPacketTag (tagCopy2);
  p_copy->PeekPacketTag (tagCopy3);
  
  //std::cout<< "==========Middle==========\n";

  std::cout<< "==========Copy Received Data==========\n"
    <<"prio: "<< tagCopy1.GetPrio()<< "  "
    <<"grant: "<< tagCopy2.GetGrant()<< "  "
    <<"flowId: "<< tagCopy3.GetFlowId()<< "  \n";

  return 0;
}

/*

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
  */  

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
    



