#pragma once

namespace positionTracking{
  void positionTracking();

  double getX();
  double getY();
  double getTheta();

  double getThetaLocal(bool range = false);
}