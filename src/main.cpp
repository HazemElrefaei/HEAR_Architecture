#include <iostream>

#include "HEAR_actuation/ActuationSystem.hpp"
#include "HEAR_actuation/Actuator.hpp"
#include "HEAR_actuation/HexaActuationSystem.hpp"
#include "HEAR_actuation/QuadActuationSystem.hpp"

#include "HEAR_control/BB_values.hpp"
#include "HEAR_control/BoundingBoxController.hpp"
#include "HEAR_control/Controller.hpp"
#include "HEAR_control/MRFT_values.hpp"
#include "HEAR_control/MRFTController.hpp"
#include "HEAR_control/PID_values.hpp"
#include "HEAR_control/PIDController.hpp"

#include "HEAR_core/Block.hpp"
#include "HEAR_core/DataMsg.hpp"
#include "HEAR_core/InputPort.hpp"
#include "HEAR_core/MsgEmitter.hpp"
#include "HEAR_core/MsgReceiver.hpp"
#include "HEAR_core/OutputPort.hpp"
#include "HEAR_core/Port.hpp"

#include "HEAR_math/Matrix3by3.hpp"
#include "HEAR_math/Pose.hpp"
#include "HEAR_math/Poses.hpp"
#include "HEAR_math/Quaternion.hpp"
#include "HEAR_math/RotationMatrix3by3.hpp"
#include "HEAR_math/Sum.hpp"
#include "HEAR_math/TaggedPoses.hpp"
#include "HEAR_math/Vector2D.hpp"
#include "HEAR_math/Vector3D.hpp"

#include "HEAR_misc/Timer.hpp"
#include "HEAR_misc/ButterFilter_2nd.hpp"
#include "HEAR_misc/Demux3D.hpp"
#include "HEAR_misc/Differentiator.hpp"
#include "HEAR_misc/InvertedSwitch.hpp"
#include "HEAR_misc/logger.hpp"
#include "HEAR_misc/Mux3D.hpp"
#include "HEAR_misc/Saturation.hpp"
#include "HEAR_misc/std_logger.hpp"
#include "HEAR_misc/Switch.hpp"

#include "HEAR_mission/Arm.hpp"
#include "HEAR_mission/Condition.hpp"
#include "HEAR_mission/Disarm.hpp"
#include "HEAR_mission/DNNConfirmationCondition.hpp"
#include "HEAR_mission/internal_states.hpp"
#include "HEAR_mission/MissionCommand.hpp"
#include "HEAR_mission/MissionElement.hpp"
#include "HEAR_mission/MissionPipeline.hpp"
#include "HEAR_mission/MissionScenario.hpp"
#include "HEAR_mission/ResetController.hpp"
#include "HEAR_mission/SetAbsoluteWaypoint.hpp"
#include "HEAR_mission/SetHeightOffset.hpp"
#include "HEAR_mission/SetRelativeWaypoint.hpp"
#include "HEAR_mission/SetRestNormSettings.hpp"
#include "HEAR_mission/SwitchTrigger.hpp"
#include "HEAR_mission/UpdateController.hpp"
#include "HEAR_mission/Wait.hpp"
#include "HEAR_mission/WaitForCondition.hpp"

#include "HEAR_msg/BooleanMsg.hpp"
#include "HEAR_msg/DoubleMsg.hpp"
#include "HEAR_msg/EmptyMsg.hpp"
#include "HEAR_msg/filterPointMsg.hpp"
#include "HEAR_msg/FloatMsg.hpp"
#include "HEAR_msg/IntegerMsg.hpp"
#include "HEAR_msg/PointsMsg.hpp"
#include "HEAR_msg/PoseMsg.hpp"
#include "HEAR_msg/PosesMsg.hpp"
#include "HEAR_msg/TaggedPosesMsg.hpp"
#include "HEAR_msg/Vector2DMsg.hpp"
#include "HEAR_msg/Vector3DMsg.hpp"
#include "HEAR_msg/VectorDoubleMsg.hpp"
#include "HEAR_msg/VectorMsg.hpp"
#include "HEAR_msg/ControllerMsg.hpp"
#include "HEAR_msg/OptitrackMessage.hpp"
#include "HEAR_msg/IMUMsg.hpp"
#include "HEAR_msg/ArmDataMsg.hpp"
#include "HEAR_msg/ErrorMsg.hpp"
#include "HEAR_msg/InfoMsg.hpp"
#include "HEAR_msg/MissionCommandMsg.hpp"
#include "HEAR_msg/PositionMsg.hpp"
#include "HEAR_msg/ResetControllerMsg.hpp"
#include "HEAR_msg/RestrictedNormRefSettingsMsg.hpp"

#include "HEAR_nav/Global2Inertial.hpp"
#include "HEAR_nav/Transform_InertialToBody.hpp"
#include "HEAR_nav/Waypoint.hpp"
#include "HEAR_nav/WrapAroundFunction.hpp"

int main(int argc, char **argv)
{
	std::cout << "HI (:" << std::endl;
}