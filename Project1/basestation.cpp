#include "BaseStation.h"
#include "WirelessNetwork.h"
#include "Logger.h"
#include <queue>
#include <iostream>


using namespace std;
class Generators;
BaseStation::BaseStation(int n)
{
		logger = new Logger();
		ack = false;
		basestation_id=n;
	
		//Generate_CGP();
		//Generate_CGP();
	//enerate_CTP();
}




void BaseStation::GeneratePackage(WirelessNetwork* wifi)
{
	Package* package_ = new Package(wifi->get_package_counter(), basestation_id);
	logger->Info("Generate new package of ID: " + to_string(wifi->get_package_counter()) + ", from BS: " + to_string(basestation_id));
	buffer.push(package_);
	wifi->package_counter_up();
	wifi->basestation_[package_->GetBS_ID()]->all_bs_package_up();

}


void BaseStation::Init()
{
	while (!buffer.empty())
	{
		buffer.pop();
	}
}



void BaseStation::Generate_CGP()
{
	CGP = cgpk_generator->RndExp(0.005);
}

void BaseStation::Generate_CTP()
{
	CTP = ctpk_generator->Rnd(1, 10);
}

void BaseStation::Generate_CRP()
{
	r = r_generator->Rnd(0, pow(2, retr_numb) - 1);
	CRP = r * CTP;
	cout << "Generated CRP: " << CRP << endl;
}
void BaseStation::Generate_CP()
{
	t = t_generator->Rnd(0, pow(2, try_numb) - 1);
	CP = t * CTP;
}