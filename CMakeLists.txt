cmake_minimum_required(VERSION 3.10)
project(TaskManagerProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled8 main.cpp HelperMethods.cpp
        TaskManager/SQLite.cpp)

set(LIB_SOURCE_FILES
        TaskManager/TaskManager.cpp
        TaskManager/TaskManager.h
        TaskManager/TaskProcessing.cpp
        TaskManager/TaskProcessing.h
)

add_library(MyLibrary ${LIB_SOURCE_FILES})
target_include_directories(MyLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/TaskManager)
target_link_libraries(untitled8 PUBLIC MyLibrary sqlite3)
