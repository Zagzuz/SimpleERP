#ifndef	GUI_DIVISIONFORM_H
#define	GUI_DIVISIONFORM_H

#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "form.h"
#include "../base/division.h"
#include "../base/basicmanager.h"


namespace SERP::gui
{
	class DivisionForm : public Form<base::Division>
	{
	public:
		DivisionForm(nana::window wd, UpdateHandler& uhandler);
		virtual void font(const nana::paint::font& f) override;
		virtual void source_object(const ObjT& div) override;
		virtual void save_changes(ObjT& div) override;
		using Form<ObjT>::source_object;
	protected:
		virtual void build() override;
		virtual void init_events() override;
	private:
		nana::label name_{ *this };
		nana::label emps_{ *this };
		nana::label avg_salary_{ *this };
		nana::textbox name_value_{ *this };
		nana::label emps_value_{ *this };
		nana::label avg_salary_value_{ *this };
		nana::button save_{ *this };
	};
} // namespace SERP::gui

#endif // GUI_DIVISIONFORM_H