#include "companytree.h"
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
		auto node = insert("Departments", "Departments");
		node.value(&obj_);
		for (auto& div : *obj_)
		{
			auto div_node = node.append(div.name, div.name, &div);
			for (const base::Employee& emp : div.employees)
			{
				auto emp_node = div_node.append(emp.name, emp.name, &emp);
			}
		}
	}

	void CompanyTree::save_changes(ObjT& obj)
	{
	}

	void CompanyTree::rebuild()
	{
		if (!obj_) return;
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