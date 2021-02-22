#ifndef PACKAGE_H
#define PACKAGE_H
class Package
{
public:
	Package(double p_id, int bs_id);        //(size_t p_time, size_t p_id);
	~Package();

	int GetPackageID() { return package_id; }
	int GetRetransmission_number() { return retransmission_number; }
	void ImproveRetransmission_number() { retransmission_number++; }

	int GetTry_number() { return try_number; }
	void ImproveTry_number() { try_number++; }

	void  SetTime_end(double t) { time_end = t; }
	double GetTime_end() { return time_end; }

	void SetTimeBeing(double t) { time_being = t; }
	double GetTimeBeing() { return time_being; };

	void SetTimeService(double t) { time_service = t; }
	double GetTimeService() { return time_service; };

	void SetAck_time(double t) { ack_time = t; };
	double GetAck_time() { return ack_time; };


	void SetWait_time(bool status) { wait_time = status; }
	bool GetWait_time() { return wait_time; }

	void SetSend_ACK(bool status) { ack_flag = status; }
	bool GetSend_ACK() { return ack_flag; }

	
	
	int GetBS_ID() { return base_id; }
	
	void Improve_channel_time() { channel_time += 0.5; } //+0.5ms
	void Clear_channel_time() { channel_time = 0; }
	double Get_channel_time() { return channel_time; }
private:

	double channel_time = 0.0;
	int package_id;											//zmienna okreœlaj¹ca to¿samoœæ pakietu 
	int base_id;
	double time_service=0.0; 								//zmienna okreœlaj¹ca czas transmisji pakietu ustawiony na sztywno w celu sprawdzenia dzialania
	double time_being=0;											//czas pojawienia siê pakietu
	double time_end=0.0;										//czas obs³ugi pakietu
	double time_buffer=0.0;
	double ack_time=1;
	int try_number = 0;
	int retransmission_number=0;								//zmienna okreœlaj¹ca liczbê dokonanych ju¿ retransmisji 
	bool retr_package = false;
	bool ack_flag=false;
	bool ter_collision;
	bool wait_time = false;
};

#endif // !Package