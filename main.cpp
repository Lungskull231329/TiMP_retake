#include <iostream>
#include "FilmDB.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    FilmDB db;

    // Демонстрация получения фильмов с рейтингом >= 8 для жанра "Action"
    std::cout << "Хорошие фильмы жанра Action (рейтинг >= 8):\n";
    for (const auto& title : db.get_good_films_of_genre(8, "Action")) {
        std::cout << "- " << title << std::endl;
    }

    // Фильмы жанра "Comedy", которые длятся меньше 120 минут
    std::cout << "\nФильмы жанра Comedy длительностью менее 120 минут:\n";
    for (const auto& title : db.get_films_of_genre_less_then(120, "Comedy")) {
        std::cout << "- " << title << std::endl;
    }

    // Все фильмы, которые идут меньше 90 минут
    std::cout << "\nФильмы длительностью менее 90 минут:\n";
    for (const auto& title : db.get_films_less_than(90)) {
        std::cout << "- " << title << std::endl;
    }

    // Подсчёт фильмов жанра "Horror"
    std::cout << "\nКоличество фильмов жанра Horror: " << db.count_genre("Horror") << std::endl;

    return 0;
}
