#include "FilmDB.h"
#include <iostream>

FilmDB::FilmDB() {
    int result = sqlite3_open(DB_PATH, &db);
    if (result != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else {
        createTableIfNotExists();  // Создаем таблицу, если её еще нет
        // insertTestData();          // Заполняем базу данных тестовыми данными (Используется только при первом запуске приложения)
    }
}

FilmDB::~FilmDB() {
    if (db) {
        sqlite3_close(db);
    }
}

void FilmDB::createTableIfNotExists() {
    const char* create_table_sql =
            "CREATE TABLE IF NOT EXISTS films ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT NOT NULL, "
            "genre TEXT NOT NULL, "
            "rating INTEGER NOT NULL, "
            "duration INTEGER NOT NULL);";

    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, create_table_sql, nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Error creating table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}
// Использовалось только при первом запуске приложения для заполнения таблицы БД
//void FilmDB::insertTestData() {
//    const char* insert_data_sql =
//            "INSERT INTO films (title, genre, rating, duration) VALUES "
//            "('The Matrix', 'Action', 9, 136),"
//            "('Inception', 'Action', 8, 148),"
//            "('Toy Story', 'Comedy', 8, 81),"
//            "('The Dark Knight', 'Action', 9, 152),"
//            "('Shrek', 'Comedy', 7, 90),"
//            "('Avengers', 'Action', 8, 143),"
//            "('Pulp Fiction', 'Crime', 9, 154),"
//            "('The Conjuring', 'Horror', 7, 112),"
//            "('Saw', 'Horror', 7, 103),"
//            "('Finding Nemo', 'Comedy', 8, 100);";
//
//    char* errorMessage = nullptr;
//    int result = sqlite3_exec(db, insert_data_sql, nullptr, nullptr, &errorMessage);
//
//    if (result != SQLITE_OK) {
//        std::cerr << "Error inserting data: " << errorMessage << std::endl;
//        sqlite3_free(errorMessage);
//    }
//}

std::vector<std::string> FilmDB::get_good_films_of_genre(int rating, const std::string& genre) {
    std::vector<std::string> films;
    std::string query = "SELECT title FROM films WHERE genre = '" + genre + "' AND rating >= " + std::to_string(rating);

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return films;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        films.emplace_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    }

    sqlite3_finalize(stmt);
    return films;
}

std::vector<std::string> FilmDB::get_films_of_genre_less_then(int time, const std::string& genre) {
    std::vector<std::string> films;
    std::string query = "SELECT title FROM films WHERE genre = '" + genre + "' AND duration <= " + std::to_string(time);

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return films;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        films.emplace_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    }

    sqlite3_finalize(stmt);
    return films;
}

std::vector<std::string> FilmDB::get_films_less_than(int time) {
    std::vector<std::string> films;
    std::string query = "SELECT title FROM films WHERE duration <= " + std::to_string(time);

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return films;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        films.emplace_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    }

    sqlite3_finalize(stmt);
    return films;
}

int FilmDB::count_genre(const std::string& genre) {
    int count = 0;
    std::string query = "SELECT COUNT(*) FROM films WHERE genre = '" + genre + "'";

    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return count;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count;
}
