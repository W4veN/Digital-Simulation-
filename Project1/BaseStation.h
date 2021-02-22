#ifndef	BASESTATION_H
#define BASESTATION_H
#include "Package.h"
#include "Logger.h"
#include "WirelessNetwork.h"
#include <queue>
#include<vector>
#include "Generators.h"

class Generators;
class WirelessNetwork;
using namespace std;
class BaseStation
{
public:
	BaseStation(int n);
	~BaseStation();

	void Init();

	int GetBaseStationID() { return basestation_id; }



	void GeneratePackage(WirelessNetwork* wifi);
	void WaitingPackage(WirelessNetwork* wifi);
	void SetRetr_numb(int value) { retr_numb = value; }
	void SetTry_numb(int value) { try_numb = value; }
	bool GetIs_retransmission() { return is_retransmission; }
	void SetIs_retransmission(bool status) { is_retransmission = status; }


	void SetAck(bool status) { ack = status; }				//Ustawienie ACK 
	bool GetAck() { return ack; }						//pobranie ACK, True - > otrzymano False -> nie otrzymano


	void Generate_CGP();
		void Set_CGP(double value) { CGP = value; }
		double Get_CGP() { return CGP; }

	void Generate_CTP();
	void Set_CTP(double value) { CTP = value; }
	double Get_CTP() { return CTP; }

	void Generate_CRP();
	void Set_CRP(double value) { CRP = value; }
	double Get_CRP() { return CRP; }

	void Generate_CP();
	void Set_CP(double value) { CP = value; }
	double Get_CP() { return CP; }

	bool Get_is_transmitting() { return is_trasmitting; }
	void Set_is_transmitting(bool status) { is_trasmitting = status; }

	void package_incorrect_up() { package_incorrect++; }
	double Get_package_incorrect() { return package_incorrect; }

	void all_bs_package_up() { all_bs_package++; }
	double Get_all_bs_package() { return all_bs_package; }


	void SetAck_time(double value) { ack_time = value; }
	double GetAck_time() { return ack_time; }

	void SetPackage_error_rate(double value) { package_error_rate = value; }
	double GetPackage_error_rate() { return package_error_rate; }

	queue<Package*> buffer;				// kolejka pakietow
	Logger* logger;
	//----------------------------------------------------------------------------------------
	void SetCgpkKernel(double& kernel) { cgpk_kernel = kernel; }
	double GetCgpkKernel() { return cgpk_kernel; }

	void CreateCgpkGenerator() { cgpk_generator = new Generators(cgpk_kernel); }
	Generators* GetCgpkGenerator() { return cgpk_generator; }

	void SetCtpkKernel(double& kernel) { ctpk_kernel = kernel; }
	double GetCtpkKernel(){return ctpk_kernel;}

	void CreateCtpkGenerator() { ctpk_generator = new Generators(ctpk_kernel); }
	Generators* GetCtpkGenerator() { return ctpk_generator; }

	void SetRKernel(double& kernel) { r_kernel = kernel; }
	double GetRKernel() { return r_kernel; }

	void SetTKernel(double& kernel) { t_kernel = kernel; }
	double GetTKernel() { return t_kernel; }

	void CreateeRGenerator() { r_generator = new Generators(r_kernel); }
	Generators* GetRGenerator() { return r_generator; }

	void CreateeTGenerator() { t_generator = new Generators(t_kernel); }
	Generators* GetTGenerator() { return t_generator; }

	void SetCTP_temp(double value) { CTP_temp = value; }
private:	
	
	size_t time_ctiz = 1;
	int basestation_id;					// zmienna okreœlaj¹ca dany nadajnik
	double ack_time=1.0;					//czas transmisji informacji ACK
	double package_incorrect = 0;
	double all_bs_package = 0;
	int retr_numb = 0;
	int try_numb = 0;
	//double channel_time;				// czas sprawdzania zajêtoœci kana³u
	double CGP=0;
	double CTP = 0;
	double CTP_temp = 0;
	double CRP=0;
	double CP = 0;
	double t = 0;
	double r = 0;
	double package_error_rate = 0;
	double cgpk_kernel;			
	double ctpk_kernel;			
	double r_kernel;		
	double t_kernel;

	Generators* cgpk_generator;	
	Generators* ctpk_generator;	
	Generators* r_generator;
	Generators* t_generator;


	bool ack=false;									// zmienna informujaca czyoczekujemy na  ACK | true=oczekujemy, false=nie oczekujemy.				
	bool is_retransmission=false;				//zmiennna okreœlaj¹ca czy dokonywana jest retransmisja
	bool is_trasmitting=false;
				
	
			
	

};

#endif // !Basestation