#include"ns3/core-module.h"
#include"ns3/network-module.h"
#include"ns3/csma-module.h"
#include"ns3/applications-module.h"
#include"ns3/internet-apps-module.h"
#include"ns3/internet-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("CsmaPingExample");

static void PingRtt(std::string context, Time Rtt){
	std::cout<<context<<""<<Rtt<<std::endl;
}


int main(int argc, char*argv[]){
	
	CommandLine cmd;
	cmd.Parse(argc,argv);
	
	NodeContainer nodes;
	nodes.Create(6);
	
	CsmaHelper csma;
	csma.SetChannelAttribute("DataRate",DataRateValue(DataRate(10000)));
	csma.SetChannelAttribute("Delay",TimeValue(MilliSeconds(0.2)));
	NetDeviceContainer devs=csma.Install(nodes);
	
	InternetStackHelper ipstack;
	ipstack.Install(nodes);
	
	Ipv4AddressHelper ip;
	ip.SetBase("10.1.1.0","255.255.255.0");
	Ipv4InterfaceContainer addresses=ip.Assign(devs);
	
	uint16_t port=9;
	OnOffHelper onoff("ns3::UdpSocketFactory",Address(InetSocketAddress(addresses.GetAddress(2),port)));
	onoff.SetConstantRate(DataRate("500Mb/s"));
	ApplicationContainer app=onoff.Install(nodes.Get(0));
	app.Start(Seconds(0.0));
	app.Stop(Seconds(10.0));
	
	PacketSinkHelper sink("ns3::UdpSocketFactory",Address(InetSocketAddress(Ipv4Address::GetAny(),port)));
	app=sink.Install(nodes.Get(2));
	app.Start(Seconds(0.0));
	
	V4PingHelper ping=V4PingHelper(addresses.GetAddress(2));
	NodeContainer pingers;
	pingers.Add(nodes.Get(0));
	pingers.Add(nodes.Get(1));
	
	ApplicationContainer apps;
	apps=ping.Install(pingers);
	apps.Start(Seconds(1.0));
	apps.Stop(Seconds(5.0));
	
	Config::Connect ("/NodeList/*/ApplicationList/*/$ns3::V4Ping/Rtt",MakeCallback (&PingRtt));
	
	AsciiTraceHelper ascii;
	csma.EnableAsciiAll(ascii.CreateFileStream("ping1.tr"));
	
	
	Simulator::Run();
	Simulator::Destroy();
	return 0;
}
	
	
	
