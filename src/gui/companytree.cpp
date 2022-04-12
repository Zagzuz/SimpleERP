#include "companytree.h"


namespace SERP::gui
{
	CompanyTree::CompanyTree(nana::window wd, UpdateHandler& uhandler) :
		nana::treebox(wd), uhandler_(&uhandler)
	{
		init_events();
	}

	void CompanyTree::set_divisions(base::BasicManager::div_container_t& divisions)
	{
		divisions_ = &divisions;
	}

	void CompanyTree::set_font(nana::paint::font f)
	{
		f_ = f;
	}

	void CompanyTree::build()
	{
		if (!divisions_) return;
		typeface(f_);
		auto node = insert("Departments", "Departments");
		node.value(&divisions_);
		for (auto& div : *divisions_)
		{
			auto div_node = node.append(div.name, div.name, &div);
			for (const base::Employee& emp : div.employees)
			{
				auto emp_node = div_node.append(emp.name, emp.name, &emp);
			}
		}
	}

	void CompanyTree::rebuild()
	{
		if (!divisions_) return;
		erase("Departments");
		build();
	}

	void CompanyTree::init_events()
	{
		events().selected([this](const nana::arg_treebox& tb_msg) {
			if (!tb_msg.operated) return;
			if (tb_msg.item.level() == 2)
				uhandler_->handle_update(Update::ShowDivisionForm);
			else if (tb_msg.item.level() == 3)
				uhandler_->handle_update(Update::ShowEmployeeForm);
			}
		);
	}
} // namespace SERP::gui