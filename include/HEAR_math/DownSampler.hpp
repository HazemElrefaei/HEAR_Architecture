#pragma once
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"

class DownSampler : public Block {
private:
    Port* _input_port_0;
    Port* _output_port_0;
    float _down_sample_rate;
    int _counter;
    void resetCounter();

public:
    DownSampler(float);
    enum ports_id {IP_0_DATA, OP_0_DATA};
    void process(DataMsg* t_msg, Port* t_port);
    ~DownSampler();
};