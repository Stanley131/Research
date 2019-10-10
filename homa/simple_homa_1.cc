/*
 *
 *
 *
 */


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/tag.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include <iostream>

using namespace ns3; 

NS_LOG_COMPONENT_DEFINE("SimpleHomaImplementation"); 


int get_homa_priority(unsigned int){
    //Calculate homa priority 
    return 0; 
}



class homaMetadata : : public Tag 
{
publicc:
   static TypeId GetTypeId (void);
   virtual TypeId GetInstanceTypeId (void) const;
   virtual uint32_t GetSerializedSize (void) const;
   virtual void Serialize (TagBuffer i) const;
   virtual void Deserialize (TagBuffer i);
   virtual void Print (std::ostream &os) const;
    
   // these are our accessors to our tag structure
   void SetSimpleValue (uint8_t value);
   uint8_t GetSimpleValue (void) const;

private:
    uint16_t m_prio;
    uint16_t m_grant;
};

TypeId 
homaMetadata::GetTypeId (void)
{
    static TypeId tid = TypeId ("ns3::homaMetadata")
            .SetParent<Tag> ()
            .AddConstructor<homaMetadata> ()
            .AddAttribute ("Priority",
                           "Homa Priority",
                           EmptyAttributeValue (),
                           MakeUintegerAccessor (&homaMetadata::GetPrio),
                           MakeUintegerChecker<uint8_t> ());
            .AddAttribute ("Grant",
                           "Homa Grant",
                           EmptyAttributeValue (),
                           MakeUintegerAccessor (&homaMetadata::GetGrant),
                           MakeUintegerChecker<uint8_t> ());
    return tid;
}
                    
TypeId 
homaMetadata::GetInstanceTypeId (void) const
{
    return GetTypeId ();
}

homaMetadata::Print (std::ostream &os) const
{
    os << "m_prio=" << (uint32_t)m_prio<< "  m_grant="<<m_grant;
}


void 
homaMetadata::Serialize (TagBuffer i) const
{
    i.WriteU8 (m_prio);
    i.WriteU8 (m_grant);
}


void 
homaMetadata::Deserialize (TagBuffer i)
{
    m_prio = i.ReadU8();
    m_grant = i.ReadU8();
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
homaMetadata::GetPrio (uint8_t value)
{
    return m_grant;
}


void
homaMetadata::GetGrant (uint8_t value)
{
    return m_grant;
}









Ptr<Packet> create_packet(u_int32_t payload, Address source, Address destination, 
                          uint16_t source_port, uint16_t destination_port, FlowId flowId ){
    //Fill the packet information 
    Ptr<Packet> pkt = Create<Packet> (payload);
    
    //Header 
    UdpHeader udpHeader;
    udpHeader.InitializeChecksum(source, destination, 17); 
    udpHeadder.SetSourcePort(source_port); 
    udpHeadder.SetDestinationPort(destination_port); 
    udpHeadder.ForcePayloadSize(payload); 

    packet->AddHeader (udpHeader); 
    
    
    //GetSize (void) const
    //Tag

    
    //Buffer Data 

    //Metadata
    PacketMetadata m_metadata;



    
    return pkt; 
}

int read_packet(){
    //Read the packet infomation 
}


// If we are going to use gRPC, we have to use
// ns3 monitor the flow transiactions





int 
main(int argc, char *agrv[])
{
    
    Time:SetResolution (Time::NS)
    LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

    //Create two nodes 
    NodeContainer nodes; 
    nodes.Create(2);

    intToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
    pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
    

    NetDeviceContainer devices;
    devices = pointToPoint.Install (nodes);

    InternetStackHelper stack;
    stack.Install (nodes);

    //Set IP base 
    Ipv4AddressHelper address;
    address.SetBase ("10.1.1.0", "255.255.255.0");

    Ipv4InterfaceContainer interfaces = address.Assign (devices);
    

    //Use UDP for a RPC, Server
    UdpEchoServerHelper echoServer (520);
    ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
    serverApps.Start (Seconds (1.0));
    serverApps.Stop (Seconds (100.0));

    UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 520);
    echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
    echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
    //echoClient.SetAttribute ("PacketSize", UintegerValue (1024));


    //Fill up the packet information 
    

    //Read the packet information 
    


    ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
    clientApps.Start (Seconds (2.0));
    clientApps.Stop (Seconds (100.0));

    Simulator::Run ();
    Simulator::Destroy ();

    return 0; 
}
