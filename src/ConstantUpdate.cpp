#include "HEAR_mission/ConstantUpdate.hpp"

void ConstantUpdate::perform() {
    _output_port_0->receiveMsgData((DataMsg*)&float_msg);
}

ConstantUpdate::ConstantUpdate(float t_val) {
    float_msg.data = t_val;
    _output_port_0 = new OutputPort(ports_id::OP_0, this);
    _ports = {_output_port_0};
}
ConstantUpdate::~ConstantUpdate(){
    
}