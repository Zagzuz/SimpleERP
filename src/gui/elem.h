#ifndef GUI_ELEM_H
#define GUI_ELEM_H

#include "updatehandler.h"
#include <nana/gui.hpp>


namespace SERP::gui
{
	template <class T>
	class Elem
	{
	public:
		using ObjT = T;
		Elem(UpdateHandler& uhandler);
		virtual void font(const nana::paint::font& f);
		const nana::paint::font& font() const;
		virtual void source_object(const T& obj);
		const T& source_object() const;
		virtual void build() = 0;
		virtual void save_changes(ObjT& obj) = 0;
	protected:
		virtual void init_events() = 0;

		nana::paint::font f_{};
		const T* obj_ = nullptr;
		UpdateHandler* uhandler_ = nullptr;
	};

	template <class T>
	Elem<T>::Elem(UpdateHandler& uhandler) : uhandler_(&uhandler) {}

	template <class T>
	inline void Elem<T>::font(const nana::paint::font& f)
	{
		f_ = f;
	}

	template <class T>
	inline const nana::paint::font& Elem<T>::font() const
	{
		return f_;
	}

	template <class T>
	inline void Elem<T>::source_object(const T& obj)
	{
		obj_ = &obj;
	}

	template <class T>
	inline const T& Elem<T>::source_object() const
	{
		return *obj_;
	}
} // namespace SERP::gui

#endif // GUI_ELEM_H
