#pragma once
#include "HEAR_mission/MissionElement.hpp"
#include "HEAR_msg/FloatMsg.hpp"

class ConstantUpdate : public MissionElement{
private:
    Port* _output_port_0;
public:
    enum ports_id {OP_0};
    FloatMsg float_msg;
    void perform();
    void process(DataMsg* t_msg, Port* t_port) {};
    ConstantUpdate(float);
    ~ConstantUpdate();
};