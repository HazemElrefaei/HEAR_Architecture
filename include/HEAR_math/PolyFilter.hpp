#pragma once
#include "HEAR_core/common_types.hpp"
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Block.hpp"
#include "HEAR_msg/FloatMsg.hpp"
#include "HEAR_msg/FloatArrayMsg.hpp"
#include "HEAR_core/logger.hpp"
#include "HEAR_math/polyfit.hpp"
#include <vector>
#include <list>
#include <deque>

class PolyFilter: public Block {
private:
    Port* _input_port_0;
    Port* _output_port_0;
    Port* _output_port_1;
    uint8_t _win_sz, _deg, init_count = 0;
    float _dt, _prev=0.0;
    std::vector<float> t_val;
    std::deque<float> sig_val;
public:
    enum ports_id {IP_0_DATA, OP_0_FILT, OP_1_FILT_DOT};
    void process(DataMsg* t_msg, Port* t_port);
    PolyFilter(int freq, uint8_t win_sz, uint8_t deg);
    ~PolyFilter();
};