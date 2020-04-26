#pragma once
#include <iostream>
#include <vector>
#include <sqlite3.h>
#define logl(x) std::cout << x << std::endl

struct Data {
	int rows = 0;
	std::vector<std::string> vector;
};

class Database {
	sqlite3 * database;
	char * db_error;
	int status;

public:
	Database();
	bool OpenDatabase(const char *);
	bool ExecuteQuery(const std::string &);
	bool GetQueryResult(const std::string &, Data &);
	void CloseDatabase();
};

static int callback(void * data, int, char **, char **);