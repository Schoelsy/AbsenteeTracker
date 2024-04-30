#pragma once
#include <vector>
#include <fstream>

#include "Employee.h"
#include "Date.h"


// Reads employee data from a CSV file and updates the database.
// Parameters:
//   - file: Input file stream.
//   - delimiter: Character used to separate columns.
// Returns:
//   - true if an employee record was successfully read, false otherwise.
class CSVHandler {
	std::vector<Employee> employeeRecords;
	std::ifstream file;

	void parseEmployeeFromLine(std::stringstream& ss, Employee& employee, const char delimiter) {
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
				break;
			}
		}
	}

	void parseAbsenceFromLine(std::stringstream& ss, Absence& absence, const std::string& peselId, const char delimiter,
		const std::string& periodStart, const std::string& periodEnd) {
		std::string cell;
		int counter{ 0u };
		if (periodStart.empty()) {
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
		}
		else if (periodEnd.empty()) {
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
			auto periodDate = Date::convertDateStringToChronoDate(periodStart);
			if (absence.startOfAbsence < periodDate && absence.endOfAbsence > periodDate) absence.startOfAbsence = periodDate;
			else if (absence.endOfAbsence < periodDate) absence.startOfAbsence = absence.endOfAbsence;
		}
		else {
			absence.startOfAbsence = Date::convertDateStringToChronoDate(periodStart);
			absence.endOfAbsence = Date::convertDateStringToChronoDate(periodEnd);
		}
	}

	bool getNextEmployeeFromFile(const char delimiter, const std::string& periodStart,
			const std::string& periodEnd) {
		std::string line;
		if (std::getline(file, line)) {
			std::stringstream ss(line);
			Employee employee;
			Absence absence;

			parseEmployeeFromLine(ss, employee, delimiter);
			parseAbsenceFromLine(ss, absence, employee.peselId, delimiter, periodStart, periodEnd);
			auto result = std::find_if(employeeRecords.begin(), employeeRecords.end(), [&employee](const auto& e) { return employee.peselId == e.peselId; });
			if (result != employeeRecords.end()) {
				result->addAbsence(absence);  // jakim chujem jak tu zawolam na liscie to sie cos innego wgl dzieje, a nie jednak nie
			}
			else {
				employee.addAbsence(absence);
				employeeRecords.push_back(employee);  // to tutaj czemu kolejnosc jest wazna
			}
			return true;
		}
		return false;
	}

public:
	CSVHandler(const std::string& filePath, const std::string& periodStart,
			const std::string& periodEnd, const char delimiter = ';') {
		openFile(filePath);
		while (getNextEmployeeFromFile(delimiter, periodStart, periodEnd)) {}
	}

	void openFile(const std::string& filePath) {
		file.open(filePath);
		if (!file.is_open()) {
			throw std::runtime_error("Error opening file.");
		}
	}

	void saveEmployeeRecordsToFile(const std::string& filePath = "employeeRecords.txt") {
		std::ofstream outfile(filePath);
		if (outfile.is_open()) {
			for (auto& er : employeeRecords) {
				outfile << er.employeeFormatForReport() << std::endl;
			}
			outfile.close();
		}
	}

	const std::vector<Employee>& getEmployeeRecords() {
		return employeeRecords;
	}
};