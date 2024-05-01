#pragma once
#include "Date.h"


class Absence {
public:
	Date::Date startOfAbsence;
	Date::Date endOfAbsence;
	bool outOfPeriod = false;

	Absence() {}
	Absence(const Date::Date& startOfAbsence, const Date::Date& endOfAbsence)
		: startOfAbsence(startOfAbsence), endOfAbsence(endOfAbsence) {}

	int daysOfAbsence() {
		if (outOfPeriod) return 0;

		int daysOfAbsence{};

		auto time1 = std::chrono::sys_days{ startOfAbsence };
		auto time2 = std::chrono::sys_days{ endOfAbsence };

		// +1 for inclusive count
		daysOfAbsence += (time2 - time1).count() + 1;

		return daysOfAbsence;
	}
};

class AbsenceList {
public:
	std::vector<Absence> absences;

	AbsenceList() {}

	void addAbsence(const Absence& absence) {
		absences.push_back(absence);
	}

	int daysOfAbsences() {
		int daysOfAbsences{};
		for (auto& abs : absences) {
			daysOfAbsences += abs.daysOfAbsence();
		}
		return daysOfAbsences;
	}
};