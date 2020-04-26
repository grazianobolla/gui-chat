#include "Database.h"

bool Database::OpenDatabase(const char * path) {
	status = sqlite3_open(path, &database);
	if (status == true) return false;
	else return true;
}

bool Database::ExecuteQuery(const char * query) {
	status = sqlite3_exec(database, query, 0, 0, &db_error);
	if (status != SQLITE_DONE) {
		sqlite3_free(db_error);
		return false;
	}
}
bool Database::InitializeDatabase() {
	ExecuteQuery("CREATE TABLE if NOT EXISTS 'users' ('username' VARCHAR(16), 'password' VARCHAR(32))");
}

void Database::CloseDatabase() {
	sqlite3_close(database);
}