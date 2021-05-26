#include <functional>
#include <gazebo/gazebo.hh>
#include <ros/ros.h>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <arm_gazebo/Angles.h>
#include <iostream>
namespace gazebo
{
	class ModelPush : public ModelPlugin
	{
	public:
		void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
		{
			// Store the pointer to the model
			this->model = _parent;

			// // intiantiate the joint controller
			this->jointController = this->model->GetJointController();

			ros::NodeHandle node;
			this->anglePublisher = node.advertise<arm_gazebo::Angles>("/publishAngles", 1000);

			if (!ros::isInitialized()) {
				int argc = 0;
				char **argv = NULL;
				ros::init(argc, argv, "publish_angles", ros::init_options::NoSigintHandler);
			}

			// Listen to the update event. This event is broadcast every
			// simulation iteration.
			this->updateConnection = event::Events::ConnectWorldUpdateBegin(
				std::bind(&ModelPush::OnUpdate, this));

		}

		// Called by the world update start event
	public:
		void OnUpdate()
		{
			float angleDegree = -90;
			float rad = M_PI * angleDegree / 180;

			auto joint1 = "chasis_arm1_joint";
			auto joint2 = "arm1_arm2_joint";
			auto joint3 = "arm2_arm3_joint";
			auto joint4 = "arm3_arm4_joint";

			// Get joint position by index. 
			// 0 returns rotation accross X axis
			// 1 returns rotation accross Y axis
			// 2 returns rotation accross Z axis
			// If the Joint has only Z axis for rotation, 0 returns that value and 1 and 2 return nan
			double a1 = physics::JointState(this->model->GetJoint(joint1)).Position(0);
			double a2 = physics::JointState(this->model->GetJoint(joint2)).Position(0);
			double a3 = physics::JointState(this->model->GetJoint(joint3)).Position(0);
			double a4 = physics::JointState(this->model->GetJoint(joint4)).Position(0);

			arm_gazebo::Angles angles;
			angles.joint1 = a1 * 180.0 / M_PI;
			angles.joint2 = a2 * 180.0 / M_PI;
			angles.joint3 = a3 * 180.0 / M_PI;
			angles.joint4 = a4 * 180.0 / M_PI;

			std::cout << "Current " << joint1 << " values: " << angles.joint1 << std::endl;
			std::cout << "Current " << joint2 << " values: " << angles.joint2 << std::endl;
			std::cout << "Current " << joint3 << " values: " << angles.joint3 << std::endl;
			std::cout << "Current " << joint4 << " values: " << angles.joint4 << std::endl;

			anglePublisher.publish(angles);
		}

		// a pointer that points to a model object
	private:
		physics::ModelPtr model;

		// 	// A joint controller object
		// 	// Takes PID value and apply angular velocity
		// 	//  or sets position of the angles
	private:
		physics::JointControllerPtr jointController;
	
	private:
		ros::Publisher anglePublisher;

	private:
		event::ConnectionPtr updateConnection;

		// // 	// PID object
	private:
		common::PID pid;
	};

	// Register this plugin with the simulator
	GZ_REGISTER_MODEL_PLUGIN(ModelPush)
}
