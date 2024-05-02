#pragma once
#include "Employee.h"

#include <fstream>

// Reads employee data from a CSV file and updates the database.
// Parameters:
//   - file: Input file stream.
//   - delimiter: Character used to separate columns.
// Returns:
//   - true if an employee record was successfully read, false otherwise.
class CSVHandler {
public:
	CSVHandler(const std::string& filePath, const std::string& periodStart,
		const std::string& periodEnd, const char delimiter = ';');

	void openFile(const std::string& filePath);
	void saveEmployeeRecordsToFile(const std::string& filePath = "employeeRecords.txt");
	const std::vector<Employee>& getEmployeeRecords();

private:
	void parseEmployeeFromLine(std::stringstream& ss, Employee& employee);
	void parseAbsenceFromLine(std::stringstream& ss, Absence& absence, const std::string& peselId,
		const std::string& periodStart, const std::string& periodEnd);
	bool getNextEmployeeFromFile(const std::string& periodStart, const std::string& periodEnd);

	std::vector<Employee> employeeRecords_;
	std::ifstream file_;
	char delimiter_;
};