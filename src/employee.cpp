#include "employee.h"


namespace SERP
{
	Employee::Employee(const std::string& name, const std::string& position, salary_t salary) :
		name(name), position(position), salary(salary) {}
} // namespace SERP
