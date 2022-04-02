#include "treeview.h"


namespace SERP::gui
{
	void TreeView::show()
	{
        nana::form fm;
        fm.caption(L"Hello, World!");
        nana::button btn(fm, nana::rectangle{ 20, 20, 150, 30 });
        btn.caption(L"Quit");
        btn.events().click(nana::API::exit);
        fm.show();
        nana::exec();
	}
} // namespace SERP::gui
