#include "tmanager.h"


namespace SERP
{
    TManager::TManager(std::size_t state_capacity) : state_cap_(state_capacity)
    {
        cur_state_ = 0;
        if (!state_cap_) return;
    }

    void TManager::add(const std::string& filename)
    {
        pt::ptree tree;
        pt::read_xml(filename, tree);
        load_tree(tree);
    }

    void TManager::load(const std::string& filename)
    {
        clear();
        add(filename);
    }

    void TManager::save(const std::string& filename, std::size_t indent_count)
    {
        pt::write_xml(filename, make_tree(), std::locale(),
            pt::xml_writer_make_settings<std::string>(' ', indent_count));
    }

    void TManager::save_state()
    {
        if (!state_cap_) return;
        std::ostringstream oss;
        pt::write_xml(oss, make_tree());
        if (state_cap_ == state_vec_.size())
        {
            state_vec_.pop_front();
        }
        if (cur_state_ + 1 < state_vec_.size())
        {
            state_vec_.erase(
                std::next(state_vec_.begin(), cur_state_ + 1),
                state_vec_.end()
            );
        }
        state_vec_.push_back(oss.str());
        cur_state_ = state_vec_.size() - 1;
    }

    void TManager::load_state(std::size_t steps, Direction d)
    {
        if (!steps || !state_cap_)
        {
            return;
        }
        else if (d == BACKWARD && steps > cur_state_ ||
            d == FORWARD && cur_state_ + steps >= state_cap_)
        {
            // too far away
            return;
        }
        pt::ptree t;
        cur_state_ = d == BACKWARD ? 
            cur_state_ - steps : 
            cur_state_ + steps;
        std::istringstream iss(state_vec_[cur_state_]);
        pt::read_xml(iss, t);
        clear();
        load_tree(t);
    }

    bool SERP::TManager::undo()
    {
        if (cur_state_ == 0) 
            return false;
        load_state(1, BACKWARD);
        return true;
    }

    bool SERP::TManager::redo()
    {
        if (cur_state_ == state_vec_.size() - 1)
            return false;
        load_state(1, FORWARD);
        return true;
    }

    void SERP::TManager::set_state_capacity(std::size_t n)
    {
        if (!n)
        {
            state_vec_.clear();
            cur_state_ = 0;
        }
        else if (state_cap_ > n)
        {
            bool enough_space = state_cap_ - n > state_cap_ - cur_state_ + 1;
            std::size_t i, j;
            if (enough_space)
            {
                i = state_cap_ - n;
                j = state_cap_;
                cur_state_ -= i;
            }
            else
            {
                i = cur_state_;
                j = cur_state_ + state_cap_ - n;
                cur_state_ = 0;
            }
            state_vec_.erase(state_vec_.begin(), std::next(state_vec_.begin(), i));
            state_vec_.erase(std::next(state_vec_.begin(), j), state_vec_.end());
        }
        state_cap_ = n;
    }

    std::size_t TManager::get_state_capacity() const
    {
        return state_cap_;
    }

    void TManager::clear()
    {
        divisions_.clear();
    }

    void TManager::load_tree(const pt::ptree& t)
    {
        for (auto& dep : t.get_child("departments"))
        {
            auto div_name = dep.second.get<std::string>("<xmlattr>.name");
            create_division(div_name);
            for (auto& emp : dep.second.get_child("employments"))
            {
                Employee e(
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

    pt::ptree TManager::make_tree() const
    {
        pt::ptree t;
        for (const Division& dep : divisions_)
        {
            pt::ptree tdep;
            for (const Employee& emp : dep.employees)
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
