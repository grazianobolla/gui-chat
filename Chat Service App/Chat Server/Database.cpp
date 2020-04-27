#include "Database.h"

Database::Database() { }

bool Database::OpenDatabase(const char * path) {
	status = sqlite3_open(path, &database);
	if (status == 1) return false;
	else return true;
}

bool Database::ExecuteQuery(const std::string & query) {
	status = sqlite3_exec(database, query.c_str(), callback, 0, &db_error);
	if (status != SQLITE_OK) {
		logl("Could not execute query");
		sqlite3_free(db_error);
		return false;
	}
	else return true;
}

//Gets the result from the database and saves it on the Data reference
bool Database::GetQueryResult(const std::string & query, Data & data) {
	status = sqlite3_exec(database, query.c_str(), callback, &data, &db_error);
	if (status != SQLITE_OK) {
		logl("Could not execute query on GetEntry()");
		sqlite3_free(db_error);
		return false;
	}
	else return true;
}

void Database::CloseDatabase() {
	sqlite3_close(database);
}

static int callback(void * data, int argc, char **argv, char **azColName) {
	Data * d = (Data *)data;
	d->rows = argc;
	for (int i = 0; i < argc; i++) {
		if (data != nullptr) {
			d->vector.push_back((argv[i] ? argv[i] : "NULL"));
		}
	}
	return 0;

}