#pragma once
#include <chrono>

#include "Date.h"
#include "Absence.h"


class Employee {
	int currentAge() const {
		using namespace std::chrono;

		auto currentDate = Date::get_current_date();
		int currentAge = static_cast<int>(currentDate.year()) - static_cast<int>(birthday.year());

		if (currentDate.month() < birthday.month() || (currentDate.month() == birthday.month() && currentDate.day() < birthday.day())) {
			currentAge--;
		}

		return currentAge;
	}

	bool turnFiftyThisYear() {
		const auto currentDate = Date::get_current_date();
		int res = static_cast<int>(currentDate.year()) - static_cast<int>(birthday.year());
		std::cout << "RESULT: " << res << std::endl;
		return (currentAge() == 50) && (res == 50);
	}

public:
	std::string name;
	std::string surname;
	std::string peselId;
	Date::Date birthday;
	char gender;
	AbsenceList absenceList;

	Employee() {}
	Employee(const std::string& name, const std::string& surname,
		const std::string& peselId, const std::string& birthday, const std::string& gender)
		: name(name), surname(surname), peselId(peselId), gender(gender[0]) {
		this->birthday = Date::convertDateStringToChronoDate(birthday);
	}

	void addAbsence(const Absence& absence) {
		absenceList.addAbsence(absence);
	}

	// returns amounts of sick pay days in format: pair of "Wynagrodzenie chorobowe" and "Zasi³ek chorobowy"
	std::pair<int, int> calculateCompensation() {
		constexpr int borderAge{ 50 };
		constexpr int borderDaysForYoung{ 33 };
		constexpr int borderDaysForOld{ 14 };

		int daysOfAbsence = absenceList.daysOfAbsences();

		if (currentAge() < borderAge || turnFiftyThisYear()) {
			std::cout << "Dupa" << std::endl;
			if (daysOfAbsence > borderDaysForYoung)
				return { borderDaysForYoung,  daysOfAbsence - borderDaysForYoung };
			else
				return { daysOfAbsence, 0 };
		}
		else {
			std::cout << "Guwno" << std::endl;
			if (daysOfAbsence > borderDaysForOld)
				return { borderDaysForOld,  daysOfAbsence - borderDaysForOld };
			else
				return { daysOfAbsence, 0 };
		}
	}

	std::string employeeFormatForReport(const char delimeter = ';') {
		std::stringstream ss;
		auto absenceDays = calculateCompensation();

		ss << name << delimeter
			<< surname << delimeter
			<< peselId << delimeter
			<< birthday.day() << '.' << std::format("{:%m}", birthday.month()) << '.' << birthday.year() << delimeter
			<< gender << delimeter
			<< currentAge() << delimeter
			<< (absenceDays.first + absenceDays.second) << delimeter
			<< absenceDays.first << delimeter
			<< absenceDays.second;

		return ss.str();
	}
};