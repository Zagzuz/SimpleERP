find_package(Boost 1.78 COMPONENTS serialization REQUIRED)
link_directories(${PROJECT_SOURCE_DIR}/Boost/lib)
include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
add_executable(Main "main.cpp")
add_library(Employee STATIC "employee.cpp" "employee.h")
add_library(Division STATIC "division.cpp" "division.h")
add_library(Manager  STATIC "manager.cpp"  "manager.h")
add_library(TManager STATIC "tmanager.cpp" "tmanager.h")
target_link_libraries(Main PUBLIC Employee
								  Division
								  Manager
								  TManager
								  Boost::serialization)
