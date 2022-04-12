#include <iostream>

#include "manager.h"


int main(int* argc, char** argv)
{
	std::cout.imbue(std::locale("ru_RU.UTF8"));
	SERP::Manager tm;
	tm.load("data.xml");
	tm.save_state();
	tm.create_division("SEO");
	tm.add_employee("SEO", { "Ivan", "Ivanovich", "Ivanov", "SEO manager", 10000 });
	tm.save_state();
	tm.undo();
	tm.save("new_data2.xml");
	tm.redo();
	tm.save("new_data1.xml");
	tm.window_show();
	tm.save("new_data1.xml");
	return 0;
}
