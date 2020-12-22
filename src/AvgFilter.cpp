#include "HEAR_math/AvgFilter.hpp"

AvgFilter::AvgFilter(int _samples) {
    this->_num_samples = _samples;
    _input_port = new InputPort(ports_id::IP_0_DATA, this);
    _output_port = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port, _output_port};
}

AvgFilter::~AvgFilter() {

}

void AvgFilter::process(DataMsg* t_msg, Port* t_port) {
    if(t_port->getID() == ports_id::IP_0_DATA) {
        float data = ((FloatMsg*)t_msg)->data;
        _float_msg.data = (_float_msg.data*_num_samples)/(_num_samples + 1) + data/(_num_samples+1);
        _output_port->receiveMsgData((DataMsg*)&_float_msg);
    }
}