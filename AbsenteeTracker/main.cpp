/*****************************************************************************************************
*                                      --== Absence Tracker ==--
*                Aplication used to track absences and how many sick days should be payed
*
* Usage: Absence Tracker { PATH_TO_FILE } { START_OF_PERIOD_TO_REPORT } { END_OF_PERIOD_TO_REPORT }
* if start and end of period is not provided first and last available dates are taken by default
* if only start of period is provided last available date is taken by default (as end of period)
*
*****************************************************************************************************/

#include <iostream>

#include "CSVHandler.h"

int main(int argc, char* argv[])
{
	std::string filePath{};
	std::string periodStart{};
	std::string periodEnd{};
	if (argc < 2) {
		std::cout << "Please provide file path: ";
		std::cin >> filePath;
	}
	else {
		filePath = argv[1];

		if (argc > 2) periodStart = argv[2];
		if (argc > 3) periodEnd = argv[3];
	}

	CSVHandler handler = CSVHandler(filePath, periodStart, periodEnd);
	handler.saveEmployeeRecordsToFile();
}