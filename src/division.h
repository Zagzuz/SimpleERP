#ifndef DIVISION_H
#define DIVISION_H

#include <string>
#include <string_view>
#include <numeric>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

#include "employee.h"


using boost::multi_index_container;
using namespace boost::multi_index;

namespace SERP
{
	struct Division
	{
		using salary_t = Employee::salary_t;
		using member_t = member<Employee, const std::string, &Employee::name>;

		Division(const std::string& name);
		void calculate_avg_salary();
		void count_employees();

		const std::string name;
		std::size_t n_employees = 0;
		salary_t avg_salary = 0;

		using emp_container_t = multi_index_container<Employee, indexed_by<hashed_unique<member_t>>>;
		emp_container_t employees;
	};
} // namespace SERP

#endif // DIVISION_H
