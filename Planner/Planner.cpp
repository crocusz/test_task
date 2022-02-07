#include "Planner.h"
#include <cstddef>
#include <iostream>
#include <mysql/mysql.h>

Planner::Planner() {
    createDB(pathToDB);
    createTable(pathToDB);
    WelcomeMenu();
    AppLoop();
}

Planner::~Planner() {

}
void Planner::WelcomeMenu() {
    system("clear");
    std::cout << "==============================" << std::endl;
    std::cout << "This is your personal planner!" << std::endl;
    std::cout << "Enjoy using this!" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << std::endl;
}

void Planner::showMenu() {
    std::cout << "===========================" << std::endl;
    std::cout << "SHOW ALL EVENT LIST: type s" << std::endl;
    std::cout << "ADD ONE EVENT: type a" << std::endl;
    std::cout << "DELETE ONE EVENT: type d" << std::endl;
    std::cout << "QUIT: type q" << std::endl;
    std::cout << "===========================" << std::endl;
}
void Planner::AppLoop() {
    char userChoose;
    while(true) {
        system("clear");
        showMenu();
        std::cout << "Your option: ";
        std::cin >> userChoose;

        if(userChoose == 's' || userChoose == 'S') showAllEvents();
        else if(userChoose == 'a' || userChoose == 'A') addOneEvent();
        else if(userChoose == 'd' || userChoose == 'D') deleteOneEvent();
        else if(userChoose == 'q' || userChoose == 'Q') break;
    }
}

int Planner::createDB(const char* path) {
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open(path, &DB);

	sqlite3_close(DB);

	return 0;
}

int Planner::createTable(const char* path) {
    sqlite3 *DB;
	char* messageError;

    std::string sql = "CREATE TABLE IF NOT EXISTS events("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME      TEXT NOT NULL, "
		"NOTE      TEXT NOT NULL, "
		"DATE      TEXT NOT NULL); ";
    
    
    try {
	
		int exit = 0;
		exit = sqlite3_open(path, &DB);
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
            std::cerr << "Error in createTable function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Table created Successfully" << std::endl;
		sqlite3_close(DB);
	}
	catch (const std::exception& e) {

        std::cerr << e.what();
	}

	return 0;
}

int Planner::insertData(const char *path, std::string name, std::string note, std::string date) {

    sqlite3* DB;
	char* messageError;
    std::string firstName;

    std::string sql("INSERT INTO events (NAME, NOTE, DATE) VALUES('$firstname', 'Chapa', 35, 'Tampa', 'A');");

	int exit = sqlite3_open(path, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
        std::cerr << "Error in insertData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
	std::cout << "Records inserted Successfully!" << std::endl;
        
    return 0;
}
void Planner::deleteOneEvent() {

}

int Planner::selectData(const char* path) {

}
void Planner::addOneEvent() {
    system("clear");
    std::string name;
    std::string note;
    std::string date;

    std::cout << "Enter a name of your event: ";
    std::cin >> name;
    std::cout << "Add some note to the event: " << std::endl;
    std::cin >> note;
    std::cout << "Enter a date when it will happens: " << std::endl;
    std::cin >> date;

    insertData(pathToDB, name, note, date);

}
void Planner::showAllEvents() {

}