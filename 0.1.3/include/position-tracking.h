#pragma once

namespace positionTracking{
  void positionTracking();

  double getX();
  double getY();
  double getTheta();

  double getThetaWrapped(bool range = true);
}