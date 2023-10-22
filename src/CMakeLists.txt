cmake_minimum_required(VERSION 3.26)

add_executable(27_4_3
        ../main.cpp
        ../includes/constance.h
        ../includes/utilities.h
        ../includes/Base.h
        ../includes/Worker.h
        ../includes/Supervisor.h
        ../includes/Manager.h
        utilities.cpp
        Base.cpp
        Manager.cpp
        Supervisor.cpp
        Worker.cpp
)

target_include_directories(27_4_3 PUBLIC ${CMAKE_SOURCE_DIR}/includes)