#include "WirelessNetwork.h"
#include "BaseStation.h"
#include "Channel.h"
#include "Package.h"
#include"Logger.h"
#include "ReceivingStation.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;


WirelessNetwork::WirelessNetwork(int k)
{
	k_basestation=k;
	k_receivingstation=k;
	
	
	for (int i = 0; i < k_basestation; i++)
	{
		
		auto n_basestation = new BaseStation(i);
		basestation_.push_back(n_basestation);
		

		auto n_receivingstation = new ReceivingStation(i);
		receivingstation_.push_back(n_receivingstation);

	}
	
	system_clock_ = 0;
	
}

WirelessNetwork::~WirelessNetwork()
= default;

int WirelessNetwork::Getk_basestation()
{
	return k_basestation;
}



bool WirelessNetwork::IsRetransmission()
{
	return retr_package;
}


void WirelessNetwork::StartTransmission(Logger* logger, Channel* channel)
{
	
	logger->Debug("Started transmission of packet:"+ to_string(channel->channel_queue.front()->GetPackageID()) + "\n");
		
}

void WirelessNetwork::EndTransmission(Logger* logger, Channel* channel)
{
	
	logger->Info("End of  transmission of packet:" + to_string(channel->channel_queue.front()->GetPackageID()) + "\n");
	
}