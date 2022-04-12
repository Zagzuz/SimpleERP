#ifndef GUI_FORM_H
#define GUI_FORM_H

#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/place.hpp>

#include "elem.h"


namespace SERP::gui
{
	template <class T>
	class Form : public Elem<T>, public nana::panel<false>
	{
	public:
		using Elem<T>::ObjT;
		Form(nana::window wd, UpdateHandler& uhandler);
	protected:
		nana::place layout_;
	};

	template <class T>
	Form<T>::Form(nana::window wd, UpdateHandler& uhandler) :
		Elem<T>(uhandler), nana::panel<false>(wd), layout_(*this) {}
} // namespace SERP::gui

#endif // GUI_FORM_H
