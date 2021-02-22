#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "BaseStation.h"
#include "Package.h"
#include "Channel.h"
#include "Logger.h"
#include<queue>
#include<vector>


using namespace std;

Simulator::Simulator(WirelessNetwork* wifi, Channel* channel, Logger* loggerr)
{
	wifi_ = wifi;
	channel_ = channel;
	logger_ = loggerr;
	simulation_time = 0;
}

void Simulator::wait_key(bool status) // function to step working 
{
	if (status == true)
	{
		do
		{
			cout << '\n' << "Press a key to continue...";
		}
		while (cin.get() != '\n');
	}
}

void Simulator::M1(double time_)
{
	max_simulation_time = time_;
	bool stats = false;
	double stat_time = 0; //when are we starting to collect stats
	cout << "When you want to start collecting informations? ";
	cin >> stat_time;
	bool step_work = false;
	cout << "Do You want Step Work Simulation? \n 1 - step mode \n 0 - normal mode \n";
	cin >> step_work;
	ofstream myfile;
	ofstream myfile2;
	myfile.open("example.txt");
	myfile2.open("Example2.txt");

	Sleep(500);

	for (int i = 0; i < k; i++)
	{
		wifi_->basestation_[i]->Init(); //creating basestations
	}

	while (simulation_time < max_simulation_time)
	{
		auto no_events = false; //event_triggered flag
		auto crp_generated = false;

		if (simulation_time > stat_time)
		{
			stats = true;
		} //collecting stats

		logger_->Info("Simulation time: " + to_string(simulation_time));

		while (no_events == false)
		{
			no_events = true;// tiu
			wait_key(step_work);
			if (!channel_->channel_queue.empty()) //&& / wifi_->basestation_[channel_->channel_queue.front()->GetBS_ID()]->
				//Get_CRP() == 0)
			{
				Package* p_ptr = channel_->channel_queue.front();
				wifi_->basestation_[p_ptr->GetBS_ID()]->Set_is_transmitting(true);

				if (wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CTP() == 0 && wifi_->basestation_[p_ptr->GetBS_ID()]->
					GetAck() == false)
				{
					if (wifi_->GetTerGenerator()->RndZeroOne(0.8) == 1 || channel_->GetCollisionStatus() == true && !crp_generated) //||channel_->GetTer_collision() == true || 
					{
						channel_->SetTer_collision(true); //collsision or ter flag
						wifi_->basestation_[p_ptr->GetBS_ID()]->SetIs_retransmission(true);
						logger_->Error("TER/COLLISION");
						p_ptr->ImproveRetransmission_number(); //liczba retransmisji+1
						no_events = false;
						logger_->Info("Retransmission of package ID: " + to_string(p_ptr->GetPackageID()) + " for " + to_string(p_ptr->GetRetransmission_number()) + " time");
						wifi_->basestation_[p_ptr->GetBS_ID()]->Generate_CTP(); //CCTP generate
						if (p_ptr->GetRetransmission_number()==10)
						{
							myfile << "ID: " << to_string(p_ptr->GetPackageID()); myfile << " " << to_string(p_ptr->GetRetransmission_number()) << "\n";
						}
						wifi_->basestation_[p_ptr->GetBS_ID()]->SetRetr_numb(p_ptr->GetRetransmission_number());
						//retransmission number++
						wifi_->basestation_[p_ptr->GetBS_ID()]->Generate_CRP(); //CRP generate
						crp_generated = true;
						if (stats==true)
						{
							wifi_->All_retransmission_up();
							wait_p_time += wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CRP();
							delay_time += wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CTP();
						}
						if (wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CRP() !=0 && p_ptr->GetRetransmission_number() < wifi_->GetLR())
						{
							logger_->Info("Packet ID: " + to_string(p_ptr->GetPackageID()) + " will wait for: " + to_string(wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CRP()));
							//channel_->SetChannelStatus(true);
							wifi_->basestation_[p_ptr->GetBS_ID()]->buffer.front()=p_ptr;
							channel_->channel_queue.pop();
							wifi_->basestation_[p_ptr->GetBS_ID()]->Set_is_transmitting(false) ;
							no_events = false;
						}
						else if (p_ptr->GetRetransmission_number() >= wifi_->GetLR())
							//if number of retransmissions is more than LR packet is rejected
						{
							cout << "Package of ID: " << p_ptr->GetPackageID() << " rejected." << endl;
							wifi_->EndTransmission(logger_, channel_);
							wifi_->basestation_[p_ptr->GetBS_ID()]->Set_CRP(0); //CRP to 0
							wifi_->basestation_[p_ptr->GetBS_ID()]->SetIs_retransmission(false); //flags 
							wifi_->basestation_[p_ptr->GetBS_ID()]->Set_is_transmitting(false); //flags

							if (stats == true)
							{
								wifi_->basestation_[p_ptr->GetBS_ID()]->package_incorrect_up();
							} // incorrect packages +

							wifi_->basestation_[p_ptr->GetBS_ID()]->buffer.pop(); //out of stack 
							channel_->channel_queue.pop(); //out of stack
							channel_->SetChannelStatus(true); //channel free
							//wait_key(step_work);
							no_events = false;
						}
						wait_key(step_work);
					}
					else {
						wifi_->basestation_[p_ptr->GetBS_ID()]->SetAck(true);
						logger_->Info("ACK==true");
						wifi_->basestation_[p_ptr->GetBS_ID()]->SetIs_retransmission(false);
					}
					
				}
				if (wifi_->basestation_[p_ptr->GetBS_ID()]->GetAck_time() == 0 && no_events == true)
				{
					if(crp_generated && wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CRP() == 0)
					{
						//logger_->Info("Retransmission of package of ID: " + to_string(p_ptr->GetPackageID()));
						/*wifi_->basestation_[p_ptr->GetBS_ID()]->SetIs_retransmission(true);
						p_ptr->ImproveRetransmission_number(); //retransmission numbeR++
						if (stats == true)
						{
							wifi_->All_retransmission_up();
						} //number of retransmissions

						wifi_->basestation_[p_ptr->GetBS_ID()]->SetAck(false); //ack false
						wifi_->basestation_[p_ptr->GetBS_ID()]->SetAck_time(1.0);
						channel_->SetTer_collision(false);
						channel_->SetCollisionStatus(false);
						channel_->SetChannelStatus(false);
						crp_generated = false;
						wait_key(step_work);
						*/
					}
					else
					{
						logger_->Info("ACK received");
						myfile2 << "ID: " << to_string(p_ptr->GetPackageID()); myfile2 << " " << to_string(p_ptr->GetRetransmission_number()) << "\n";
						wifi_->EndTransmission(logger_, channel_); //packet correct
						if (stats == true)
						{
							delay_time = simulation_time - p_ptr->GetTimeBeing();
						} //how long 
						wifi_->basestation_[p_ptr->GetBS_ID()]->Set_is_transmitting(false); // flag false
						wifi_->basestation_[p_ptr->GetBS_ID()]->SetAck(false);
						wifi_->basestation_[p_ptr->GetBS_ID()]->SetAck_time(1);
						wifi_->basestation_[p_ptr->GetBS_ID()]->Generate_CTP(); //generate new CTP
						//myfile << to_string(wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CTP()) << "\n";
						wifi_->basestation_[p_ptr->GetBS_ID()]->buffer.pop(); //ot of stack
						if (stats == true)
						{
							wifi_->package_correct_up();
						} //all packages++
						channel_->channel_queue.pop(); //out of stack
						channel_->SetTer_collision(false);
						channel_->SetChannelStatus(true);
						channel_->SetCollisionStatus(false);
						wifi_->package_correct_up(); //correct +1
						wait_key(step_work);
					}
				}
				else if (wifi_->basestation_[p_ptr->GetBS_ID()]->GetAck() == true && no_events == true)
				{
					logger_->Info(
						"Waiting for ACK.   ACK time = " + to_string(
							wifi_->basestation_[p_ptr->GetBS_ID()]->GetAck_time()));
					wifi_->basestation_[p_ptr->GetBS_ID()]->SetAck_time(
						wifi_->basestation_[p_ptr->GetBS_ID()]->GetAck_time() - 0.5);

					wait_key(step_work);
				}
			}

			//channel update if is free
			if (channel_->channel_queue.empty())
			{
				channel_->SetChannelStatus(true);
				channel_->SetTer_collision(false);
			}

			//generate package and cgp
			for (int i = 0; i < k; i++)
			{
				if (wifi_->basestation_[i]->Get_CGP() <= 0)
				{
					wifi_->basestation_[i]->GeneratePackage(wifi_);
					wifi_->basestation_[i]->Generate_CGP();

					//myfile.close();
					if (stats == true)
					{
						//wifi_->basestation_[i]->all_bs_package_up();
						//wifi_->all_packages_counter_up();
					}
					wait_key(step_work); // wait for press key after generate new packet
				}
			}

			for (int i = 0; i < k; i++)
			{
				if (!wifi_->basestation_[i]->buffer.empty())
				{
					Package* p_ptr = wifi_->basestation_[i]->buffer.front();
					if (channel_->GetChannelStatus() == true && wifi_->basestation_[p_ptr->GetBS_ID()]->
						Get_is_transmitting() == false)
					{
						if (!channel_->channel_queue.empty())
						{
							channel_->SetTer_collision(true);
							channel_->SetCollisionStatus(true);
							
							//channel_->channel_queue.push(wifi_->basestation_[p_ptr->GetBS_ID()]->buffer.front());
							logger_->Error("COLLISION IN BS:" + to_string(p_ptr->GetBS_ID()) + "\n");
							no_events = false;
						}
						
						 if (channel_->channel_queue.empty() && channel_->GetChannelStatus()==true && wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CRP() == 0)//&& p_ptr->GetPackageID() == correct_id ) //start transmission -> ¿eby dzia³a³o normalnie
						//if (channel_->GetChannelStatus() == true && p_ptr->GetPackageID() == correct_id) //start transmission
						{
							channel_->channel_queue.push(wifi_->basestation_[p_ptr->GetBS_ID()]->buffer.front());
							wifi_->basestation_[p_ptr->GetBS_ID()]->Set_is_transmitting(true);
							wifi_->basestation_[p_ptr->GetBS_ID()]->Generate_CTP();
							//myfile << to_string(wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CTP()) << "\n";
							if (stats == true)
							{
								wifi_->Set_time_buffer_all(simulation_time);
								delay_time += wifi_->basestation_[p_ptr->GetBS_ID()]->Get_CTP();
							}
							if (stats == true)
							{
								//wait_p_time = wait_p_time + (simulation_time - p_ptr->GetTimeBeing());
							}
							wifi_->StartTransmission(logger_, channel_);
							if (stats == true)
							{
								wifi_->all_packages_counter_up();
							}
							no_events = false;
							wait_key(step_work);
						}
					}
				}
			}
			//channel update if is busy
			if (!channel_->channel_queue.empty())
			{
				channel_->SetChannelStatus(false);
				no_events = false;
				for (int i = 0; i < k; i++)
				{
					if (!wifi_->basestation_[i]->buffer.empty())
					{
						wifi_->basestation_[i]->buffer.front()->SetWait_time(false); //wait time false
						wifi_->basestation_[i]->buffer.front()->Clear_channel_time();
					}
				}
			}

			no_events = true;
		}
		
		logger_->Info("Time update:");

		//generator time update
		for (int i = 0; i < k; i++)
		{
			wifi_->basestation_[i]->Set_CGP((wifi_->basestation_[i]->Get_CGP() - 0.5));
			logger_->Info("BS " + to_string(i) + ": CGP = " + to_string(wifi_->basestation_[i]->Get_CGP()));


			if (wifi_->basestation_[i]->Get_is_transmitting() == true && wifi_->basestation_[i]->Get_CRP() <= 0)
			{
				if (wifi_->basestation_[i]->Get_CTP() > 0)
				{
					wifi_->basestation_[i]->Set_CTP(wifi_->basestation_[i]->Get_CTP() - 0.5);
					logger_->Info("BS " + to_string(i) + ": CTP = " + to_string(wifi_->basestation_[i]->Get_CTP()));
				}
			}
			if (wifi_->basestation_[i]->GetIs_retransmission() == true && wifi_->basestation_[i]->Get_CRP() > 0)
			{
				wifi_->basestation_[i]->Set_CRP(wifi_->basestation_[i]->Get_CRP() - 0.5);
				logger_->Info("BS " + to_string(i) + ": CRP = " + to_string(wifi_->basestation_[i]->Get_CRP()));
			}
		}
		logger_->Info("Channel status: " + to_string(channel_->GetChannelStatus()));
		simulation_time += 0.5;
		cout << endl; 
	}
	Results(wifi_);
}

