cmake_minimum_required(VERSION 3.14)

project(HavaDurumuUygulamasi)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)


set(SOURCES
    main.cpp
    havadurumu.cpp
)


set(HEADERS
    havadurumu.h
)


set(UIS
    havadurumu.ui
)


add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)


target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)
