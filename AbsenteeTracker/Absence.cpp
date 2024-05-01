#include "Absence.h"

// Absence
Absence::Absence(const Date::Date& startOfAbsence, const Date::Date& endOfAbsence) 
	: startOfAbsence(startOfAbsence), endOfAbsence(endOfAbsence) {}

int Absence::daysOfAbsence() const {
	if (outOfPeriod) return 0;

	int daysOfAbsence{};

	auto time1 = std::chrono::sys_days{ startOfAbsence };
	auto time2 = std::chrono::sys_days{ endOfAbsence };

	// +1 for inclusive count
	daysOfAbsence += (time2 - time1).count() + 1;

	return daysOfAbsence;
}


// AbsenceList
void AbsenceList::addAbsence(const Absence& absence) {
	absences.push_back(absence);
}

int AbsenceList::daysOfAbsences() const {
	int daysOfAbsences{};
	for (auto& abs : absences) {
		daysOfAbsences += abs.daysOfAbsence();
	}
	return daysOfAbsences;
}

Date::Date AbsenceList::getAbsencesDate() const {
	Date::Date date{};
	for (auto& abs : absences) {
		if (date < abs.endOfAbsence) date = abs.endOfAbsence;
	}
	return date;
}