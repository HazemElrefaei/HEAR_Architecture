#include "HEAR_math/PolyFilter.hpp"

PolyFilter::PolyFilter(int freq, uint8_t win_sz, uint8_t deg): _win_sz(win_sz), _dt(1.0/freq), _deg(deg) {
    this->_input_port_0 = new InputPort(ports_id::IP_0_DATA, this);
    this->_output_port_0 = new OutputPort(ports_id::OP_0_FILT, this);
    this->_output_port_1 = new OutputPort(ports_id::OP_1_FILT_DOT, this);
    _ports = {_input_port_0, _output_port_0, _output_port_1};

    t_val = std::vector<float>(win_sz);
    sig_val = std::deque<float>(win_sz);
    for (uint8_t i =0; i<_win_sz; i++){
        t_val[i] = _dt*i;
    }
}
PolyFilter::~PolyFilter(){

}

void PolyFilter::process(DataMsg* t_msg, Port* t_port){
    if(t_port->getID() == ports_id::IP_0_DATA){
        FloatMsg* float_msg = (FloatMsg*)t_msg;
        FloatMsg *filt_msg = new FloatMsg(), *filt_dot_msg = new FloatMsg();
        if(init_count < _win_sz){
            auto filt = float_msg->data;

            sig_val[init_count] = filt;
            init_count++;
            
            filt_msg->data = filt;
            filt_dot_msg->data = (filt - _prev)/_dt;
            this->_output_port_0->receiveMsgData(filt_msg);
            this->_output_port_1->receiveMsgData(filt_dot_msg);
        }
        else{
            sig_val.pop_front();
            sig_val.push_back(float_msg->data);

            auto p = polyfit(t_val, sig_val, _deg);
            auto k = polyder(p);
            filt_msg->data = polyval(p, t_val.back());
            filt_dot_msg->data = polyval(k, t_val.back());
            this->_output_port_0->receiveMsgData(filt_msg);
            this->_output_port_1->receiveMsgData(filt_dot_msg);
        }
    }
}

