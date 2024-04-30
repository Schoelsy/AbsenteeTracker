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

	CSVHandler reader = CSVHandler(filePath);
	reader.saveEmployeeRecordsToFile();
}