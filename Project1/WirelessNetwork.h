#ifndef WIRELESSNETWORK_H
#define WIRELESSNETWORK_H
#include <vector>
#include <queue>
#include "BaseStation.h"
#include "ReceivingStation.h"
#include "Channel.h"
#include "Logger.h"
#include"Generators.h"

class BaseStation;
class Channel;
class Logger;
using namespace std;

class WirelessNetwork
{
public:
	WirelessNetwork(int k);
	~WirelessNetwork();

	vector<BaseStation*> basestation_;							// wektor stacji nadawczych
	
	vector<ReceivingStation*> receivingstation_;				// wektor stacji odbiorczych
	  

	
	void setChanell(bool status);									//ustawia status zajetosci kanalu w sieci
	bool IsRetransmission();										//metoda zwracajaca czy mamy do czynienia z retransmisja TRUE -> retransmisja FALSE -> brak retransmisji
	

	int GetLR() { return lr; }
	int Getk_basestation();
	
	void StartTransmission(Logger* logger, Channel* channel);
	void EndTransmission(Logger* logger, Channel*channel);

	void SetRetrPackage(bool status) { retr_package = status; }

	void package_counter_up() { package_counter++; }
	double get_all_package() { return package_counter; }
	void package_correct_up() { package_correct++; }
	double get_package_correct() { return package_correct; }
	int get_package_counter() { return package_counter; }

	void All_retransmission_up() { all_retransmissions++; }
	double GetAll_retransmissions() { return all_retransmissions; }

	void SetAverage_number_of_retransmissions(double value) { average_number_of_retransmissions = value; }
	double GetAverage_number_of_retransmissions() { return average_number_of_retransmissions; }

	void SetAvarage_package_dalay(double value) { avarage_package_dalay = value; }
	double GetAvarage_package_dalay() { return avarage_package_dalay; }

	void SetAvarage_waiting_time(double value) { avarage_waiting_time = value; }
	double GetAvarage_waiting_time() { return avarage_waiting_time; }
	void SetSystem_bit_rate(double value) { system_bit_rate = value; }
	double GetSystem_bit_rate(){ return system_bit_rate; }

	void Set_time_being_all(double value) { time_being_all += value; }
	double Get_time_being_all() { return time_being_all; }

	void Set_time_end_all(double value) { time_end_all += value; }
	double Get_time_end_all() { return time_end_all; }

	void Set_time_buffer_all(double value) { time_buffer_all += value; }
	double Get_time_buffer_all() { return time_buffer_all; }

	void SetTerKernel(int& kernel) { ter_kernel = kernel; }
	double GetTeRKernel() { return ter_kernel; }

	void CreateTerGenerator() { ter_generator = new Generators(ter_kernel); }
	Generators* GetTerGenerator() { return ter_generator; }

	void all_packages_counter_up() { all_packages_counter++; }
	int get_all_packages_counter() { return all_packages_counter; }
private:
									//zmienna okreœlaj¹ca max czas zwrotnego potwierdzenia ACK
	int k_basestation;											//liczba nadajników
	int k_receivingstation;										//liczba odbiorników
	int package_correct = 0;
	double all_packages_counter = 0;
	bool retr_package=false;											//zmienna okreœlaj¹ca czy dany pakiet bêdzie retransmitowany
	size_t system_clock_ ;										//czas systemu
	
	size_t id = 0;
	size_t bs_id_;
	double package_counter = 1;
	int lr = 10;						//max liczba retransmisjii
	double all_retransmissions = 0;
	double average_number_of_retransmissions = 0;
	double avarage_package_dalay = 0;
	double avarage_waiting_time = 0;
	double system_bit_rate=0;

	double time_being_all = 0;
	double time_end_all = 0;
	double time_buffer_all = 0;


	double ter_kernel;								// ziarno dla generatora TER
	Generators* ter_generator;						// Generator TER
	int ter;
};








#endif // !WirelessNetwork