cmake_minimum_required(VERSION 3.16)
project(smart_hos_mgmt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 5.12 REQUIRED COMPONENTS Core Network Widgets)

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client-patient)
