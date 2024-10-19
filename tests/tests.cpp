#include "FilmDB.h"
#include <iostream>
#include <vector>
#include <string>

// Простая функция для проверки равенства двух векторов строк
bool compareVectors(const std::vector<std::string>& expected, const std::vector<std::string>& actual) {
    if (expected.size() != actual.size()) return false;

    for (size_t i = 0; i < expected.size(); ++i) {
        if (expected[i] != actual[i]) {
            return false;
        }
    }

    return true;
}

// Функция для запуска одного теста
void runTest(const std::string& testName, const std::vector<std::string>& expected, const std::vector<std::string>& actual) {
    if (compareVectors(expected, actual)) {
        std::cout << testName << " passed." << std::endl;
    } else {
        std::cout << testName << " failed." << std::endl;
        std::cout << "Expected: ";
        for (const auto& film : expected) {
            std::cout << film << " ";
        }
        std::cout << "\nActual: ";
        for (const auto& film : actual) {
            std::cout << film << " ";
        }
        std::cout << std::endl;
    }
}

// Основная функция для тестирования методов класса FilmDB
void runAllTests() {
    FilmDB db;

    // Тест 1: Получение фильмов жанра "Action" с рейтингом >= 8
    std::vector<std::string> expectedActionFilms = { "The Matrix", "Inception", "The Dark Knight", "Avengers" };
    std::vector<std::string> actualActionFilms = db.get_good_films_of_genre(8, "Action");
    runTest("Test 1: Action films with rating >= 8", expectedActionFilms, actualActionFilms);

    // Тест 2: Получение фильмов жанра "Comedy" с рейтингом >= 8
    std::vector<std::string> expectedComedyFilms = { "Toy Story", "Finding Nemo" };
    std::vector<std::string> actualComedyFilms = db.get_good_films_of_genre(8, "Comedy");
    runTest("Test 2: Comedy films with rating >= 8", expectedComedyFilms, actualComedyFilms);

    // Тест 3: Получение фильмов жанра "Horror" с рейтингом >= 7
    std::vector<std::string> expectedHorrorFilms = { "The Conjuring", "Saw" };
    std::vector<std::string> actualHorrorFilms = db.get_good_films_of_genre(7, "Horror");
    runTest("Test 3: Horror films with rating >= 7", expectedHorrorFilms, actualHorrorFilms);

    // Добавьте больше тестов по необходимости...
}

int main() {
    runAllTests();
    return 0;
}
