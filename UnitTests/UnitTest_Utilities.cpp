#include "CppUnitTest.h"

#include "Utilities.h"
#include "DmsDegree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest_Utilities)
	{
	public:
		
		TEST_METHOD(TestCelsius2Fahrenheit)
		{			
			static const double DELTA = 0.000001;
			Assert::AreEqual(32.0, CUtilities::Celsius2Fahrenheit(0.0), DELTA);

			Assert::AreEqual(33.8, CUtilities::Celsius2Fahrenheit(1.0), DELTA);
			Assert::AreEqual(35.6, CUtilities::Celsius2Fahrenheit(2.0), DELTA);
			Assert::AreEqual(39.2, CUtilities::Celsius2Fahrenheit(4.0), DELTA);

			Assert::AreEqual(3'632.0, CUtilities::Celsius2Fahrenheit(2'000.0), DELTA);

			Assert::AreEqual(30.2, CUtilities::Celsius2Fahrenheit(-1.0), DELTA);
			Assert::AreEqual(28.4, CUtilities::Celsius2Fahrenheit(-2.0), DELTA);
			Assert::AreEqual(24.8, CUtilities::Celsius2Fahrenheit(-4.0), DELTA);
		}

		TEST_METHOD(TestFahrenheit2Celsius)
		{
			static const double DELTA = 0.000001;
			Assert::AreEqual(0.0, CUtilities::Fahrenheit2Celsius(32.0), DELTA);

			Assert::AreEqual(1.0, CUtilities::Fahrenheit2Celsius(33.8), DELTA);
			Assert::AreEqual(2.0, CUtilities::Fahrenheit2Celsius(35.6), DELTA);
			Assert::AreEqual(4.0, CUtilities::Fahrenheit2Celsius(39.2), DELTA);

			Assert::AreEqual(2'000.0, CUtilities::Fahrenheit2Celsius(3'632.0), DELTA);

			Assert::AreEqual(-1.0, CUtilities::Fahrenheit2Celsius(30.2), DELTA);
			Assert::AreEqual(-2.0, CUtilities::Fahrenheit2Celsius(28.4), DELTA);
			Assert::AreEqual(-4.0, CUtilities::Fahrenheit2Celsius(24.8), DELTA);
		}

		TEST_METHOD(TestCelsius2Kelvin) 
		{
			static const double DELTA = 0.000001;
			Assert::AreEqual(0.0, CUtilities::Celsius2Kelvin(-273.15));
		}

		TEST_METHOD(TestKelvin2Celsius)
		{
			static const double DELTA = 0.000001;
			Assert::AreEqual(0.0, CUtilities::Kelvin2Celsius(273.15));
			Assert::AreEqual(-273.15, CUtilities::Kelvin2Celsius(0.0));
		}

	};

	TEST_CLASS(UnitTest_DmsDegrees) {
	public:

		TEST_METHOD(TestDms)
		{
			static const double DELTA = 0.000001;
			{
				CDmsDegree dms(10, 25, 11);
				Assert::AreEqual(dms.getDecimalFormat(), 10.419722, DELTA);
        Assert::AreEqual(10.0, dms.getDegrees(), DELTA);
        Assert::AreEqual(25.0, dms.getMinutes(), DELTA);
        Assert::AreEqual(11.0, dms.getSeconds(), DELTA);
        Assert::AreEqual(std::string("10°25´11´´"), dms.getDmsFormatString());
			}
			
			CDmsDegree dms(13.0, 4.0, 10.0);
			Assert::AreEqual(dms.getDecimalFormat(), 13.069444, DELTA);
      Assert::AreEqual(13.0, dms.getDegrees(), DELTA);
      Assert::AreEqual(4.0, dms.getMinutes(), DELTA);
      Assert::AreEqual(10.0, dms.getSeconds(), DELTA);
      Assert::AreEqual(std::string("13°4´10´´"), dms.getDmsFormatString());

      dms.setDegrees(300.0);
      dms.setMinutes(20.0);
      dms.setSeconds(0.0);
							
			Assert::AreEqual(dms.getDecimalFormat(), 300.333333, DELTA);
      Assert::AreEqual(300.0, dms.getDegrees(), DELTA);
      Assert::AreEqual(20.0, dms.getMinutes(), DELTA);
      Assert::AreEqual(0.0, dms.getSeconds(), DELTA);
      Assert::AreEqual(std::string("300°20´0´´"), dms.getDmsFormatString());
				
		}
	};
}