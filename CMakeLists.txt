cmake_minimum_required(VERSION 3.16)
project(SalaLivre_Sprint1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Liste todos os seus arquivos aqui para o Linker encontrá-los
qt_add_executable(SalaLivre_Sprint1
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    reservalib.cpp
    reservalib.h
    IReservaService.h
)

target_link_libraries(SalaLivre_Sprint1 PRIVATE Qt6::Widgets)
add_subdirectory(UnitTests)
