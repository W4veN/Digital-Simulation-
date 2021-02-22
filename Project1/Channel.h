#ifndef CHANNEL_H
#define CHANNEL_H
#include<vector>
#include <queue>
#include"BaseStation.h"
using namespace std;
class Channel
{
public:
	Channel();
	~Channel();
	void SetChannelStatus(bool status) {is_channel_free = status;};					//ustawianie czy kana³ zajêty
	bool GetChannelStatus() {return is_channel_free;};								//odczyt czy kanal zajêty

	
	void SetCollisionStatus(bool status) { is_collision= status; }			//ustawianie czy wyst¹pi³a kolizja
	bool GetCollisionStatus() {return is_collision;}							// odczytanie czy wyst¹pi³a kolizja
	
	
	void SetTer_collision(bool status) { ter_collision = status; }
	bool GetTer_collision() { return ter_collision; }
	
	bool get_channel_is_empty();
	
	queue<Package*> channel_queue;

private:
	bool is_channel_free;					//informacja czy kana³jest wolny;
	bool is_collision;				//informacja czy wyst¹pi³a kolizja lub b³¹d ter w kanale w kanale
	bool ter_collision = false;

	
	
};

#endif // !Channel