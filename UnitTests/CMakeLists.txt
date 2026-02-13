cmake_minimum_required(VERSION 3.16)
project(UnitTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilita as ferramentas do Qt
set(CMAKE_AUTOMOC ON)

# Encontra os pacotes necessários (Widgets para o QString/QDate e Test para o framework)
find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

# Inclui a pasta anterior para que o teste ache os seus headers (.h)
include_directories(..)

add_executable(UnitTests
    tst_unittests.cpp
    ../reservalib.cpp
)

# Vincula as bibliotecas ao executável de teste
target_link_libraries(UnitTests PRIVATE Qt6::Widgets Qt6::Test)
