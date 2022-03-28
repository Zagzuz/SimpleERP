#ifndef TMANAGER_H
#define TMANAGER_H

#include <string>
#include <deque>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "manager.h"


namespace pt = boost::property_tree;

namespace SERP
{
	class TManager : public Manager
	{
	public:
		enum Direction { BACKWARD, FORWARD };
		TManager(std::size_t state_capacity = 10);
		void add(const std::string& filename);
		void load(const std::string& filename);
		void save(const std::string& filename, std::size_t indent_count = 3);
		void load_state(std::size_t steps, Direction d = BACKWARD);
		void save_state();
		bool undo();
		bool redo();
		void set_state_capacity(std::size_t n);
		std::size_t get_state_capacity() const;
	private:
		void clear();
		void load_tree(const pt::ptree& t);
		pt::ptree make_tree() const;
		std::size_t state_cap_;
		std::size_t cur_state_;
		std::deque<std::string> state_vec_;
	};
} // namespace SERP

#endif // TMANAGER_H
