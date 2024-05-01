#include "CSVHandler.h"

#include <vector>

void CSVHandler::parseEmployeeFromLine(std::stringstream& ss, Employee& employee) {
	std::string cell;
	int counter{ 0u };
	while (std::getline(ss, cell, delimiter)) {
		switch (counter++) {
		case 0:
			employee.name = cell;
			break;
		case 1:
			employee.surname = cell;
			break;
		case 2:
			employee.peselId = cell;
			break;
		case 3:
			employee.birthday = Date::convertDateStringToChronoDate(cell);
			break;
		case 4:
			employee.gender = cell[0];
			return;
		}
	}
}

void CSVHandler::parseAbsenceFromLine(std::stringstream& ss, Absence& absence, const std::string& peselId,
	const std::string& periodStart, const std::string& periodEnd) {
	std::string cell;
	int counter{ 0u };
	while (std::getline(ss, cell, delimiter)) {
		switch (counter++) {
		case 0:
			absence.startOfAbsence = Date::convertDateStringToChronoDate(cell);
			break;
		case 1:
			absence.endOfAbsence = Date::convertDateStringToChronoDate(cell);
			break;
		}
	}
	if (periodStart.empty()) {
		return;
	}
	else if (periodEnd.empty()) {
		auto periodDate = Date::convertDateStringToChronoDate(periodStart);
		if (absence.startOfAbsence <= periodDate && absence.endOfAbsence >= periodDate) absence.startOfAbsence = periodDate;
		else if (absence.endOfAbsence < periodDate) absence.outOfPeriod = true;
	}
	else {
		auto startDate = Date::convertDateStringToChronoDate(periodStart);
		auto endDate = Date::convertDateStringToChronoDate(periodEnd);
		if (absence.endOfAbsence < startDate || absence.startOfAbsence > endDate) absence.outOfPeriod = true;
		else if (absence.startOfAbsence <= startDate && absence.endOfAbsence >= endDate) {
			absence.startOfAbsence = startDate;
			absence.endOfAbsence = endDate;
		}
		else if (absence.startOfAbsence > startDate && absence.endOfAbsence > endDate) {
			absence.endOfAbsence = endDate;
		}
		else if (absence.startOfAbsence < startDate && absence.endOfAbsence < endDate) {
			absence.startOfAbsence = startDate;
		}
	}
}

bool CSVHandler::getNextEmployeeFromFile(const std::string& periodStart, const std::string& periodEnd) {
	std::string line;
	if (std::getline(file, line)) {
		std::stringstream ss(line);
		Employee employee;
		Absence absence;

		parseEmployeeFromLine(ss, employee);
		parseAbsenceFromLine(ss, absence, employee.peselId, periodStart, periodEnd);
		auto result = std::find_if(employeeRecords.begin(), employeeRecords.end(),
			[&employee](const auto& e) { return employee.peselId == e.peselId; });
		if (result != employeeRecords.end()) {
			result->addAbsence(absence);
		}
		else {
			employee.addAbsence(absence);
			employeeRecords.push_back(employee);
		}
		return true;
	}
	return false;
}

CSVHandler::CSVHandler(const std::string& filePath, const std::string& periodStart,
	const std::string& periodEnd, const char delimiter) {
	openFile(filePath);
	this->delimiter = delimiter;
	while (getNextEmployeeFromFile(periodStart, periodEnd)) {}
}

void CSVHandler::openFile(const std::string& filePath) {
	file.open(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file.");
	}
}

void CSVHandler::saveEmployeeRecordsToFile(const std::string& filePath) {
	std::ofstream outfile(filePath);
	if (outfile.is_open()) {
		for (auto& er : employeeRecords) {
			outfile << er.employeeFormatForReport() << std::endl;
		}
		outfile.close();
	}
}

const std::vector<Employee>& CSVHandler::getEmployeeRecords() {
	return employeeRecords;
}