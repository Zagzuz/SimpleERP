#include "divisionform.h"


namespace SERP::gui
{
	DivisionForm::DivisionForm(nana::window wd, UpdateHandler& uhandler) :
		Form<ObjT>(wd, uhandler)
	{
		init_events();
	}

	void DivisionForm::source_object(const ObjT& div)
	{
		obj_ = &div;
		name_value_.caption(obj_->name);
		emps_value_.caption(std::to_string(obj_->n_employees));
		std::stringstream sstream;
		sstream.setf(std::ios::fixed);
		sstream.precision(2);
		sstream << obj_->avg_salary;
		avg_salary_value_.caption(sstream.str());
		save_.enabled(false);
	}

	void DivisionForm::build()
	{
		layout_.div(
			"<vert margin=10% weight=60% <><>"
			"<<name_lbl> <nameval_txt>> <>"
			"<<emps_lbl> <empsval_lbl>> <>"
			"<<aver_lbl> <averval_lbl>> <>"
			"<save_btn>"
			"<><> >"
		);

		name_.caption("Division name: ");
		name_.typeface(f_);
		name_.text_align(nana::align::right, nana::align_v::center);
		layout_["name_lbl"] << name_;

		emps_.caption("Employees: ");
		emps_.typeface(f_);
		emps_.text_align(nana::align::right, nana::align_v::center);
		layout_["emps_lbl"] << emps_;

		avg_salary_.caption("Average salary: ");
		avg_salary_.text_align(nana::align::right, nana::align_v::center);
		avg_salary_.typeface(f_);
		layout_["aver_lbl"] << avg_salary_;

		name_value_.multi_lines(false);
		name_value_.text_align(nana::align::left);
		name_value_.typeface(f_);
		layout_["nameval_txt"] << name_value_;

		emps_value_.text_align(nana::align::left, nana::align_v::center);
		emps_value_.typeface(f_);
		layout_["empsval_lbl"] << emps_value_;

		avg_salary_value_.text_align(nana::align::left, nana::align_v::center);
		avg_salary_value_.typeface(f_);
		layout_["averval_lbl"] << avg_salary_value_;

		save_.caption("Save changes");
		save_.typeface(f_);
		layout_["save_btn"] << save_;

		layout_.collocate();
	}

	void SERP::gui::DivisionForm::save_changes(ObjT& div)
	{
		div.name = name_value_.text();
	}

	void DivisionForm::init_events()
	{
		name_value_.events().text_changed(
			[this]() { this->save_.enabled(true); });
		save_.events().click(
			[this]() {
				save_.enabled(false);
				uhandler_->handle_update(Update::DivisionUpdate);
			}
		);
	}
} // namespace SERP::gui