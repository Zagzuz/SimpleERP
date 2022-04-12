#ifndef	GUI_COMPANYTREE_H
#define	GUI_COMPANYTREE_H

#include "elem.h"
#include "../base/basicmanager.h"

#include <nana/gui/widgets/treebox.hpp>


namespace SERP::gui
{
	class CompanyTree : public nana::treebox, 
		public Elem<base::BasicManager::div_container_t>
	{
	public:
		CompanyTree(nana::window wd, UpdateHandler& uhandler);
		virtual void build() override;
		virtual void save_changes(ObjT& obj) override;
		void rebuild();
	protected:
		virtual void init_events() override;
	};
} // namespace SERP::gui

#endif // GUI_COMPANYTREE_H