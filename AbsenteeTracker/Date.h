#pragma once
#include <chrono>


namespace Date {
	using Date = std::chrono::year_month_day;

	Date convertDateStringToChronoDate(const std::string& str) {
		std::istringstream ss(str);
		std::string temp;
		std::vector<std::string> dateParts;

		while (std::getline(ss, temp, '.')) {
			dateParts.push_back(temp);
		}

		if (dateParts.size() != 3) {
			throw std::invalid_argument("Invalid date format. Expected format: dd.mm.yyyy");
		}

		int day = std::stoi(dateParts[0]);
		int month = std::stoi(dateParts[1]);
		int year = std::stoi(dateParts[2]);

		return Date(std::chrono::year(year), std::chrono::month(month), std::chrono::day(day));
	}

	Date get_current_date() {  
		using namespace std::chrono;
		auto now = zoned_time{ current_zone(), system_clock::now() }.get_local_time();
		return year_month_day({ time_point_cast<days>(now) });
	}
};