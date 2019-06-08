#pragma once

#include <cstdlib>
#include <string>
#include <sstream>
//#include <math>

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

  std::string getDmsFormatString() {
    std::stringstream sstream;
    sstream << mDegrees << "°" << mMinutes << "´" << mSeconds << "´´";
    return sstream.str();
  }

	double getDegrees() { return mDegrees; }	
	double getMinutes() { return mMinutes; }	
	double getSeconds() { return mSeconds; }

  void setDegrees(double value) { mDegrees = value; }
  void setMinutes(double value) { mMinutes = value; }
  void setSeconds(double value) { mSeconds = value; }
       
};

