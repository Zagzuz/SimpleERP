#include "manager.h"


namespace SERP
{
	void Manager::create_division(const std::string& name)
	{
		divisions_.emplace(name);
	}

	void Manager::delete_division(const std::string& name)
	{
		divisions_.erase(name);
	}
	
	void Manager::add_employee(const std::string& division_name, const Employee& e)
	{
		auto div_it = divisions_.find(division_name);
		if (div_it == divisions_.end())
		{
			// division not found
			return;
		}
		divisions_.modify(div_it,
			[&e](Division& d) {
				d.employees.insert(e);
				d.count_employees();
				d.calculate_avg_salary();
			}
		);
	}

	void Manager::change_salary(const std::string& employee_name, salary_t new_salary, const std::string& division_name)
	{
		auto res = find_employee_it(employee_name, division_name);
		if (!res.is_valid())
		{
			// either division or employee not found
			return;
		}
		modify_employee(res.div_it, res.emp_it,
			[&new_salary](Employee& e) { e.salary = new_salary; }
		);
		divisions_.modify(res.div_it, [](Division& d) {
			d.calculate_avg_salary(); }
		);
	}

	void Manager::change_position(const std::string& employee_name, const std::string& new_position, const std::string& division_name)
	{
		auto res = find_employee_it(employee_name, division_name);
		if (!res.is_valid())
		{
			// either division or employee not found
			return;
		}
		modify_employee(res.div_it, res.emp_it,
			[&new_position](Employee& e) { e.position = new_position; }
		);
	}

	void Manager::dismiss_employee(const std::string& employee_name, const std::string& division_name)
	{
		auto res = find_employee_it(employee_name, division_name);
		if (!res.is_valid())
		{
			// either division or employee not found
			return;
		}
		divisions_.modify(res.div_it,
			[&](Division& d) {
				d.employees.erase(res.emp_it);
				d.count_employees();
				d.calculate_avg_salary();
			}
		);
	}

	const Employee* Manager::find_employee(const std::string& employee_name, const std::string& division_name) const
	{
		auto div_it = !division_name.empty() ?
			// O(1) with hint
			divisions_.find(division_name) :
			// O(N) without hint
			std::find_if(divisions_.cbegin(), divisions_.cend(),
				[employee_name](const Division& d) {
					return d.employees.contains(employee_name); });
		if (div_it == divisions_.end()) return nullptr;
		auto it = div_it->employees.find(employee_name);
		if (it == div_it->employees.end()) return nullptr;
		return &*it;
	}

	Manager::DivEmpIt Manager::find_employee_it(const std::string& employee_name, const std::string& division_name) const
	{
		auto div_it = !division_name.empty() ?
			// O(1) with hint
			divisions_.find(division_name) :
			// O(N) without hint
			std::find_if(divisions_.cbegin(), divisions_.cend(),
				[employee_name](const Division& d) {
					return d.employees.contains(employee_name); });
		if (div_it == divisions_.end()) return DivEmpIt::invalid();
		auto it = div_it->employees.find(employee_name);
		if (it == div_it->employees.end()) return DivEmpIt::invalid();
		return { div_it, it };
	}
} // namespace SERP
