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
#include "homaTag.h"
#include <iostream>
#include <string>

using namespace ns3;

int
main (int argc, char *argv[])
{

  
  //Create a packet
  Ptr<Packet> pkt_send = Create<Packet> (reinterpret_cast<const uint8_t*> ("Today is not ncie"), 100);

  homaTag h_tag;

  //Add some simple date for testing
  h_tag.SetPrio(1);
  h_tag.SetGrant(2);
  h_tag.SetFlowId(3);

  
  std::cout<< "==========Client Sent Data==========\n"
    <<"Prio: "<< h_tag.GetPrio()<< "   "
    <<"Grant: "<< h_tag.GetGrant()<< "   "
    <<"FlowId: "<< h_tag.GetFlowId()<< "   "<<"\n";
  

  //Add h_tag to a packet
  pkt_send -> AddPacketTag(h_tag);

  //Create a copy of the packet
  Ptr<Packet> p_copy = pkt_send->Copy ();

  //Read the tag
  homaTag tagCopy;
  p_copy->PeekPacketTag (tagCopy);

  std::cout<< "==========Copy Sent Data==========\n"
    <<"Prio: "<< tagCopy.GetPrio()<< "   "
    <<"Grant: "<< tagCopy.GetGrant()<< "   "
    <<"FlowId: "<< tagCopy.GetFlowId()<< "   "<<"\n";

  return 0;
}
