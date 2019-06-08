#include "DmsDegree.h"

double CDmsDegree::getDecimalFormat() {
	int sign = mDegrees < 0 ? -1 : 1;
	double degs = abs(mDegrees) + ((mSeconds / 60.0) + mMinutes) / 60.0;
	return degs * sign;
}
