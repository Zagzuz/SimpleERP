#include "companytree.h"


namespace SERP::gui
{
	CompanyTree::CompanyTree(nana::window wd, UpdateHandler& uhandler) :
		nana::treebox(wd), Elem<ObjT>(uhandler)
	{
		init_events();
	}

	void CompanyTree::build()
	{
		if (!obj_) return;
		typeface(f_);
		auto_draw(false);
		
		auto cmp = [](const auto* lhs, const auto* rhs) { 
			return lhs->name < rhs->name;
		};

		std::set<const base::Division*, decltype(cmp)> divs(cmp);
		std::transform(
			obj_->begin(), obj_->end(),
			std::inserter(divs, divs.begin()),
			[](const base::Division& d) { return &d; }
		);
		
		for (const base::Division* div : divs)
		{
			auto div_node = insert(div->name, div->name);
			div_node.value(div);

			std::set<const base::Employee*, decltype(cmp)> emps(cmp);
			std::transform(
				div->employees.begin(), div->employees.end(), 
				std::inserter(emps, emps.begin()),
				[](const base::Employee& e) { return &e; }
			);
			
			for (const base::Employee* emp : emps)
				auto emp_node = div_node.append(emp->name, emp->name, emp);
		}
		auto_draw(true);
	}

	void CompanyTree::replace_division(const std::string& div, const std::string& new_div)
	{
		auto_draw(false);
		find(div).key(new_div).text(new_div);
		auto_draw(true);
	}

	void CompanyTree::replace_employee(const std::string& emp, const std::string& div, const std::string& new_emp)
	{
		auto_draw(false);
		item_proxy div_node = find(div);
		item_proxy emp_node = std::find_if(div_node.begin(), div_node.end(), 
			[&emp](const item_proxy& item) { return item.text() == emp; });
		emp_node.key(new_emp).text(new_emp);
		auto_draw(true);
	}

	void CompanyTree::save_changes(ObjT& obj)
	{
	}

	void CompanyTree::rebuild()
	{
		if (!obj_) return;
		clear();
		build();
	}

	void CompanyTree::init_events()
	{
		events().selected([this](const nana::arg_treebox& tb_msg) {
			if (!tb_msg.operated) return;
			if (tb_msg.item.level() == 1)
				uhandler_->handle_update(Update::ShowDivisionForm);
			else if (tb_msg.item.level() == 2)
				uhandler_->handle_update(Update::ShowEmployeeForm);
			}
		);
	}

	void CompanyTree::insert_division(const base::Division& div)
	{
		auto div_node = insert(div.name, div.name);
		div_node.value(&div);
		for (auto& emp : div.employees)
			auto emp_node = div_node.append(emp.name, emp.name, &emp);
	}

	void CompanyTree::insert_employee(const base::Employee& emp, const base::Division& div)
	{
		find(div.name).append(emp.name, emp.name, &emp);
	}
} // namespace SERP::gui