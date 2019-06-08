#pragma once
class CUtilities 
{	

public:
	CUtilities();
	~CUtilities();

	static constexpr double Fahrenheit2Celsius(const double f) {
		return (5.0 / 9.0)*(f - 32.0);
	}

	static constexpr double Celsius2Fahrenheit(const double c) {
		return 32.0 + (9.0 / 5.0)*c;
	}

	static constexpr double Celsius2Kelvin(const double c) {
		return c + 273.15;
	}

	static constexpr double Kelvin2Celsius(const double k) {
		return k - 273.15;
	}

};