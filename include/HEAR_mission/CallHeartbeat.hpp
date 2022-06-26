#pragma once
#include "HEAR_mission/MissionElement.hpp"
#include "HEAR_msg/DoubleMsg.hpp"

class CallHeartbeat : public MissionElement{
private:
    Port* _output_port_0;
public:
    enum ports_id {OP_0};
    DoubleMsg double_msg;
    void perform();
    void process(DataMsg* t_msg, Port* t_port) {};
    CallHeartbeat(double);
    ~CallHeartbeat();
};