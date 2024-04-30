#pragma once
#include "Date.h"


class Absence {
public:
	Date::Date startOfAbsence;
	Date::Date endOfAbsence;

	Absence() {}
	Absence(const Date::Date& startOfAbsence, const Date::Date& endOfAbsence)
		: startOfAbsence(startOfAbsence), endOfAbsence(endOfAbsence) {}

	int daysOfAbsence(const Date::Date& periodStart, const Date::Date& periodEnd) {
		int daysOfAbsence{};

		if ((startOfAbsence < periodStart && endOfAbsence < periodStart) ||
			(startOfAbsence > periodEnd)) return 0;

		if (startOfAbsence < periodStart && endOfAbsence < periodEnd) {
			auto time1 = std::chrono::sys_days{ periodStart };
			auto time2 = std::chrono::sys_days{ endOfAbsence };

			daysOfAbsence += (time2 - time1).count() + 1;

			return daysOfAbsence;
		}

		if (startOfAbsence < periodStart && endOfAbsence > periodEnd) {
			auto time1 = std::chrono::sys_days{ periodStart };
			auto time2 = std::chrono::sys_days{ periodEnd };

			daysOfAbsence += (time2 - time1).count() + 1;

			return daysOfAbsence;
		}

		if (startOfAbsence > periodStart && endOfAbsence > periodEnd) {
			auto time1 = std::chrono::sys_days{ startOfAbsence };
			auto time2 = std::chrono::sys_days{ periodEnd };

			daysOfAbsence += (time2 - time1).count() + 1;

			return daysOfAbsence;
		}

		if (startOfAbsence > periodStart && endOfAbsence < periodEnd) {
			auto time1 = std::chrono::sys_days{ startOfAbsence };
			auto time2 = std::chrono::sys_days{ endOfAbsence };

			daysOfAbsence += (time2 - time1).count() + 1;

			return daysOfAbsence;
		}
	}
};

class AbsenceList {
public:
	std::vector<Absence> absences;

	AbsenceList() {}

	void addAbsence(const Absence& absence) {
		absences.push_back(absence);
	}

	int daysOfAbsences(const Date::Date& periodStart, const Date::Date& periodEnd) {
		int daysOfAbsences{};
		for (auto& abs : absences) {
			daysOfAbsences += abs.daysOfAbsence(periodStart, periodEnd);
		}
		return daysOfAbsences;
	}
};