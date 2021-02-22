#ifndef RECEIVINGSTATION_H
#define RECEIVINGSTATION_H


class ReceivingStation
{
public:
    ReceivingStation(int n);
    ~ReceivingStation();
    int GetReceivingStationID();
    
private:    
                    //informacja czy wyst¹pi³a kolizja 
 bool send_ack;                      //zmienna decyduj¹ca czy wysylamy ack
 int time_crp;                  //czas retransmisji pakietu
 int  receivingstation_id;      //zmienna okreœlaj¹ca konkretn¹ stacjê nadawcz¹
 int ret_number;                //zmienna okreslajaca numer retransmisji

};
#endif // !ReceivingStation
