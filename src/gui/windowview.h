#ifndef GUI_WINDOWVIEW_H
#define GUI_WINDOWVIEW_H

#include <nana/gui.hpp>

#include "companytree.h"
#include "divisionform.h"
#include "employeeform.h"
#include "updatehandler.h"


namespace SERP::gui
{
	class WindowView : public nana::form, public UpdateHandler
	{
	public:
		WindowView(unsigned w = 960, unsigned h = 540);
		virtual void window_show();
	protected:
		nana::place layout_;
		nana::paint::font normal_;
		CompanyTree tree_;
		DivisionForm dform_;
		EmployeeForm eform_;
	};
} // namespace SERP::gui

#endif // GUI_WINDOWVIEW_H