#include "manager.h"


namespace SERP
{
    Manager::Manager(std::size_t new_capacity) :
        Stateful(new_capacity),
        gui::WindowView() {}

    void Manager::add(const std::string& filename)
    {
        pt::ptree tree;
        pt::read_xml(filename, tree);
        load_tree(tree);
    }

    void Manager::load(const std::string& filename)
    {
        dissolve_divisions();
        add(filename);
    }

    void Manager::save(const std::string& filename, std::size_t indent_count)
    {
        pt::write_xml(filename, make_tree(), std::locale(),
            pt::xml_writer_make_settings<std::string>(' ', indent_count));
    }

    void Manager::save_state()
    {
        if (!get_state_capacity()) return;
        if (states_.size() == get_state_capacity())
        {
            states_.pop_front();
        }
        if (cur_state_ + 1 < states_.size())
        {
            states_.erase(
                std::next(states_.begin(), cur_state_ + 1),
                states_.end()
            );
        }
        std::ostringstream oss;
        pt::write_xml(oss, make_tree());
        states_.push_back(oss.str());
        cur_state_ = states_.size() - 1;
    }

    void Manager::load_state(std::size_t index)
    {
        pt::ptree t;
        std::istringstream iss(states_[index]);
        pt::read_xml(iss, t);
        dissolve_divisions();
        load_tree(t);
    }

    void Manager::dissolve_divisions()
    {
        divisions_.clear();
    }

    bool Manager::handle_update(gui::Update upd)
    {
        if (upd == gui::Update::DivisionUpdate)
        {
            const std::string div_name = dform_.source_object().name;
            divisions_.modify(divisions_.find(div_name),
                [this](base::Division& div) {
                    dform_.save_changes(div);
                }
            );
            layout_.field_display("dform", false);
            tree_.replace_division(div_name, dform_.source_object().name);
            return true;
        }
        if (upd == gui::Update::EmployeeUpdate)
        {
            const std::string& div_name = eform_.source_object().division_->name;
            const std::string emp_name = eform_.source_object().name;
            auto div_it = divisions_.find(div_name);
            auto emp_it = div_it->employees.find(emp_name);
            divisions_.modify(div_it,
                [this, &emp_it](base::Division& div) {
                    div.employees.modify(emp_it,
                        [this](base::Employee& emp) {
                            eform_.save_changes(emp);
                        }
                    );
                }
            );
            layout_.field_display("eform", false);
            tree_.replace_employee(emp_name, div_name, eform_.source_object().name);
            return true;
        }
        if (upd == gui::Update::ShowDivisionForm)
        {
            dform_.source_object(*tree_.selected().value<const base::Division*>());
            layout_.field_display("eform", false);
            layout_.field_display("dform", true);
            layout_.collocate();
            return true;
        }
        if (upd == gui::Update::ShowEmployeeForm)
        {
            eform_.source_object(*tree_.selected().value<const base::Employee*>());
            layout_.field_display("dform", false);
            layout_.field_display("eform", true);
            layout_.collocate();
            return true;
        }
        return false;
    }

    void Manager::window_show()
    {
        tree_.source_object(divisions_);
        tree_.build();
        layout_["tree"] << tree_;
        layout_["dform"] << dform_;
        layout_["eform"] << eform_;
        layout_.field_display("dform", false);
        layout_.field_display("eform", false);
        layout_.collocate();
        show();
        nana::exec();
    }

    void Manager::load_tree(const pt::ptree& t)
    {
        for (auto& dep : t.get_child("departments"))
        {
            auto div_name = dep.second.get<std::string>("<xmlattr>.name");
            const base::Division& div = create_division(div_name);
            for (auto& emp : dep.second.get_child("employments"))
            {
                base::Employee e(
                    emp.second.get_child("name").data(),
                    emp.second.get_child("middleName").data(),
                    emp.second.get_child("surname").data(),
                    emp.second.get_child("function").data(),
                    salary_t(::atof(emp.second.get_child("salary").data().c_str()))
                );
                add_employee(div_name, e);
            }
        }
    }

    pt::ptree Manager::make_tree() const
    {
        pt::ptree t;
        for (const base::Division& dep : divisions_)
        {
            pt::ptree tdep;
            for (const base::Employee& emp : dep.employees)
            {
                pt::ptree edep;
                edep.add("surname", emp.last_name());
                edep.add("name", emp.first_name());
                edep.add("middleName", emp.middle_name());
                edep.add("function", emp.position);
                edep.add("salary", emp.salary);
                tdep.add_child("employments.employment", edep);
            }
            tdep.add("<xmlattr>.name", dep.name);
            t.add_child("departments.department", tdep);
        }
        return t;
    }
} // namespace SERP
