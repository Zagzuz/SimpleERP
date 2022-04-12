#include "windowview.h"


namespace SERP::gui
{
	WindowView::WindowView(unsigned w, unsigned h) :
		nana::form(nana::API::make_center(w, h)),
		layout_(*this),
		tree_(*this, *this),
		dform_(*this, *this),
		eform_(*this, *this),
		normal_("Segoe UI", 14.0)
	{
		nana::API::track_window_size(*this, { 800, 600 }, false);
		caption("SimpleERP");
		icon(nana::paint::image("SimpleERP.png"));
		layout_.div("<<min=20% tree> | 60% <switchable min=50% <dform><eform>>>");
		dform_.font(normal_);
		eform_.font(normal_);
		tree_.set_font(normal_);
	}

	void WindowView::window_show()
	{
		show();
		nana::exec();
	}
} // namespace SERP::gui