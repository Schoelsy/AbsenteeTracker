#pragma once
#include <chrono>

namespace Date {
	using Date = std::chrono::year_month_day;

	Date convertDateStringToChronoDate(const std::string& str);
	Date get_current_date();
};