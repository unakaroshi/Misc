#include "DmsDegree.h"

double CDmsDegree::getDecimalFormat() {
	int sign = mDegrees < 0 ? -1 : 1;
	double degs = abs(mDegrees) + ((mSeconds / 60.0) + mMinutes) / 60.0;
	return degs * sign;
}


double CDmsDegree::setDegreesVal(double degrees) {
  int sign = degrees < 0 ? -1 : 1;

  double dummy;

  double deg = abs(degrees);


  int _degrees = static_cast<int>(deg);

  int _minutes = static_cast<int>(60 * modf(deg, &dummy));

  double _seconds = 60 * modf(60 * modf(deg, &dummy), &dummy);

  if (_degrees > 0) {
    _degrees = _degrees * sign;
  }
  else {
    _degrees = _degrees * -1;
  }
  setDms(_degrees, _minutes, _seconds);
  return getDecimalFormat();
}

