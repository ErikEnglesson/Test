#make
#./runTests
#./runTests --gtest_filter=BST.Insert

cmake_minimum_required(VERSION 2.6)

enable_testing()
 
# Locate wxWidgets
#set(wxWidgets_ROOT_DIR </home/englesson/Programming/wxWidgets>)
#set(wxWidgets_CONFIGURATION mswu)
#find_package(wxWidgets COMPONENTS core base REQUIRED)
#include(${wxWidgets_USE_FILE})
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

####################################################
########### ADD NEW SOURCE FILES HERE###############
set( test_sources ../BinaryNode.cpp
                  ../BinarySearchTree.cpp
                  ../List.cpp
                  ../Node.cpp
   )
####################################################   


add_executable(runTests tests.cpp ${test_sources} )

# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

set( CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++11" )

add_test(
    NAME runTests
    COMMAND runTests
)



#target_link_libraries(runTests ${wxWidgets_LIBRARIES})
