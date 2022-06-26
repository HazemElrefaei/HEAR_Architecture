#include "HEAR_mission/CallHeartbeat.hpp"

void CallHeartbeat::perform() {
    _output_port_0->receiveMsgData((DataMsg*)&double_msg);
}

CallHeartbeat::CallHeartbeat(double t_val) {
    double_msg.data = t_val;
    _output_port_0 = new OutputPort(ports_id::OP_0, this);
    _ports = {_output_port_0};
}
CallHeartbeat::~CallHeartbeat(){
    
}