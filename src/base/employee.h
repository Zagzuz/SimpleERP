#ifndef BASE_EMPLOYEE_H
#define BASE_EMPLOYEE_H

#include <string>


namespace SERP::base
{
	struct Division;

	struct Employee
	{
		using salary_t = float;

		Employee(const std::string& name, 
			const std::string& position, 
			salary_t salary);
		Employee(const std::string& first_name, 
			const std::string& middle_name,
			const std::string& last_name,
			const std::string& position, 
			salary_t salary);
		std::string first_name() const;
		std::string middle_name() const;
		std::string last_name() const;
		static std::string full_name(const std::string& first_name,
			const std::string& middle_name,
			const std::string& last_name);

		std::string name;
		std::string position;
		salary_t salary;
		const Division* division_ = nullptr;
	};
} // namespace SERP::base

#endif // BASE_EMPLOYEE_H
