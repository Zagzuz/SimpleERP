#ifndef GUI_WINDOWVIEW_H
#define GUI_WINDOWVIEW_H

#include <nana/gui.hpp>
#include <nana/gui/widgets/treebox.hpp>


namespace SERP::gui
{
	class WindowView
	{
	public:
		virtual void show() = 0;
	};
} // namespace SERP::gui

#endif // GUI_WINDOWVIEW_H