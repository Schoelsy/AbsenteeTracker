#pragma once
#include "Date.h"

class Absence {
public:
	Date::Date startOfAbsence;
	Date::Date endOfAbsence;
	bool outOfPeriod = false;

	Absence() {}
	Absence(const Date::Date& startOfAbsence, const Date::Date& endOfAbsence);

	int daysOfAbsence() const;
};

class AbsenceList {
public:
	std::vector<Absence> absences;

	AbsenceList() {}

	void addAbsence(const Absence& absence);
	int daysOfAbsences() const;
	Date::Date getAbsencesDate() const;
};