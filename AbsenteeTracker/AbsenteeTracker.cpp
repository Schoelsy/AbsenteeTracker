/**************************************************************************
*                        --== Absence Tracker ==--
* Aplication used to track absences and how many sick days should be payed
*
* Usage: Absentee_Tracker { PATH_TO_FILE }
*
**************************************************************************/

#include <iostream>

#include "CSVHandler.h"


int main(int argc, char* argv[])
{
	std::string filePath{};
	if (argc < 2) {
		std::cout << "Please provide file path: ";
		std::cin >> filePath;
	}
	else {
		filePath = argv[1];
	}
	//auto filePath = "C:\\Users\\Scholes\\Downloads\\input.csv";
	std::cout << "DUPA " << filePath << std::endl;
	CSVHandler reader = CSVHandler(filePath);
	auto db = reader.getEmployeeRecords();

	for (auto& em : db) {
		std::cout << "Employee: " << em.name << std::endl;
		auto comp = em.calculateCompensation();
		std::cout << "Compensation - Wynagrodzenie: " << comp.first << " Zasilek: " << comp.second << std::endl;
		std::cout << "Absences: " << std::endl;
		for (auto& abs : em.absenceList.absences) {
			std::cout << "From: " << abs.startOfAbsence << " to: " << abs.endOfAbsence << std::endl;
		}

		std::cout << std::endl;
	}

	for (auto& em : db) {
		std::cout << em.employeeFormatForReport() << std::endl;
	}
}