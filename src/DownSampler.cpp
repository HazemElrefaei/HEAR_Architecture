#include "HEAR_math/DownSampler.hpp"

DownSampler::DownSampler(float t_down_sample_rate) {
    _input_port_0 = new InputPort(ports_id::IP_0_DATA, this);
    _output_port_0 = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port_0, _output_port_0};

    _down_sample_rate = t_down_sample_rate;
    resetCounter();
}

void DownSampler::resetCounter() {
    _counter = 0;
}

void DownSampler::process(DataMsg* t_msg, Port* t_port) {
    if(t_port->getID() == ports_id::IP_0_DATA) {
        _counter++;
        if(_counter >= 1/_down_sample_rate) {
            this->_output_port_0->receiveMsgData(t_msg);
            resetCounter();
        }
    }
}
