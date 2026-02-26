cmake_minimum_required(VERSION 3.16)
project(UnitTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Adicionado Sql aqui também!
find_package(Qt6 REQUIRED COMPONENTS Widgets Test Sql)

include_directories(..)

add_executable(UnitTests
    tst_unittests.cpp
    tst_adminmoduletests.cpp
    ../reservalib.cpp
    ../adminmodel.cpp
    ../adminmodel.ui
    ../userservice.cpp
    ../databasemanager.cpp
    tst_adminmoduletests.h
)

# Adicionado Qt6::Sql aqui!
target_link_libraries(UnitTests PRIVATE
    Qt6::Widgets
    Qt6::Test
    Qt6::Sql
)

