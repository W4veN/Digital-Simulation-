#include "Channel.h"
#include<vector>
#include <queue>
#include<vector>
using namespace std;

Channel::Channel()
{
	is_channel_free = true;
	is_collision = false;
	
}
Channel:: ~Channel()
{

}





bool Channel::get_channel_is_empty()
{
	bool help = true; // is empty
	if (channel_queue.size() > 0)
	{
		help = false; // is not empty
	}
	return help;
}
