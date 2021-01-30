#include "XDrive.h"

//#include <HAL/HAL.h>

#include "SmartDashboard/SendableBuilder.h"

/**
 * Construct a XDrive.
 */
XDrive::XDrive(std::shared_ptr<WPI_TalonSRX> frontLeft,
    std::shared_ptr<WPI_TalonSRX> frontRight,
    std::shared_ptr<WPI_TalonSRX> rearRight,
    std::shared_ptr<WPI_TalonSRX> rearLeft)
{
    m_frontLeftFrontMotor = frontLeft;
    m_frontRightMotor = frontRight;
    m_rearRightMotor = rearRight;
    m_rearLeftMotor = rearLeft;

    AddChild(m_frontLeftFrontMotor);
    AddChild(m_frontRightMotor);
    AddChild(m_rearRightMotor);
    AddChild(m_rearLeftMotor);

    static int instances = 0;
    ++instances;
    SetName("XDrive", instances);
}

void XDrive::XDriveAbsolute(double frontLeft, double frontRight, double rearRight, double rearLeft)
{
/*  static bool reported = false;
  if (!reported) {
    HAL_Report(HALUsageReporting::kResourceType_RobotDrive, 2,
               HALUsageReporting::kRobotDrive_Tank);
    reported = true;
  }*/
    m_frontLeftFrontMotor->Set(frontLeft);
    m_frontRightMotor->Set(frontRight);
    m_rearRightMotor->Set(rearRight);
    m_rearLeftMotor->Set(rearLeft);

    m_safetyHelper.Feed();
}

void XDrive::XDriveSpeed(double frontLeft, double frontRight, double rearRight, double rearLeft)
{
    m_frontLeftFrontMotor->Set(ControlMode::Velocity, frontLeft);
    m_frontRightMotor->Set(ControlMode::Velocity, frontRight);
    m_rearRightMotor->Set(ControlMode::Velocity, rearRight);
    m_rearLeftMotor->Set(ControlMode::Velocity, rearLeft);

    m_safetyHelper.Feed();
}

void XDrive::StopMotor()
{
    m_frontLeftFrontMotor->StopMotor();
    m_frontRightMotor->StopMotor();
    m_rearRightMotor->StopMotor();
    m_rearLeftMotor->StopMotor();

    m_safetyHelper.Feed();
}

void XDrive::GetDescription(llvm::raw_ostream& desc) const
{
    desc << "XlDrive";
}

void XDrive::InitSendable(SendableBuilder& builder)
{
  builder.SetSmartDashboardType("XDrive");
  builder.AddDoubleProperty("Left Front Motor Speed",
                            [=]() { return m_FrontLeftMotor->Get(); },
                            [=](double value) { m_FrontLeftMotor->Set(value); });
  builder.AddDoubleProperty("Right Front Motor Speed",
                            [=]() { return m_FrontRightMotor->Get(); },
                            [=](double value) { m_FrontRightMotor->Set(value); });
  builder.AddDoubleProperty("Right Rear Motor Speed",
                            [=]() { return m_BackRightMotor->Get(); },
                            [=](double value) { m_BackRightMotor->Set(value); });
  builder.AddDoubleProperty("Left Rear Motor Speed",
                            [=]() { return m_BackLeftMotor->Get(); },
                            [=](double value) { m_BackLeftMotor->Set(value); });
}
