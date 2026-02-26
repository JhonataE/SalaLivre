
cmake_minimum_required(VERSION 3.16)
project(SalaLivre_Sprint1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontra todos os pacotes de uma vez
find_package(Qt6 REQUIRED COMPONENTS Widgets Test Sql Core)

qt_add_executable(SalaLivre_Sprint1
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    reservalib.cpp
    reservalib.h
    IReservaService.h
    IUserService.h
    userservice.h
    userservice.cpp
    logindialog.h
    logindialog.cpp
    logindialog.ui
    adminmodel.h adminmodel.cpp adminmodel.ui
    databasemanager.h databasemanager.cpp


)

# Vincula as bibliotecas ao executável principal
target_link_libraries(SalaLivre_Sprint1 PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::Core
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/UnitTests/CMakeLists.txt")
    add_subdirectory(UnitTests)
endif()
