#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>


namespace SERP
{
	struct Employee
	{
		using salary_t = float;

		Employee(const std::string& name, 
			const std::string& position, 
			salary_t salary);
		
		const std::string name;
		std::string position;
		salary_t salary;
	};
} // namespace SERP

#endif // EMPLOYEE_H
