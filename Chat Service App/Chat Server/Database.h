#pragma once
#include <sqlite3.h>

class Database {
	sqlite3 * database;
	char * db_error;
	int status;
public:
	bool OpenDatabase(const char *);
	bool ExecuteQuery(const char *);
	bool InitializeDatabase();
	void CloseDatabase();
};