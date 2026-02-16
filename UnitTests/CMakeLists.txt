cmake_minimum_required(VERSION 3.16)
project(UnitTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilita o processamento automático de arquivos Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Encontra os pacotes necessários
find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

# Inclui a pasta anterior para localizar os headers (.h)
include_directories(..)

# UNIFICAÇÃO: Liste TODOS os arquivos aqui em um único comando
add_executable(UnitTests
    tst_unittests.cpp
    ../reservalib.cpp
    ../adminmodel.cpp
    ../adminmodel.ui
    ../userservice.cpp
)

# Vincula as bibliotecas ao executável
target_link_libraries(UnitTests PRIVATE Qt6::Widgets Qt6::Test)
