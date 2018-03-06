/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <array>
#include <thread>


#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Joystick.h>
#include <Buttons/JoystickButton.h>
#include <Spark.h>
#include <Victor.h>
#include <Timer.h>
#include <DoubleSolenoid.h>
#include <RobotDrive.h>
#include <GenericHID.h>
#include <Drive/DifferentialDrive.h>


#include <CameraServer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "WPILib.h"
#include "ctre/Phoenix.h"

using namespace frc;

class Robot : public IterativeRobot {



	Talon *m_intakeRight;
	Talon *m_intakeLeft;
//	Spark *rightBack;
//	Spark *rightFront;
//	Spark *leftFront;
//	Spark *leftBack;

//	SpeedControllerGroup *left;
//	SpeedControllerGroup *right;
//
//	DifferentialDrive *drivetrain;


public:



	Joystick rightJoystick;
	Joystick leftJoystick;
	Joystick controller;



//	DigitalInput limitSwitchUp;
//	DigitalInput limitSwitchDown;

	TalonSRX m_intakeBack;
	TalonSRX m_lift;

	frc::Spark rightBack{1};
		frc::Spark leftBack{3};
		frc::Spark rightFront{0};
		frc::Spark leftFront{2};

//
//	  frc::SpeedControllerGroup m_left{leftFront, leftBack};
//
//	  frc::SpeedControllerGroup m_right{rightFront, rightBack};
//
//	  frc::DifferentialDrive m_drive{m_left, m_right};
//


	Robot():
//		limitSwitchUp(0),
//		limitSwitchDown(1),
		leftJoystick(0),
		rightJoystick(1),
		controller(2),
		m_lift(59),
		m_intakeBack(0)

		{

		m_timer.Start();
//		m_drive.SetExpiration(0.1);

		m_intakeRight = new Talon(4);
		m_intakeLeft = new Talon(5);
//		rightBack = new Spark(1);
//		leftBack = new Spark(3);
//		rightFront = new Spark(0);
//		leftFront = new Spark(2);
//
//		right = new SpeedControllerGroup(rightFront, rightBack);
//		left = new SpeedControllerGroup(leftFront, leftBack);
//
//
//		drivetrain = new DifferentialDrive(right, left);

		}


	void RobotInit() {

//		limitSwitchUp = DigitalInput(0);
//		limitSwitchDown = DigitalInput(1);
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		SmartDashboard::PutData("Auto Modes", &m_chooser);


		std::thread visionThread(VisionThread);
		visionThread.detach();

	}

	/*
	 * This autonomous (along with the chooser code above) shows how to
	 * select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to
	 * the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as
	 * well.
	 */
	void AutonomousInit() override {
//		m_timer.Reset();
//		m_timer.Start();
//		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString(
		// 		"Auto Selector", kAutoNameDefault);
		//std::cout << "Auto selected: " << m_autoSelected << std::endl;

//		if (m_autoSelected == kAutoNameCustom) {
//			// Custom Auto goes here
//		} else {
//			// Default Auto goes here

	//}

		std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
//		if (gameData.length > 0) {
//			if (gameData)
//		}

	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
//			if (m_timer.Get() < 5.0) {
//							m_robotDrive.ArcadeDrive(0.5,0.0);
						//}
		}
	}

	void TeleopInit() {
//		stopWatch = new frc::Timer();
//		stopWatch.Start();

	}

	void TeleopPeriodic() {
//		m_right.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, squareDrive(rightJoystick.GetY()));
//		m_left.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, squareDrive(rightJoystick.GetY()));


//		stopWatch.Delay(0.005);

		//drivetrain.ArcadeDrive(squareDrive(rightJoystick.GetY()),squareDrive(rightJoystick.GetX()));
		//m_robotDrive.TankDrive(m_joystick.GetY(),m_controller.GetY());
		//m_lift.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, squareDrive(leftJoystick.GetRawAxis(5)));




//		DifferentialDrive drivetrain{right, left};
//
//	drivetrain.ArcadeDrive(rightJoystick.GetY(), rightJoystick.GetX());
	rightFront.Set(squareDrive(rightJoystick.GetY()));
	rightBack.Set(squareDrive(rightJoystick.GetY()));

	leftFront.Set(-squareDrive(leftJoystick.GetY()));

	leftBack.Set(-squareDrive(leftJoystick.GetY()));

//
//	rightFront.Set(squareDrive(controller.GetRawAxis(1)));
//		rightBack.Set(squareDrive(controller.GetRawAxis(2)));
//
//		leftFront.Set(squareDrive(controller.GetRawAxis(3)));
//
//		leftBack.Set(squareDrive(controller.GetRawAxis(4)));




		if (controller.GetRawButton(4)) {
		p_lift2.Set(DoubleSolenoid::kReverse);
		} else if (controller.GetRawButton(1)) {
		p_lift2.Set(DoubleSolenoid::kForward);
		} else if (controller.GetRawButton(2)) {
		p_lift.Set(DoubleSolenoid::kForward);
		} else if (controller.GetRawButton(3)) {
		p_lift.Set(DoubleSolenoid::kReverse);
	}

//		while (limitSwitchUp.Get()) {
		m_lift.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, controller.GetRawAxis(1));
		m_intakeBack.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, controller.GetRawAxis(5));
		m_intakeRight->Set(controller.GetRawAxis(5));
		m_intakeLeft->Set(controller.GetRawAxis(5));


		//}

		// intake is 6 on controller
		// outake is 5 on controller

	}

	void TestPeriodic() {

	}

private:

	float squareDrive(float val) {

		if (val > 0.0) {
			val = val*val;
			return val;
		}
		else if (val < 0.0) {
			val = -(val*val);
			return val;
		} else {
			return 0;
		}
	}

	static void VisionThread() {
				// Get the USB camera from CameraServer
				cs::UsbCamera camera =
						CameraServer::GetInstance()
								->StartAutomaticCapture();
				// Set the resolution
				camera.SetResolution(640, 480);

				// Get a CvSink. This will capture Mats from the Camera
				cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
				// Setup a CvSource. This will send images back to the Dashboard
				cs::CvSource outputStream =
						CameraServer::GetInstance()->PutVideo(
								"Rectangle", 640, 480);

				// Mats are very memory expensive. Lets reuse this Mat.
				cv::Mat mat;

				while (true) {
					// Tell the CvSink to grab a frame from the camera and
					// put it
					// in the source mat.  If there is an error notify the
					// output.
					if (cvSink.GrabFrame(mat) == 0) {
						// Send the output the error.
						outputStream.NotifyError(cvSink.GetError());
						// skip the rest of the current iteration
						continue;
					}
					// Put a rectangle on the image
					rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
							cv::Scalar(255, 255, 255), 5);
					// Give the output stream a new image to display
					outputStream.PutFrame(mat);
				}
	}

	LiveWindow& m_lw = *LiveWindow::GetInstance();
	SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;

//	Spark p_lift{2};

//




//	Joystick m_joystick{0};
//	JoystickButton j_12{&m_joystick, 12};
//	Joystick m_controller{1};
//	JoystickButton c_6{&m_controller, 6};
	DoubleSolenoid p_lift{0,1};
	DoubleSolenoid p_lift2{2,3};
	Timer m_timer;









};

START_ROBOT_CLASS(Robot);

