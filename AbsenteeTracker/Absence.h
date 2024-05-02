#pragma once
#include "Date.h"

struct Absence {
	Date::Date startOfAbsence;
	Date::Date endOfAbsence;
	bool outOfPeriod = false;

	Absence() {}
	Absence(const Date::Date& startOfAbsence, const Date::Date& endOfAbsence);

	int daysOfAbsence() const;
};

struct AbsenceList {
	std::vector<Absence> absences;

	AbsenceList() {}

	void addAbsence(const Absence& absence);
	int daysOfAbsences() const;
	Date::Date getAbsencesDate() const;
};