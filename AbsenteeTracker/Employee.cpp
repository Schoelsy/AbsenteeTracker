#include "Employee.h"

Employee::Employee(const std::string& name, const std::string& surname,
	const std::string& peselId, const std::string& birthday, const std::string& gender)
	: name(name), surname(surname), peselId(peselId), gender(gender[0]) {
	this->birthday = Date::convertDateStringToChronoDate(birthday);
}

void Employee::addAbsence(const Absence& absence) {
	absenceList.addAbsence(absence);
}

std::pair<int, int> Employee::calculateCompensation() {
	constexpr int borderAge{ 50 };
	constexpr int borderDaysForYoung{ 33 };
	constexpr int borderDaysForOld{ 14 };

	int daysOfAbsence = absenceList.daysOfAbsences();

	if (ageInAbsencePeriod() < borderAge || turnFiftyInAbsenceYear()) {
		if (daysOfAbsence > borderDaysForYoung)
			return { borderDaysForYoung,  daysOfAbsence - borderDaysForYoung };
		else
			return { daysOfAbsence, 0 };
	}
	else {
		if (daysOfAbsence > borderDaysForOld)
			return { borderDaysForOld,  daysOfAbsence - borderDaysForOld };
		else
			return { daysOfAbsence, 0 };
	}
}

std::string Employee::employeeFormatForReport(const char delimeter) {
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

int Employee::currentAge() const {
	using namespace std::chrono;

	auto currentDate = Date::get_current_date();
	int currentAge = static_cast<int>(currentDate.year()) - static_cast<int>(birthday.year());

	if (currentDate.month() < birthday.month() || (currentDate.month() == birthday.month() && currentDate.day() < birthday.day())) {
		currentAge--;
	}

	return currentAge;
}

int Employee::ageInAbsencePeriod() const {
	using namespace std::chrono;

	auto absenceDate = absenceList.getAbsencesDate();
	int absenceAge = static_cast<int>(absenceDate.year()) - static_cast<int>(birthday.year());

	if (absenceDate.month() < birthday.month() || (absenceDate.month() == birthday.month() && absenceDate.day() < birthday.day())) {
		absenceAge--;
	}

	return absenceAge;
}

bool Employee::turnFiftyThisYear() {
	const auto currentDate = Date::get_current_date();
	int resultYear = static_cast<int>(currentDate.year()) - static_cast<int>(birthday.year());

	return (currentAge() == 50) && (resultYear == 50);
}

bool Employee::turnFiftyInAbsenceYear() {
	auto absenceDate = absenceList.getAbsencesDate();
	int resultYear = static_cast<int>(absenceDate.year()) - static_cast<int>(birthday.year());

	return (ageInAbsencePeriod() == 50) && (resultYear == 50);
}
