
//TODO: change the naming of rotation matrices

#include "HEAR_math/FbLinearizer.hpp"

FbLinearizer::FbLinearizer(){
    this->_input_port_0 = new InputPort(ports_id::IP_X, this);
    this->_input_port_1 = new InputPort(ports_id::IP_ROLL, this);
    this->_input_port_2 = new InputPort(ports_id::IP_PITCH, this);
    this->_input_port_3 = new InputPort(ports_id::IP_YAW, this);
    this->_input_port_4 = new InputPort(ports_id::IP_YAW_REF, this);
    this->_input_port_5 = new InputPort(ports_id::IP_FHX_DES, this);

    this->_output_port_xh = new OutputPort(ports_id::OP_XH, this);
    this->_output_port_rot_err = new OutputPort(ports_id::OP_ROT_ERROR, this);
    this->_output_port_z_com = new OutputPort(ports_id::OP_Z_COMMAND, this);
    
    _ports = {_input_port_0, _input_port_1, _input_port_2, _input_port_3, _input_port_4, _input_port_5, _output_port_xh, _output_port_rot_err, _output_port_z_com};
    
}

FbLinearizer::~FbLinearizer(){
    
}

void FbLinearizer::process(DataMsg* t_msg, Port* t_port){
    if(t_port->getID() == ports_id::IP_X){
        
        Vector3DMsg* msg = (Vector3DMsg*)t_msg;
        tf2::Vector3 x_h = this->R_H_I*tf2::Vector3(msg->data.x, msg->data.y, msg->data.z );

        Vector3DMsg out;
        out.data = Vector3D<double>({x_h.x(), x_h.y(), x_h.z()});
        this->_output_port_xh->receiveMsgData(&out);
    
    }
    // else if(t_port->getID() == ports_id::IP_X_DOT){
        
    //     Vector3DMsg* msg = (Vector3DMsg*)t_msg;
    //     tf2::Vector3 x_h_dot = this->R_H_I*tf2::Vector3(msg->data.x, msg->data.y, msg->data.z );
    //     Vector3DMsg out;
    //     out.data = Vector3D<double>({x_h_dot.x(), x_h_dot.y(), x_h_dot.z()});
    //     this->_output_port_xh_dot->receiveMsgData(&out);
    
    // }
    else if(t_port->getID() == ports_id::IP_ROLL){
        
        this->roll = ((FloatMsg*)t_msg)->data;
    
    }
    else if(t_port->getID() == ports_id::IP_PITCH){
        
        this->pitch = ((FloatMsg*)t_msg)->data;
    
    }
    else if(t_port->getID() == ports_id::IP_YAW){
        
        this->yaw = ((FloatMsg*)t_msg)->data;
        this->R_H_I.setEulerYPR(this->yaw, 0., 0.);
        this->R_B_I.setEulerYPR(this->yaw, this->pitch, this->roll);
    
    }
    else if(t_port->getID() == ports_id::IP_YAW_REF){
        
        this->yaw_ref = ((FloatMsg*)t_msg)->data;
    
    }
    else if(t_port->getID() == ports_id::IP_FHX_DES){

        Vector3DMsg* msg = (Vector3DMsg*)t_msg;
        
        auto F_H_des = tf2::Vector3(msg->data.x, msg->data.y, msg->data.z);
        auto F_I_des = R_H_I.transpose()*F_H_des;
        auto err_angles = this->force2angles(F_I_des);  

        FloatMsg u_z;
        Vector3DMsg rot_err;
        u_z.data = (this->R_B_I*F_I_des).z();
        rot_err.data = Vector3D<double>({err_angles.x(), err_angles.y(), err_angles.z()});

        this->_output_port_z_com->receiveMsgData(&u_z);
        this->_output_port_rot_err->receiveMsgData(&rot_err);
    
    }

}

tf2::Vector3 FbLinearizer::force2angles(tf2::Vector3 F_I_des){
    auto z_B_des = F_I_des.normalized();
    auto y_aux = F_I_des.cross(tf2::Vector3(cos(this->yaw_ref), sin(this->yaw_ref), 0.0));
    auto y_B_des = y_aux.normalized();
    auto x_B_des = y_B_des.cross(z_B_des); //TODO: check if it is z_B or z_B_des
    auto R_B_des_I = tf2::Matrix3x3(x_B_des.x(), x_B_des.y(), x_B_des.z(),
                                    y_B_des.x(), y_B_des.y(), y_B_des.z(),
                                    z_B_des.x(), z_B_des.y(), z_B_des.z());
    auto R_B_B_des = R_B_I.timesTranspose(R_B_des_I);
    tf2::Quaternion quat;
    R_B_B_des.getRotation(quat);
    auto err_ang = quat.getAngleShortestPath()*quat.getAxis();
    return err_ang;
}