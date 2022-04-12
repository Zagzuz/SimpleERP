#ifndef	GUI_COMPANYTREE_H
#define	GUI_COMPANYTREE_H

#include "updatehandler.h"
#include "../base/basicmanager.h"

#include <nana/gui/widgets/treebox.hpp>


namespace SERP::gui
{
	class CompanyTree : public nana::treebox
	{
	public:
		CompanyTree(nana::window wd, UpdateHandler& uhandler);
		void set_divisions(base::BasicManager::div_container_t& divisions);
		void set_font(nana::paint::font f);
		void build();
		void rebuild();
	private:
		void init_events();
		nana::paint::font f_{};
		base::BasicManager::div_container_t* divisions_ = nullptr;
		UpdateHandler* uhandler_ = nullptr;
	};
} // namespace SERP::gui

#endif // GUI_COMPANYTREE_H