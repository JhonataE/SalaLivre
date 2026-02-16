cmake_minimum_required(VERSION 3.16)
project(SalaLivre_Sprint1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adicionado o componente Test para suportar o UnitTests
find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

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

)

target_link_libraries(SalaLivre_Sprint1 PRIVATE Qt6::Widgets)

# Verifica a existência da pasta de testes antes de adicionar o subdiretório
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/UnitTests/CMakeLists.txt")
    add_subdirectory(UnitTests)
endif()
