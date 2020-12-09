#pragma once
#include "HEAR_mission/MissionElement.hpp"
#include "HEAR_msg/BoolMsg.hpp"

class SendBoolSignal : public MissionElement {
private:
    Port* _output_port_0;
    bool _val;
public:
    enum ports_id {OP_0};
    void perform();
    SendBoolSignal(bool);
    ~SendBoolSignal();
};