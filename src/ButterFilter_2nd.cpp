#include "HEAR_math/ButterFilter_2nd.hpp"

ButterFilter_2nd::ButterFilter_2nd() {
    initPorts();
    Logger::getAssignedLogger()->log("2nd Order ButterFilter Initialized Without Parameters!", LoggerLevel::Warning);
}

ButterFilter_2nd::ButterFilter_2nd(BF_settings t_settings) {
    initPorts();
    if (t_settings == BF_settings::FS120FC5) {
        updateCoeff(coeff_120Hz_2nd_butter_5hz);
    }
    else if(t_settings == BF_settings::FS200FC10) {
        updateCoeff(coeff_200Hz_2nd_butter);
    }
    else if (t_settings == BF_settings::FS200FC50) {
        updateCoeff(coeff_200Hz_2nd_butter_50hz);
    }
    else if (t_settings == BF_settings::N200C90) {
        updateCoeff(coeff_N200C90);
    }
    else if (t_settings == BF_settings::N200C60) {
        updateCoeff(coeff_N200C60);
    }
    else if (t_settings == BF_settings::N200C50) {
        updateCoeff(coeff_N200C50);
    }
}

ButterFilter_2nd::~ButterFilter_2nd() {

}

void ButterFilter_2nd::initPorts() {
    this->_input_port_0 = new InputPort(ports_id::IP_0_DATA, this);
    this->_input_port_1 = new InputPort(ports_id::IP_1_COEFF, this);
    this->_output_port = new OutputPort(ports_id::OP_0_DATA, this);
    _ports = {_input_port_0, _input_port_1, _output_port};
}

float ButterFilter_2nd::runTask(float _ip_0) {
    float x=_ip_0;
	float y = -_coeff_in_use[0] * prev_y - _coeff_in_use[1] * prev2_y + _coeff_in_use[2] * x + _coeff_in_use[3] * prev_x + _coeff_in_use[4] * prev2_x;
    prev2_y = prev_y;
	prev_y = y;
	prev2_x = prev_x;
	prev_x = x;
    return y;
}

void ButterFilter_2nd::process(DataMsg* t_msg, Port* t_port) {
    if(t_port->getID() == ports_id::IP_0_DATA) {
        FloatMsg* float_msg = (FloatMsg*)t_msg;
        _ip_0 = float_msg->data;
        FloatMsg* x_msg = new FloatMsg();
        x_msg->data = this->runTask(_ip_0);
        this->_output_port->receiveMsgData(x_msg);

    }
    else if(t_port->getID() == ports_id::IP_1_COEFF) {
        if(t_msg->getType() == msg_type::FLOATARRAY) {
            updateCoeff(t_msg);
        }
    }
}

void ButterFilter_2nd::updateCoeff(DataMsg* t_msg) {
    FloatArrayMsg* t_array_floats = (FloatArrayMsg*) t_msg;
    for(int i=0; i<5; i++) {
        _coeff_in_use[i] = t_array_floats->data[i];
    }
}

void ButterFilter_2nd::updateCoeff(float* t_coeff) {
    for(int i=0; i<5; i++) {
        _coeff_in_use[i] = t_coeff[i];
    }
}