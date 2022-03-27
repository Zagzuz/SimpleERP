#include <iostream>

#include "manager.h"


int main(int* argc, char** argv)
{
	SERP::Manager m;
	m.create_division("main");
	m.add_employee("main", { "Andre", "Manager", 1000 });
	m.change_position("Andre", "SEO Manager", "main");
	auto e = m.find_employee("Andre", "main");
	if (e) std::cout << e->salary;
	return 0;
}