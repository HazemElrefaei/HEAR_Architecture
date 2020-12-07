#pragma once
#include <functional>

#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"
#include "HEAR_msg/FloatMsg.hpp"

class HoldVal : public Block {
private:
    DataMsg* _val;
    std::function<bool(float,float)> _operation;
    float _trigger_value;
    Port* _input_port;
    Port* _trigger_port;
    Port* _output_port_0;
    bool hold = false;
    void triggerCallback(float t_current_value);
public:
    HoldVal(std::function<bool(float,float)> t_operation, float t_trigger_value);
    enum ports_id {IP_0_DATA, IP_1_TRIGGER, OP_0_DATA};
    void process(DataMsg* t_msg, Port* t_port);
    ~HoldVal();
};