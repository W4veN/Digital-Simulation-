#ifndef SIMULATOR_H_
#define SIMULATOR_H
#include "WirelessNetwork.h"
#include "Package.h"
#include "Channel.h"
#include<queue>
using namespace std;
class Simulator
{
public:

    Simulator(WirelessNetwork* wifi, Channel* channel, Logger* loggerr);
    void M1(double time);
    void wait_key(bool status);
    void update_generator_time();
    void Results(WirelessNetwork* wifi_);

private:
    Logger* logger_ = nullptr;
    WirelessNetwork* wifi_ = nullptr;
    Channel* channel_ = nullptr;
    double simulation_time=50000;
    double max_simulation_time;
    queue<Package*> p_correct;
    queue<Package*> p_incorrect;
    int package_correct=0;
    int correct_id = 1;
    double delay_time = 0;
    double wait_p_time = 0.0;
    int k = 10;
};

#endif