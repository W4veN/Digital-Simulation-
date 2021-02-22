#include "ReceivingStation.h"


ReceivingStation::ReceivingStation(int n)
{
	send_ack = true;
	time_crp=0;
	ret_number = 0;
	receivingstation_id=n;
}

int ReceivingStation::GetReceivingStationID()
{
	return receivingstation_id;
}


