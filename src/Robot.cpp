/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Joystick.h>
#include <Buttons/JoystickButton.h>
#include <Spark.h>
#include <Timer.h>
#include <DoubleSolenoid.h>
#include <RobotDrive.h>
#include <GenericHID.h>


class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
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
		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString(
		// 		"Auto Selector", kAutoNameDefault);
		std::cout << "Auto selected: " << m_autoSelected << std::endl;

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {



	}

	void TeleopPeriodic() {
		m_robotDrive.ArcadeDrive(m_joystick.GetY(), m_joystick.GetX());
		m_lift.Set(m_controller.GetRawAxis(5));
		if (m_controller.GetRawButton(6)) {
		p_lift.Set(frc::DoubleSolenoid::kForward);
		} else if (m_controller.GetRawButton(7)) {
		p_lift.Set(frc::DoubleSolenoid::kReverse);
		}
		m_intake.Set(m_controller.GetRawAxis(3));


	}

	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;

	frc::Joystick m_joystick{0};
	frc::JoystickButton j_12{&m_joystick, 12};
	frc::Joystick m_controller{1};
	frc::JoystickButton c_6{&m_controller, 6};
	frc::DoubleSolenoid p_lift{1, 2};

	frc::Spark m_left{1};
	frc::Spark m_right{2};
	frc::Spark m_lift{3};
	frc::Spark m_intake{4};


	frc::RobotDrive m_robotDrive{m_left, m_right};


};

START_ROBOT_CLASS(Robot)
