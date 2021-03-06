#include "basicmanager.h"


namespace SERP::base
{
	const Division& BasicManager::create_division(const std::string& name)
	{
		auto [it, b] = divisions_.emplace(name);
		if (!b)
		{
			throw std::runtime_error("divisions_.emplace() "
				"failed in BasicManager::create_division()");
		}
		return *it;
	}

	void BasicManager::delete_division(const std::string& name)
	{
		divisions_.erase(name);
	}
	
	void BasicManager::rename_division(const std::string& name, const std::string& new_name)
	{
		auto it = divisions_.find(name);
		if (it == divisions_.end())
		{
			// division not found
			return;
		}
		divisions_.modify_key(it,
			[&new_name](std::string& key) { key = new_name; }
		);
	}

	void BasicManager::add_employee(const std::string& division_name, Employee e)
	{
		auto div_it = divisions_.find(division_name);
		if (div_it == divisions_.end())
		{
			// division not found
			return;
		}
		e.division_ = &*div_it;
		divisions_.modify(div_it,
			[&e](Division& d) {
				d.employees.insert(std::move(e));
				d.count_employees();
				d.calculate_avg_salary();
			}
		);
	}

	void BasicManager::change_salary(const std::string& employee_name, salary_t new_salary, const std::string& division_name)
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

	void BasicManager::change_position(const std::string& employee_name, const std::string& new_position, const std::string& division_name)
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

	void BasicManager::dismiss_employee(const std::string& employee_name, const std::string& division_name)
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

	const Employee* BasicManager::find_employee(const std::string& employee_name, const std::string& division_name) const
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

	const Division* BasicManager::find_division(const std::string& division_name) const
	{
		auto it = divisions_.find(division_name);
		return it == divisions_.end() ? &*it : nullptr;
	}

	std::vector<const Division*> BasicManager::get_divisions() const
	{
		std::vector<const Division*> names;
		std::transform(divisions_.begin(), divisions_.end(),
			std::back_inserter(names), [](const Division& d) { return &d; });
		return names;
	}

	std::vector<const Employee*> BasicManager::get_employees(const std::string& division_name) const
	{
		auto it = divisions_.find(division_name);
		if (it == divisions_.end())
		{
			// division not found
		}
		std::vector<const Employee*> names;
		std::transform(it->employees.begin(), it->employees.end(),
			std::back_inserter(names), [](const Employee& e) { return &e; });
		return names;
	}

	BasicManager::DivEmpIt BasicManager::find_employee_it(const std::string& employee_name, const std::string& division_name) const
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
} // namespace SERP::base
