#include "HEAR_math/ConstantFloat.hpp"

ConstantFloat::ConstantFloat(float t_val) {
    this->_input_port_0 = new InputPort(ports_id::IP_0_DATA, this);
    this->_input_port_1 = new InputPort(ports_id::IP_1_TRIGGER, this);
    this->_output_port_0 = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port_0,_input_port_1, _output_port_0};
    _val = t_val;
}

ConstantFloat::~ConstantFloat() {

}

void ConstantFloat::process(DataMsg* t_msg, Port* t_port) {
    if(t_port->getID() == ports_id::IP_0_DATA){
        _val = ((FloatMsg*)t_msg)->data;
        sendVal();
    }
    else if(t_port->getID() == ports_id::IP_1_TRIGGER){
        sendVal();
    }
}

void ConstantFloat::sendVal() {
    FloatMsg t_float_msg;
    t_float_msg.data = _val;
    _output_port_0->receiveMsgData((DataMsg*)&t_float_msg);
}