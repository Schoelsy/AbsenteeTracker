#include "pch.h"
#include <gtest/gtest.h>
#include "../AbsenteeTracker/Employee.cpp"
#include "../AbsenteeTracker/Absence.cpp"
#include "../AbsenteeTracker/Date.cpp"

class EmployeeTest : public ::testing::Test {
protected:
	Employee employee;
	EmployeeTest() : employee("Name", "Surname", "123", "01.01.1993", "M") {}
};

TEST_F(EmployeeTest, ShouldHaveGenderM) {
	EXPECT_EQ(employee.gender, 'M');
}

TEST_F(EmployeeTest, ShouldProduceCorrectReport) {
	using namespace std::chrono;
	auto abs1 = Absence(year_month_day(2024y, February, 1d), year_month_day(2024y, February, 10d));
	auto abs2 = Absence(year_month_day(2023y, December, 10d), year_month_day(2023y, December, 19d));
	employee.addAbsence(abs1);
	employee.addAbsence(abs2);
	EXPECT_EQ(employee.employeeFormatForReport(), "Name;Surname;123;01.01.1993;M;31;20;20;0");
}

TEST_F(EmployeeTest, ShouldProduceCorrectReport_EmployeeTurned50ThisYear) {
	using namespace std::chrono;

	employee.birthday = year_month_day(1974y, March, 1d);

	auto abs1 = Absence(year_month_day(2024y, February, 1d), year_month_day(2024y, February, 10d));
	auto abs2 = Absence(year_month_day(2023y, December, 10d), year_month_day(2023y, December, 19d));
	employee.addAbsence(abs1);
	employee.addAbsence(abs2);
	EXPECT_EQ(employee.employeeFormatForReport(), "Name;Surname;123;01.03.1974;M;50;20;20;0");
}

TEST_F(EmployeeTest, ShouldProduceCorrectReport_EmployeeTurned50LastYear) {
	using namespace std::chrono;

	employee.birthday = year_month_day(1973y, December, 1d);

	auto abs1 = Absence(year_month_day(2024y, February, 1d), year_month_day(2024y, February, 10d));
	auto abs2 = Absence(year_month_day(2023y, December, 10d), year_month_day(2023y, December, 19d));
	employee.addAbsence(abs1);
	employee.addAbsence(abs2);
	EXPECT_EQ(employee.employeeFormatForReport(), "Name;Surname;123;01.12.1973;M;50;20;14;6");
}
