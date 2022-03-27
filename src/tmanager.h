#ifndef TMANAGER_H
#define TMANAGER_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "manager.h"


namespace pt = boost::property_tree;

namespace SERP
{
	class TManager : public Manager
	{
	public:
		void load(const std::string& filename);
		void save(const std::string& filename);
	};
} // namespace SERP

#endif // TMANAGER_H