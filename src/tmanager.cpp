#include "tmanager.h"


namespace SERP
{
	void TManager::load(const std::string& filename)
	{
        pt::ptree tree;
		pt::read_xml(filename, tree);
        for (auto& dep : tree.get_child("departments"))
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

	void TManager::save(const std::string& filename)
	{
        pt::ptree tree;
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
            tree.add_child("departments.department", tdep);
        }
        pt::write_xml(filename, tree, std::locale(),
            pt::xml_writer_make_settings<std::string>(' ', 3));
	}
} // namespace SERP