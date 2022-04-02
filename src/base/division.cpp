#include "division.h"


namespace SERP::base
{
	Division::Division(const std::string& name) : name(name) {}

	void Division::calculate_avg_salary()
	{
		avg_salary = employees.empty() ? static_cast<salary_t>(0) :
			std::accumulate(employees.begin(), employees.end(), static_cast<salary_t>(0),
				[](salary_t salary, const Employee& e) { return salary + e.salary; }) / employees.size();
	}

	void Division::count_employees()
	{
		n_employees = employees.size();
	}

} // namespace SERP::base
