/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <array>


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
#include <Drive/DifferentialDrive.h>

class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
		for (std::size_t i = 0; i < arrX.size(); i++) {
			arrX[i] = 0.0;
			arrY[i] = 0.0;
		}
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
		double limit = m_joystick.GetRawAxis(3) + 1.0;
		double speedY = m_joystick.GetY();
		double speedX = m_joystick.GetX();


		arrX = pushAndPop(arrX, speedX);
		arrY = pushAndPop(arrY, speedY);

		speedX = average(arrX);
		speedY= average(arrY);



		m_robotDrive.ArcadeDrive(limit * 0.5 * speedY,limit * 0.5 * speedX);
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


	frc::DifferentialDrive m_robotDrive{m_left, m_right};

	std::array< double, 5> arrX;
	std::array< double, 5> arrY;

	std::array<double, 5> pushAndPop(std::array<double, 5> arr, double value ) {

			for(std::size_t i = 1; i < arr.size(); i++) {
				arr[i] = arr[i-1];
			}
			arr[0] = value;

			return arr;
		}

	double average(std::array<double, 5> arr) {
		double sum = 0.0;
		 for (std::size_t i = 0; i < arr.size(); i++) {
		        sum += arr[i];
		    }

		    return sum / arr.size();
	}




};

START_ROBOT_CLASS(Robot)
