#include "employeeform.h"


namespace SERP::gui
{
	EmployeeForm::EmployeeForm(nana::window wd, UpdateHandler& uhandler) : 
		Form<ObjT>(wd, uhandler)
	{
		init_events();
	}

	void EmployeeForm::source_object(const ObjT& emp)
	{
		obj_ = &emp;
		fname_value_.caption(obj_->first_name());
		mname_value_.caption(obj_->middle_name());
		lname_value_.caption(obj_->last_name());
		pos_value_.caption(obj_->position);
		std::stringstream sstream;
		sstream.setf(std::ios::fixed);
		sstream.precision(2);
		sstream << obj_->salary;
		salary_value_.caption(sstream.str());
		save_.enabled(false);
	}

	void EmployeeForm::build()
	{
		layout_.div(
			"<vert margin=10% weight=60% <><>"
			"<<fname_lbl> <fnameval_txt>> <>"
			"<<mname_lbl> <mnameval_txt>> <>"
			"<<lname_lbl> <lnameval_txt>> <>"
			"<<pos_lbl> <posval_txt>> <>"
			"<<sal_lbl> <salval_txt>> <>"
			"<save_btn>"
			"<><> >"
		);

		fname_.caption("First name: ");
		fname_.typeface(f_);
		fname_.text_align(nana::align::right, nana::align_v::center);
		layout_["fname_lbl"] << fname_;

		mname_.caption("Middle name: ");
		mname_.typeface(f_);
		mname_.text_align(nana::align::right, nana::align_v::center);
		layout_["mname_lbl"] << mname_;

		lname_.caption("Last name: ");
		lname_.typeface(f_);
		lname_.text_align(nana::align::right, nana::align_v::center);
		layout_["lname_lbl"] << lname_;

		pos_.caption("Position: ");
		pos_.typeface(f_);
		pos_.text_align(nana::align::right, nana::align_v::center);
		layout_["pos_lbl"] << pos_;

		salary_.caption("Salary: ");
		salary_.text_align(nana::align::right, nana::align_v::center);
		salary_.typeface(f_);
		layout_["sal_lbl"] << salary_;

		fname_value_.multi_lines(false);
		fname_value_.text_align(nana::align::left);
		fname_value_.typeface(f_);
		layout_["fnameval_txt"] << fname_value_;

		mname_value_.multi_lines(false);
		mname_value_.text_align(nana::align::left);
		mname_value_.typeface(f_);
		layout_["mnameval_txt"] << mname_value_;

		lname_value_.multi_lines(false);
		lname_value_.text_align(nana::align::left);
		lname_value_.typeface(f_);
		layout_["lnameval_txt"] << lname_value_;

		pos_value_.multi_lines(false);
		pos_value_.text_align(nana::align::left);
		pos_value_.typeface(f_);
		layout_["posval_txt"] << pos_value_;

		salary_value_.multi_lines(false);
		salary_value_.text_align(nana::align::left);
		salary_value_.typeface(f_);
		layout_["salval_txt"] << salary_value_;

		save_.caption("Save changes");
		save_.typeface(f_);
		layout_["save_btn"] << save_;

		layout_.collocate();
	}

	void EmployeeForm::save_changes(ObjT& emp)
	{
		if (fname_value_.edited() ||
			mname_value_.edited() ||
			lname_value_.edited())
		{
			emp.name = base::Employee::full_name(fname_value_.text(),
				mname_value_.text(), lname_value_.text());
		}
		if (pos_value_.edited())
		{
			emp.position = pos_value_.text();
		}
		if (salary_value_.edited())
		{
			emp.salary = salary_value_.to_double();
		}
	}

	void EmployeeForm::init_events()
	{
		static auto enable_save = [this]() { save_.enabled(true); };
		pos_value_.events().text_changed(enable_save);
		fname_value_.events().text_changed(enable_save);
		mname_value_.events().text_changed(enable_save);
		lname_value_.events().text_changed(enable_save);
		salary_value_.events().text_changed(enable_save);
		save_.events().click([this]() {
				save_.enabled(false);
				uhandler_->handle_update(Update::EmployeeUpdate);
			}
		);
	}
} // namespace SERP::gui