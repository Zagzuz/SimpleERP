#ifndef GUI_FORM_H
#define GUI_FORM_H

#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/place.hpp>

#include "updatehandler.h"


namespace SERP::gui
{
	template <class T>
	class Form : public nana::panel<false>
	{
	public:
		using ObjT = T;
		Form(nana::window wd, UpdateHandler& uhandler);
		void font(const nana::paint::font& f);
		const nana::paint::font& font() const;
		virtual void source_object(const T& obj);
		const T& source_object() const;
		virtual void build() = 0;
		virtual void save_changes(ObjT& obj) = 0;
	protected:
		virtual void init_events() = 0;

		nana::place layout_{ *this };
		nana::paint::font f_{};
		const T* obj_ = nullptr;
		UpdateHandler* uhandler_ = nullptr;
	};

	template <class T>
	Form<T>::Form(nana::window wd, UpdateHandler& uhandler) :
		nana::panel<false>(wd), layout_(*this), uhandler_(&uhandler) {}

	template <class T>
	inline void Form<T>::font(const nana::paint::font& f)
	{
		f_ = f;
	}

	template <class T>
	inline const nana::paint::font& Form<T>::font() const
	{
		return f_;
	}

	template <class T>
	inline void Form<T>::source_object(const T& obj)
	{
		obj_ = &obj;
	}

	template <class T>
	inline const T& Form<T>::source_object() const
	{
		return *obj_;
	}
} // namespace SERP::gui

#endif // GUI_FORM_H
