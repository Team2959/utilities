#pragma once

#include <llvm/raw_ostream.h>
#include <memory>
#include "Drive/RobotDriveBase.h"
#include "ctre/Phoenix.h"

class XDrive : public RobotDriveBase
{
 private:
	std::shared_ptr<WPI_TalonSRX> m_frontLeftFrontMotor;
	std::shared_ptr<WPI_TalonSRX> m_frontRightMotor;
	std::shared_ptr<WPI_TalonSRX> m_rearRightMotor;
	std::shared_ptr<WPI_TalonSRX> m_rearLeftMotor;

public:
  XDrive(std::shared_ptr<WPI_TalonSRX> frontLeft,
    std::shared_ptr<WPI_TalonSRX> frontRight,
    std::shared_ptr<WPI_TalonSRX> rearRight,
    std::shared_ptr<WPI_TalonSRX> rearLeft);
  ~XDrive() override = default;

  XDrive(const XDrive&) = delete;
  XDrive& operator=(const XDrive&) = delete;

  void XDriveAbsolute(double frontLeft, double frontRight, double rearRight, double rearLeft);
  void XDriveSpeed(double frontLeft, double frontRight, double rearRight, double rearLeft);

  void StopMotor() override;
  void GetDescription(llvm::raw_ostream& desc) const override;

  void InitSendable(SendableBuilder& builder) override;
};
