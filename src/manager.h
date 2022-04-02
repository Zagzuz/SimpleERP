#ifndef MANAGER_H
#define MANAGER_H

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "base/basicmanager.h"
#include "base/stateful.h"
#include "gui/treeview.h"


namespace pt = boost::property_tree;

namespace SERP
{
	class Manager : public base::BasicManager, public base::Stateful
	{
	public:
		Manager(std::size_t state_capacity = 10);
		void add(const std::string& filename);
		void load(const std::string& filename);
		void save(const std::string& filename, std::size_t indent_count = 3);
		void save_state() override;
		void dissolve_divisions();
	protected:
		void load_state(std::size_t index) override;
	private:
		void load_tree(const pt::ptree& t);
		pt::ptree make_tree() const;
	};
} // namespace SERP

#endif // MANAGER_H
