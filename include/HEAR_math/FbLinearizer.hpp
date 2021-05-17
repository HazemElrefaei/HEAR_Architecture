#pragma once
#include "HEAR_core/common_types.hpp"
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_msg/FloatMsg.hpp"
#include "Vector3DMsg.hpp"
#include "HEAR_msg/FloatArrayMsg.hpp"
#include "HEAR_core/logger.hpp"
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>
#include "HEAR_math/feedbacklinearization.hpp"

#include "HEAR_core/Block.hpp"

class FbLinearizer: public Block {
private:
    Port* _input_port_0;
    Port* _input_port_1;
    Port* _input_port_2;
    Port* _input_port_3;
    Port* _input_port_4;
    Port* _input_port_5;
    Port* _output_port_xh;
    Port* _output_port_rot_err;
    Port* _output_port_z_com;
    tf2::Matrix3x3 R_B_I, R_H_I;
    float roll, pitch, yaw, yaw_ref;
    tf2::Vector3 force2angles(tf2::Vector3 F_I_des);
public:
    enum ports_id {IP_X, IP_ROLL, IP_PITCH, IP_YAW, IP_YAW_REF, IP_FHX_DES, OP_XH, OP_ROT_ERROR, OP_Z_COMMAND};
    void process(DataMsg* t_msg, Port* t_port);
    FbLinearizer();
    ~FbLinearizer();
};