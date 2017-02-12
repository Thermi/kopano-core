/*
 * Copyright 2005 - 2016 Zarafa and its licensors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// ECDatabaseMySQL.h: interface for the ECDatabaseMySQL class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ECDATABASEMYSQL_H
#define ECDATABASEMYSQL_H

#include <kopano/zcdefs.h>
#include <string>

#include "ECDatabase.h"

namespace KC {

class ECConfig;
class ECLogger;
class zcp_versiontuple;

class ECDatabaseMySQL _kc_final : public ECDatabase {
public:
	ECDatabaseMySQL(ECConfig *lpConfig);
	virtual ~ECDatabaseMySQL(void);

	// Embedded mysql
	static ECRESULT	InitLibrary(const char *lpDatabaseDir, const char *lpConfigFile);
	static void UnloadLibrary(void);
	ECRESULT Connect(void) _kc_override;
	virtual ECRESULT DoSelect(const std::string &query, DB_RESULT *result, bool stream_result = false) _kc_override;
	ECRESULT DoSelectMulti(const std::string &query) _kc_override;
	virtual ECRESULT DoUpdate(const std::string &query, unsigned int *affected_rows = nullptr) _kc_override;
	virtual ECRESULT DoInsert(const std::string &query, unsigned int *insert_id = nullptr, unsigned int *affected_rows = nullptr) _kc_override;
	virtual ECRESULT DoDelete(const std::string &query, unsigned int *affected_rows = nullptr) _kc_override;
	virtual ECRESULT DoSequence(const std::string &seqname, unsigned int ulCount, unsigned long long *first_id) _kc_override;

	//Result functions
	virtual ECRESULT GetNextResult(DB_RESULT *) _kc_override;
	virtual ECRESULT FinalizeMulti(void) _kc_override;
	std::string FilterBMP(const std::string &to_filter) _kc_override;
	ECRESULT ValidateTables(void) _kc_override;
	bool SuppressLockErrorLogging(bool suppress) _kc_override;
	virtual ECRESULT Begin(void) _kc_override;
	virtual ECRESULT Commit(void) _kc_override;
	virtual ECRESULT Rollback(void) _kc_override;
	void ThreadInit(void) _kc_override;
	void ThreadEnd(void) _kc_override;

	// Database maintenance functions
	ECRESULT CreateDatabase(void) _kc_override;
	// Main update unit
	ECRESULT UpdateDatabase(bool force_update, std::string &report) _kc_override;
	ECRESULT InitializeDBState(void) _kc_override;
	ECRESULT CheckExistColumn(const std::string &table, const std::string &column, bool *exist) _kc_override;
	ECRESULT CheckExistIndex(const std::string &table, const std::string &key, bool *exist) _kc_override;

private:
	virtual const struct sSQLDatabase_t *GetDatabaseDefs(void) _kc_override;
	ECRESULT InitializeDBStateInner(void);
	virtual ECRESULT Query(const std::string &q) _kc_override;

// Database maintenance
	ECRESULT GetDatabaseVersion(zcp_versiontuple *);

	// Add a new database version record
	ECRESULT UpdateDatabaseVersion(unsigned int ulDatabaseRevision);
	ECRESULT IsUpdateDone(unsigned int ulDatabaseRevision, unsigned int ulRevision=0);
	ECRESULT GetFirstUpdate(unsigned int *lpulDatabaseRevision);

	bool m_bFirstResult = false;
	ECConfig *m_lpConfig = nullptr;
#ifdef DEBUG
	unsigned int m_ulTransactionState = 0;
#endif
};

} /* namespace */

#endif // #ifndef ECDATABASEMYSQL_H
