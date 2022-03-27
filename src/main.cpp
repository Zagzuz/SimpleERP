#include <iostream>

#include "tmanager.h"


int main(int* argc, char** argv)
{
	SERP::TManager m;
	m.create_division("main");
	m.add_employee("main", { "Andre", "Manager", 1000 });
	m.change_position("Andre", "SEO Manager", "main");
	auto e = m.find_employee("Andre", "main");
	if (e) std::cout << e->salary;
	m.save("some_data.xml");

	SERP::TManager tm;
	tm.load("data.xml");
	tm.save("new_data.xml");
	return 0;
}