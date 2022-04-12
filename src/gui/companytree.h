#ifndef	GUI_COMPANYTREE_H
#define	GUI_COMPANYTREE_H

#include "elem.h"
#include "../base/basicmanager.h"

#include <nana/gui/widgets/treebox.hpp>
#include <set>


namespace SERP::gui
{
	class CompanyTree : public nana::treebox, 
		public Elem<base::BasicManager::div_container_t>
	{
	public:
		CompanyTree(nana::window wd, UpdateHandler& uhandler);
		virtual void save_changes(ObjT& obj) override;
		virtual void build() override;
		void rebuild();
		void replace_division(const std::string& div, const std::string& new_div);
		void replace_employee(const std::string& emp, const std::string& div, const std::string& new_div);
	protected:
		virtual void init_events() override;
	private:
		void insert_division(const base::Division& div);
		void insert_employee(const base::Employee& emp, const base::Division& div);
	};
} // namespace SERP::gui

#endif // GUI_COMPANYTREE_H