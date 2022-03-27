#include "employee.h"


namespace SERP
{
	Employee::Employee(const std::string& name, const std::string& position, salary_t salary) :
		name(name), position(position), salary(salary) {}

	Employee::Employee(const std::string& first_name, 
		const std::string& middle_name, 
		const std::string& last_name, 
		const std::string& position, 
		salary_t salary) :
		name(first_name + ' ' + middle_name + ' ' + last_name),
		position(position),
		salary(salary) {}
	
	std::string Employee::first_name() const
	{
		std::size_t i = name.find(' ');
		if (i == -1) return name;
		return name.substr(0, i);
	}

	std::string Employee::middle_name() const
	{
		std::size_t i = name.find(' ');
		if (i == -1) return "";
		std::size_t j = name.find(' ', i + 1);
		if (j == -1) return "";
		return name.substr(i + 1, j - i - 1);
	}

	std::string Employee::last_name() const
	{
		std::size_t i = name.find_last_of(' ');
		if (i == -1) return "";
		return name.substr(i + 1, name.length() - i - 1);
	}
} // namespace SERP
