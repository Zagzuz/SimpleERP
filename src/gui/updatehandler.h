#ifndef	GUI_UPDATEHANDLER_H
#define GUI_UPDATEHANDLER_H

#include <functional>


namespace SERP::gui
{
	enum class Update
	{
		#include "update_types.def"
	};

	class UpdateHandler
	{
	public:
		virtual bool handle_update(Update upd) = 0;
	};
} // namespace SERP::gui

#endif // GUI_UPDATEHANDLER_H