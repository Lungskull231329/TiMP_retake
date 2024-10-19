cmake_minimum_required(VERSION 3.26)
project(Nikulchev_Ivan_231_329_retake)

set(CMAKE_CXX_STANDARD 20)




# Добавляем заголовочные и исходные файлы
add_executable(Nikulchev_Ivan_231_329_retake main.cpp FilmDB.cpp
        FilmDB.h sqlite3.h sqlite3.c)


# Добавить цель для тестов
add_executable(FilmDBTests tests/tests.cpp FilmDB.cpp)

add_library(sqlite3 sqlite3.c)
# Линковка тестов с SQLite
target_link_libraries(FilmDBTests PRIVATE sqlite3)

# Включить заголовочные файлы для тестов
target_include_directories(FilmDBTests PRIVATE ${SQLite3_INCLUDE_DIRS})

# Убедитесь, что включены тестовые пути
target_include_directories(FilmDBTests PRIVATE ${CMAKE_SOURCE_DIR})


