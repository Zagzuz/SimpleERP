#ifndef	GUI_EMPLOYEEFORM_H
#define	GUI_EMPLOYEEFORM_H

#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "../base/employee.h"
#include "form.h"


namespace SERP::gui
{
	class EmployeeForm : public Form<base::Employee>
	{
	public:
		EmployeeForm(nana::window wd, UpdateHandler& uhandler);
		virtual void font(const nana::paint::font& f) override;
		virtual void save_changes(ObjT& emp) override;
		virtual void source_object(const ObjT& emp) override;
		using Form<ObjT>::source_object;
	protected:
		virtual void build() override;
		virtual void init_events() override;
	private:
		nana::label fname_{ *this };
		nana::label mname_{ *this };
		nana::label lname_{ *this };
		nana::label pos_{ *this };
		nana::label salary_{ *this };
		nana::textbox fname_value_{ *this };
		nana::textbox mname_value_{ *this };
		nana::textbox lname_value_{ *this };
		nana::textbox pos_value_{ *this };
		nana::textbox salary_value_{ *this };
		nana::button save_{ *this };
	};
} // namespace SERP::gui

#endif // GUI_EMPLOYEEFORM_H