//results
void Simulator::Results(WirelessNetwork* wifi_)
{
	double suma = 0;
	double temp2 = 0;
	logger_->Info("All generated packages: " + to_string(wifi_->get_package_counter()-1));
	logger_->Info("Package error rate for: ");
	for (int i = 0; i < k; i++)
	{
		double temp = wifi_->basestation_[i]->Get_all_bs_package(); //- wifi_->basestation_[i]->Get_package_incorrect();
		cout << wifi_->basestation_[i]->Get_package_incorrect() << " Unsucceeded packages from: " << temp << " generated in BS: " << i << endl;
		wifi_->basestation_[i]->SetPackage_error_rate(wifi_->basestation_[i]->Get_package_incorrect() / temp);
		logger_->Info("-BS:" + to_string(i) + " = " + to_string(wifi_->basestation_[i]->GetPackage_error_rate()));
		suma += wifi_->basestation_[i]->GetPackage_error_rate();
		temp2 += wifi_->basestation_[i]->Get_package_incorrect();
	}
	cout << endl;
	wifi_->SetAverage_number_of_retransmissions(wifi_->GetAll_retransmissions() / wifi_->get_package_counter());
	//all retransmissions/all packages
	logger_->Info("Average number of retransmissions: " + to_string(wifi_->GetAverage_number_of_retransmissions()));
	cout << endl;
	wifi_->SetSystem_bit_rate(((wifi_->get_package_counter()-temp2) * 1000)/simulation_time );
	//package correct * 1000/simulation time
	logger_->Info("System bit rate: " + to_string(wifi_->GetSystem_bit_rate()));
	cout << endl;
	wifi_->SetAvarage_package_dalay(delay_time / wifi_->get_package_counter()); //delay_time/package correct
	logger_->Info("Average package delay: " + to_string(wifi_->GetAvarage_package_dalay()));
	cout << endl;
	wifi_->SetAvarage_waiting_time(wait_p_time / wifi_->get_package_counter()); //wait time//all packages
	logger_->Info("Average waiting time: " + to_string(wifi_->GetAvarage_waiting_time()));

	cout << endl << "MIDDLE  package error:" << suma /k << endl;
}
