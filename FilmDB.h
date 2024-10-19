#ifndef FILMDB_H
#define FILMDB_H

#include <string>
#include <vector>
#include "sqlite3.h"

#define DB_PATH "films.db"

class FilmDB {
private:
    sqlite3* db;

    // Закрытые методы
    void createTableIfNotExists();  // Создание таблицы, если она не существует
    void insertTestData();          // Добавление данных в таблицу

public:
    FilmDB();
    ~FilmDB();

    std::vector<std::string> get_good_films_of_genre(int rating, const std::string& genre);
    std::vector<std::string> get_films_of_genre_less_then(int time, const std::string& genre);
    std::vector<std::string> get_films_less_than(int time);
    int count_genre(const std::string& genre);
};

#endif // FILMDB_H
