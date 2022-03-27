#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>


namespace SERP
{
	struct Employee
	{
		using salary_t = float;

		Employee(const std::string& name, const std::string& position, salary_t salary);
		Employee(const std::string& first_name, 
			const std::string& middle_name,
			const std::string& last_name,
			const std::string& position, 
			salary_t salary);
		std::string first_name() const;
		std::string middle_name() const;
		std::string last_name() const;

		const std::string name;
		std::string position;
		salary_t salary;
	};
} // namespace SERP

#endif // EMPLOYEE_H
