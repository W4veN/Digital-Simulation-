#ifndef RECEIVINGSTATION_H
#define RECEIVINGSTATION_H


class ReceivingStation
{
public:
    ReceivingStation(int n);
    ~ReceivingStation();
    int GetReceivingStationID();
    
private:    
                    //informacja czy wyst�pi�a kolizja 
 bool send_ack;                      //zmienna decyduj�ca czy wysylamy ack
 int time_crp;                  //czas retransmisji pakietu
 int  receivingstation_id;      //zmienna okre�laj�ca konkretn� stacj� nadawcz�
 int ret_number;                //zmienna okreslajaca numer retransmisji

};
#endif // !ReceivingStation
