// #pragma once
// #include <Eigen/Geometry>
// #include <Eigen/Core>
// #include <HEAR_math/Vector3D.hpp>
// #include <vector>

// namespace FeedbackLinearization{

// using namespace Eigen;

// Vector3f toEigenVec(Vector3D<float> vec){
//     Vector3f eig_vec = Vector3f(vec.x, vec.y, vec.z);
//     return eig_vec;
// }

// Vector3D<float> fromEigVec(Vector3f eig_vec){
//     Vector3D<float> vec = {eig_vec.x(), eig_vec.y(), eig_vec.z()};
//     return vec;
// }

// Matrix3f vecs2Rotmat(Vector3D<float> x_1, Vector3D<float> y_1, Vector3D<float> z_1){
//     Matrix3f m;
//     m << x_1.x, x_1.y, x_1.z,
//         y_1.x, y_1.y, y_1.z,
//         z_1.x, z_1.y, z_1.z;
//     return m;
// }

// Quaternionf eul2quat(float roll, float pitch, float yaw){
//     Quaternionf q;
//     q = AngleAxisf(roll, Vector3f::UnitX())
//     * AngleAxisf(pitch, Vector3f::UnitY())
//     * AngleAxisf(yaw, Vector3f::UnitZ());
    
//     return q;
// }

// Vector3f toHorizon(Vector3f x, float yaw){
//     auto q = eul2quat(0, 0, yaw);
//     return q._transformVector(x);
// }

// Vector3f backFromHorizon(Vector3f x, float yaw){
//     auto q = eul2quat(0, 0, yaw);
//     q = q.inverse();
//     return q._transformVector(x);
// }

// Vector3f rotm2Rodparam(Matrix3f rot){
//     AngleAxisf a_(rot);
//     Vector3f rod_param = a_.axis();
//     auto angle  = a_.angle();
// //    rod_param = rod_param*(abs(angle)>180? angle - sign(angle)*360 : angle); //todo: check 
//     return rod_param;
// }

// Matrix3f eul2Rotmat(const float &roll, const float &pitch, const float &yaw){
//     Quaternionf quat = eul2quat(roll, pitch, yaw);
//     return quat.toRotationMatrix();
// }

// }