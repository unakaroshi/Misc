#pragma once

#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>

class CDmsDegree
{
private:	
	double mDegrees = 0.0;
	double mMinutes = 0.0;
	double mSeconds = 0.0;

public:
	CDmsDegree() { }

	CDmsDegree(double degrees, double minutes, double seconds)
		: mDegrees(degrees)
		, mMinutes(minutes)
		, mSeconds(seconds)
	{

	}

	~CDmsDegree() {}

	double getDecimalFormat();

  std::string getDmsFormatString() const {
    std::stringstream sstream;
    sstream << mDegrees << "°" << mMinutes << "´" << mSeconds << "´´";
    return sstream.str();
  }

	double getDegrees() const { return mDegrees; }	
	double getMinutes() const { return mMinutes; }	
	double getSeconds() const { return mSeconds; }

  void setDegrees(double value) { mDegrees = value; }
  void setMinutes(double value) { mMinutes = value; }
  void setSeconds(double value) { mSeconds = value; }

  void setDms(double degrees, double minutes, double seconds) {
    setDegrees(degrees);
    setMinutes(minutes);
    setSeconds(seconds);
  }

  double setDegreesVal(double degrees);

       
};

