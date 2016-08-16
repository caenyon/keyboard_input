cmake_minimum_required(VERSION 3.5)
project(keyboard_input)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# X11 libraries are required
FIND_PACKAGE(X11 REQUIRED)
INCLUDE_DIRECTORIES ( ${X11_INCLUDE_DIR} )
LINK_LIBRARIES ( ${X11_LIBRARIES} )

# also link XInput and XTest extension modules
LINK_LIBRARIES(Xi Xtst)

# specify targets
add_executable(send_xtest keyboard_input/linux/send/send_xtest.cpp)
