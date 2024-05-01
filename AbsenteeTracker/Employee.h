#pragma once
#include <chrono>

#include "Absence.h"

class Employee {
	int currentAge() const;

	// Should be expanded if raport will be generated for multiple years
	int ageInAbsencePeriod() const;
	bool turnFiftyThisYear();
	bool turnFiftyInAbsenceYear();

public:
	std::string name;
	std::string surname;
	std::string peselId;
	Date::Date birthday;
	char gender;
	AbsenceList absenceList;

	Employee() {}
	Employee(const std::string& name, const std::string& surname,
		const std::string& peselId, const std::string& birthday, const std::string& gender);

	void addAbsence(const Absence& absence);

	// returns amounts of sick pay days in format: pair of "Wynagrodzenie chorobowe" and "Zasi³ek chorobowy"
	std::pair<int, int> calculateCompensation();
	std::string employeeFormatForReport(const char delimeter = ';');
};