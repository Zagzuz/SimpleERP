#ifndef	BASE_BASICMANAGER_H
#define BASE_BASICMANAGER_H

#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

#include "employee.h"
#include "division.h"


namespace SERP::base
{
	class BasicManager
	{
	public:
		using salary_t = Employee::salary_t;

		BasicManager() = default;
		const Division& create_division(const std::string& name);
		void delete_division(const std::string& name);
		void rename_division(const std::string& name, const std::string& new_name);
		void add_employee(const std::string& division_name, Employee e);
		void change_salary(const std::string& employee_name, salary_t new_salary, const std::string& division_name = "");
		void change_position(const std::string& employee_name, const std::string& new_position, const std::string& division_name = "");
		void dismiss_employee(const std::string& employee_name, const std::string& division_name = "");
		const Employee* find_employee(const std::string& employee_name, const std::string& division_name = "") const;
		const Division* find_division(const std::string& division_name) const;
		std::vector<const Division*> get_divisions() const;
		std::vector<const Employee*> get_employees(const std::string& division_name) const;
		using div_member_t = member<Division, std::string, &Division::name>;
		using div_container_t = multi_index_container<Division, indexed_by<hashed_unique<div_member_t>>>;
	private:
		using div_it_t = div_container_t::iterator;
		using emp_it_t = Division::emp_container_t::iterator;

		struct DivEmpIt
		{
			DivEmpIt(div_it_t div_it, emp_it_t emp_it) :
				div_it(div_it), emp_it(emp_it), valid(true) {}
			div_it_t div_it;
			emp_it_t emp_it;
			bool is_valid() const { return valid; }
			static DivEmpIt invalid() { return DivEmpIt(false); }
		private:
			explicit DivEmpIt(bool valid) : valid(valid) {}
			bool valid;
		};

		DivEmpIt find_employee_it(const std::string& employee_name, const std::string& division_name = "") const;
		template <class Callable> void modify_employee(div_it_t div_it, emp_it_t emp_it, Callable mod);
	protected:
		div_container_t divisions_;
	};
	
	template<class Callable>
	inline void BasicManager::modify_employee(div_it_t div_it, emp_it_t emp_it, Callable mod)
	{
		divisions_.modify(div_it,
			[&emp_it, &mod](Division& d) {
				d.employees.modify(emp_it,
					[&mod](Employee& e) {
						mod(e);
					}
				);
			}
		);
	}
} // namespace SERP::base

#endif // BASE_BASICMANAGER_H
