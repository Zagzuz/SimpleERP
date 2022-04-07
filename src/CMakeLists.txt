set($Boost_ROOT ${PROJECT_SOURCE_DIR}/Boost/lib/cmake)
find_package(Boost 1.78 REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/nana/include)
add_subdirectory(base)
add_executable(Main "main.cpp")
add_library(Manager STATIC "manager.cpp" "manager.h")
target_link_libraries(Main PUBLIC Employee
                                  Division
                                  BasicManager
                                  Stateful
                                  Manager
                                  Boost::serialization
                                  nana)
