#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"

#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("DataCenter2");

int main (int argc, char *argv[])
{
	bool verbose = true;

	if (verbose)
	{
		LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
		LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	}


	//node 0 to node 9
	NodeContainer nodes;
	nodes.Create(50);

	// Define the Point-To-Point Links and their Paramters
	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

	// pp3.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
	// pp3.SetChannelAttribute("Delay", StringValue("1ms"));
	NetDeviceContainer devices;

	for (int i = 1; i < 10; ++i)
	{
			devices = pointToPoint.Install(nodes.Get(i), nodes.Get(0));
	}

	for (int i = 10; i < 20; ++i)
	{
			devices = pointToPoint.Install(nodes.Get(i), nodes.Get(10));
	}
	for (int i = 20; i < 30; ++i)
	{
			devices = pointToPoint.Install(nodes.Get(i), nodes.Get(20));
	}
	for (int i = 30; i < 40; ++i)
	{
			devices = pointToPoint.Install(nodes.Get(i), nodes.Get(30));
	}
	for (int i = 40; i < 50; ++i)
	{
			devices = pointToPoint.Install(nodes.Get(i), nodes.Get(40));
	}



	InternetStackHelper stack;
	stack.Install (nodes);

	Ipv4AddressHelper address;
	address.SetBase ("10.1.1.0", "255.255.255.0");

	Ipv4InterfaceContainer interfaces = address.Assign (devices);

	UdpEchoServerHelper echoServer (9);

	ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
	serverApps.Start (Seconds (1.0));
	serverApps.Stop (Seconds (10.0));

	UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
	echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

	ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
	clientApps.Start (Seconds (2.0));
	clientApps.Stop (Seconds (10.0));

	// //Construct ptp topo  upper
	// PointToPointHelper ptp1,ptp2;
	// ptp1.SetDeviceAttribute ("DataRate", StringValue ("3Mbps"));
	// ptp1.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (500)));
	// ptp2.SetDeviceAttribute ("DataRate", StringValue ("3Mbps"));
	// ptp2.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (500)));
	//
	// NetDeviceContainer devicePtp1,devicePtp2;
	// devicePtp1=ptp1.Install (firstgroup1);
	// devicePtp2=ptp2.Install (firstgroup2);

	// NodeContainer firstgroup2,firstgroup3,firstgroup4,firstgroup5;
	// firstgroup2.Add(firstgroup1.Get(0));
	// firstgroup2.Create(2);
	// firstgroup3.Add(firstgroup1.Get(0));
	// firstgroup3.Create(2);
	// firstgroup4.Add(firstgroup1.Get(0));
	// firstgroup4.Create(2);
	// firstgroup5.Add(firstgroup1.Get(0));
	// firstgroup5.Create(2);



	// // node 10 to 19
	//
	// NodeContainer secondgroup1;
	// secondgroup1.Create(2);
	//
	// NodeContainer secondgroup2,secondgroup3,secondgroup4,secondgroup5;
	// secondgroup2.Add(secondgroup1.Get(10));
	// secondgroup2.Create(2);
	// secondgroup3.Add(secondgroup1.Get(10));
	// secondgroup3.Create(2);
	// secondgroup4.Add(secondgroup1.Get(10));
	// secondgroup4.Create(2);
	// secondgroup5.Add(secondgroup1.Get(10));
	// secondgroup5.Create(2);

	//
	// // node 20 to 29
	//
	// NodeContainer thirdgroup1;
	// thirdgroup1.Create(2);
	//
	// NodeContainer thirdgroup2,thirdgroup3,thirdgroup4,thirdgroup5;
	// thirdgroup2.Add(thirdgroup1.Get(10));
	// thirdgroup2.Create(2);
	// thirdgroup3.Add(thirdgroup1.Get(10));
	// thirdgroup3.Create(2);
	// thirdgroup4.Add(thirdgroup1.Get(10));
	// thirdgroup4.Create(2);
	// thirdgroup5.Add(thirdgroup1.Get(10));
	// thirdgroup5.Create(2);



	//
	// //Construct the lower Network:csmaNodes
	// NodeContainer csmaNodes1,csmaNodes2,csmaNodes3,csmaNodes4;
	//
	// csmaNodes1.Add(secondgroup1.Get(1));
	// csmaNodes1.Create(2);
	// csmaNodes2.Add(secondgroup1.Get(2));
	// csmaNodes2.Create(2);
	// csmaNodes3.Add(secondgroup2.Get(1));
	// csmaNodes3.Create(2);
	// csmaNodes4.Add(secondgroup2.Get(2));
	// csmaNodes4.Create(2);
	//


	// //Construct ptp topo  upper
	// PointToPointHelper ptp1,ptp2;
	// ptp1.SetDeviceAttribute ("DataRate", StringValue ("3Mbps"));
	// ptp1.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (500)));
	// ptp2.SetDeviceAttribute ("DataRate", StringValue ("3Mbps"));
	// ptp2.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (500)));
	//
	// NetDeviceContainer devicePtp1,devicePtp2;
	// devicePtp1=ptp1.Install (firstgroup1);
	// devicePtp2=ptp2.Install (firstgroup2);
	//
	// //Construct csma topo
	// CsmaHelper csma;
	// csma.SetChannelAttribute ("DataRate", StringValue ("1Mbps"));
	// csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (500)));
	//
	// //middle topo
	// NetDeviceContainer  deviceAggToR1,deviceAggToR2;
	// deviceAggToR1=csma.Install (secondgroup1);
	// deviceAggToR2=csma.Install (secondgroup2);

	// //lower topo
	// NetDeviceContainer deviceCsmaNodes1,deviceCsmaNodes2,deviceCsmaNodes3,deviceCsmaNodes4;
	// deviceCsmaNodes1=csma.Install (csmaNodes1);
	// deviceCsmaNodes2=csma.Install (csmaNodes2);
	// deviceCsmaNodes3=csma.Install (csmaNodes3);
	// deviceCsmaNodes4=csma.Install (csmaNodes4);

	// //Install protocol stack
	// InternetStackHelper stack;
	// stack.Install (firstgroup1);
	// stack.Install (firstgroup2.Get(1));
	// stack.Install (secondgroup1.Get(1));
	// stack.Install (secondgroup1.Get(2));
	// stack.Install (secondgroup2.Get(1));
	// stack.Install (secondgroup2.Get(2));
	// stack.Install (csmaNodes1.Get(1));
	// stack.Install (csmaNodes1.Get(2));
	// stack.Install (csmaNodes2.Get(1));
	// stack.Install (csmaNodes2.Get(2));
	// stack.Install (csmaNodes3.Get(1));
	// stack.Install (csmaNodes3.Get(2));
	// stack.Install (csmaNodes4.Get(1));
	// stack.Install (csmaNodes4.Get(2));

	// //Allocate addresses on the network
	// Ipv4AddressHelper address;
	//
	// address.SetBase ("192.168.1.0", "255.255.255.0");
	// Ipv4InterfaceContainer interfacesPtp1 = address.Assign (devicePtp1);
	//
	// address.SetBase ("192.168.2.0", "255.255.255.0");
	// Ipv4InterfaceContainer interfacesPtp2 = address.Assign (devicePtp2);
	//
	// address.SetBase ("10.1.1.0", "255.255.255.0");
	// Ipv4InterfaceContainer interfacesAggToR1 = address.Assign (deviceAggToR1);
	//
	// address.SetBase ("10.2.1.0", "255.255.255.0");
	// Ipv4InterfaceContainer interfacesAggToR2 = address.Assign (deviceAggToR2);
	//
	// address.SetBase ("10.0.1.0", "255.255.255.0");
	// Ipv4InterfaceContainer interfacesCsma1 = address.Assign (deviceCsmaNodes1);

	// address.SetBase ("10.0.2.0", "255.255.255.0");
	// Ipv4InterfaceContainer interfacesCsma2 = address.Assign (deviceCsmaNodes2);
	//
	// address.SetBase ("10.0.3.0", "255.255.255.0");
	// Ipv4InterfaceContainer interfacesCsma3 = address.Assign (deviceCsmaNodes3);
	//
	// address.SetBase ("10.0.4.0", "255.255.255.0");
	// Ipv4InterfaceContainer interfacesCsma4 = address.Assign (deviceCsmaNodes4);

	//
	//Set up many to one traffic
	//Set up n1 as a sinkApp
	// PacketSinkHelper packetSinkHelper("ns3::TcpSocketFactory", InetSocketAddress(interfacesCsma1.GetAddress(1),8080));
	// ApplicationContainer sinkApp = packetSinkHelper.Install(csmaNodes1.Get(1));
	//
	// sinkApp.Start(Seconds(0.0));
	// sinkApp.Stop(Seconds(80.0));

  	//csma.EnablePcap("N1 recieved packets", deviceCsmaNodes1.Get(1),true);




	// //set up n2-->n1
	// OnOffHelper client1("ns3::TcpSocketFactory", InetSocketAddress(interfacesCsma1.GetAddress(1), 8080));
	// client1.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	// client1.SetAttribute ("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	// client1.SetAttribute ("DataRate", DataRateValue (DataRate ("1.0Mbps")));
	// client1.SetAttribute ("PacketSize", UintegerValue (2000));

	// ApplicationContainer clientApp1 = client1.Install (csmaNodes1.Get(2));
	// clientApp1.Start(Seconds (1.0 ));
	// clientApp1.Stop (Seconds (21.0));
	//
  //   csma.EnablePcap ("Pattern3device n2 to n1 ", deviceCsmaNodes1.Get (2), true);
	//
	// //set up n3-->n1
	// OnOffHelper client2("ns3::TcpSocketFactory", InetSocketAddress(interfacesCsma1.GetAddress(1), 8080));
	// client2.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	// client2.SetAttribute ("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	// client2.SetAttribute ("DataRate", DataRateValue (DataRate ("1.0Mbps")));
	// client2.SetAttribute ("PacketSize", UintegerValue (2000));
	// ApplicationContainer clientApp2 = client2.Install (csmaNodes3.Get(1));
	// clientApp2.Start(Seconds (1.0 ));
	// clientApp2.Stop (Seconds (21.0));
	//
  //   csma.EnablePcap ("Pattern3device n3 to n1", deviceCsmaNodes2.Get (1), true);

	//
	//Set up n4-->n1
	// OnOffHelper client3("ns3::TcpSocketFactory", InetSocketAddress(interfacesCsma1.GetAddress(1), 8080));
	// client3.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	// client3.SetAttribute ("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	// client3.SetAttribute ("DataRate", DataRateValue (DataRate ("1.0Mbps")));
	// client3.SetAttribute ("PacketSize", UintegerValue (2000));

	// ApplicationContainer clientApp3 = client3.Install (csmaNodes2.Get(2));
	// clientApp3.Start(Seconds (1.0 ));
	// clientApp3.Stop (Seconds (21.0));
	//
  //   csma.EnablePcap ("Pattern3device n4 to n1", deviceCsmaNodes2.Get (2), true);

	// //Set up n5-->n1
	// OnOffHelper client4("ns3::TcpSocketFactory", InetSocketAddress(interfacesCsma1.GetAddress(1), 8080));
	// client4.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	// client4.SetAttribute ("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	// client4.SetAttribute ("DataRate", DataRateValue (DataRate ("1.0Mbps")));
	// client4.SetAttribute ("PacketSize", UintegerValue (2000));
	//
	// ApplicationContainer clientApp4 = client4.Install (csmaNodes3.Get(1));
	// clientApp4.Start(Seconds (1.0 ));
	// clientApp4.Stop (Seconds (21.0));
	//
  //   csma.EnablePcap ("Pattern3device n5 to n1", deviceCsmaNodes3.Get (1), true);
	//
	//
	// //Set up n6-->n1
	// OnOffHelper client5("ns3::TcpSocketFactory", InetSocketAddress(interfacesCsma1.GetAddress(1), 8080));
	// client5.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	// client5.SetAttribute ("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	// client5.SetAttribute ("DataRate", DataRateValue (DataRate ("1.0Mbps")));
	// client5.SetAttribute ("PacketSize", UintegerValue (2000));

	// ApplicationContainer clientApp5 = client5.Install (csmaNodes3.Get(2));
	// clientApp5.Start(Seconds (1.0 ));
	// clientApp5.Stop (Seconds (21.0));
	//
  //   csma.EnablePcap ("Pattern3device n6 to n1", deviceCsmaNodes3.Get (2), true);
	//
	// //Set up n7-->n1
	// OnOffHelper client6("ns3::TcpSocketFactory", InetSocketAddress(interfacesCsma1.GetAddress(1), 8080));
	// client6.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	// client6.SetAttribute ("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	// client6.SetAttribute ("DataRate", DataRateValue (DataRate ("1.0Mbps")));
	// client6.SetAttribute ("PacketSize", UintegerValue (2000));
	//
	// ApplicationContainer clientApp6 = client6.Install (csmaNodes4.Get(1));
	// clientApp6.Start(Seconds (1.0 ));
	// clientApp6.Stop (Seconds (21.0));
	//
  //   csma.EnablePcap ("Pattern3device n7 to n1", deviceCsmaNodes4.Get (1), true);
	//
	// //Set up n8-->n1
	// OnOffHelper client7("ns3::TcpSocketFactory", InetSocketAddress(interfacesCsma1.GetAddress(1), 8080));
	// client7.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	// client7.SetAttribute ("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	// client7.SetAttribute ("DataRate", DataRateValue (DataRate ("1.0Mbps")));
	// client7.SetAttribute ("PacketSize", UintegerValue (2000));
	//
	// ApplicationContainer clientApp7 = client7.Install (csmaNodes4.Get(2));
	// clientApp7.Start(Seconds (1.0 ));
	// clientApp7.Stop (Seconds (21.0));
	//
  //   csma.EnablePcap ("Pattern3device n8 to n1", deviceCsmaNodes4.Get (2), true);


	// Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  AnimationInterface anim("a.xml");

	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}
