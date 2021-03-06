/*
 * SPDX-License-Identifier: AGPL-3.0-only
 * Copyright 2005 - 2016 Zarafa and its licensors
 */
#pragma once
#include <kopano/zcdefs.h>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <utility>
#include "ECICS.h"
#include "SOAPUtils.h"
#include <map>
#include <set>
#include <list>
#include <string>

namespace KC {

// Above EC_TABLE_CHANGE_THRESHOLD, a TABLE_CHANGE notification is sent instead of individual notifications
#define EC_TABLE_CHANGE_THRESHOLD 10

// this belongs to the DeleteObjects function
struct DELETEITEM {
	unsigned int ulId;
	unsigned int ulParent;
	bool fRoot;
	bool fInOGQueue;
	short ulObjType;
	short ulParentType;
	unsigned int ulFlags;
	unsigned int ulStoreId;
	unsigned int ulObjSize;
	unsigned int ulMessageFlags;
	SOURCEKEY sSourceKey;
	SOURCEKEY sParentSourceKey;
	entryId sEntryId; //fixme: auto destroy entryid
};

// Used to group notify flags and object type.
struct TABLECHANGENOTIFICATION {
	TABLECHANGENOTIFICATION(unsigned int t, unsigned int f): ulFlags(f), ulType(t) {}
	bool operator<(const TABLECHANGENOTIFICATION &rhs) const noexcept
	{
		return std::tie(ulFlags, ulType) < std::tie(rhs.ulFlags, rhs.ulType);
	}

	unsigned int ulFlags, ulType;
};

class PARENTINFO final {
public:
	int lItems = 0, lFolders = 0, lAssoc = 0, lUnread = 0;
	int lDeleted = 0, lDeletedFolders = 0, lDeletedAssoc = 0;
	unsigned int ulStoreId = 0;
};

#define EC_DELETE_FOLDERS		0x00000001
#define EC_DELETE_MESSAGES		0x00000002
#define EC_DELETE_RECIPIENTS	0x00000004
#define EC_DELETE_ATTACHMENTS	0x00000008
#define EC_DELETE_CONTAINER		0x00000010
#define EC_DELETE_HARD_DELETE	0x00000020
#define	EC_DELETE_STORE			0x00000040
#define EC_DELETE_NOT_ASSOCIATED_MSG	0x00000080

typedef std::list<DELETEITEM>	ECListDeleteItems;
typedef std::set<TABLECHANGENOTIFICATION>	ECSetTableChangeNotifications;
typedef std::map<unsigned int, ECSetTableChangeNotifications> ECMapTableChangeNotifications;

void FreeDeletedItems(ECListDeleteItems *lplstDeleteItems);

class ECAttachmentStorage;

ECRESULT GetSourceKey(unsigned int ulObjId, SOURCEKEY *lpSourceKey);
ECRESULT ExpandDeletedItems(ECSession *lpSession, ECDatabase *lpDatabase, ECListInt *lpsObjectList, unsigned int ulFlags, bool bCheckPermission, ECListDeleteItems *lplstDeleteItems);
ECRESULT DeleteObjectHard(ECSession *lpSession, ECDatabase *lpDatabase, ECAttachmentStorage *lpAttachmentStorage, unsigned int ulFlags, ECListDeleteItems &lstDeleteItems, bool bNoTransaction, ECListDeleteItems &lstDeleted);
ECRESULT DeleteObjectStoreSize(ECSession *lpSession, ECDatabase *lpDatabase, unsigned int ulFlags, ECListDeleteItems &lstDeleted);
ECRESULT DeleteObjectCacheUpdate(ECSession *lpSession, unsigned int ulFlags, const ECListDeleteItems &lstDeleted);
ECRESULT DeleteObjects(ECSession *lpSession, ECDatabase *lpDatabase, ECListInt *lpsObjectList, unsigned int ulFlags, unsigned int ulSyncId, bool bNoTransaction, bool bCheckPermission);
ECRESULT DeleteObjects(ECSession *lpSession, ECDatabase *lpDatabase, unsigned int ulObjectId, unsigned int ulFlags, unsigned int ulSyncId, bool bNoTransaction, bool bCheckPermission);
ECRESULT MarkStoreAsDeleted(ECSession *lpSession, ECDatabase *lpDatabase, unsigned int ulStoreHierarchyId, unsigned int ulSyncId);
ECRESULT WriteLocalCommitTimeMax(struct soap *soap, ECDatabase *lpDatabase, unsigned int ulFolderId, propVal **ppvTime);
ECRESULT UpdateTProp(ECDatabase *lpDatabase, unsigned int ulPropTag, unsigned int ulFolderId, ECListInt *lpObjectIDs);
ECRESULT UpdateTProp(ECDatabase *lpDatabase, unsigned int ulPropTag, unsigned int ulFolderId, unsigned int ulObjId);
ECRESULT UpdateFolderCount(ECDatabase *lpDatabase, unsigned int ulFolderId, unsigned int ulPropTag, int lDelta);
ECRESULT CheckQuota(ECSession *lpecSession, ULONG ulStoreId);
ECRESULT MapEntryIdToObjectId(ECSession *lpecSession, ECDatabase *lpDatabase, ULONG ulObjId, const entryId &sEntryId);
ECRESULT UpdateFolderCounts(ECDatabase *lpDatabase, ULONG ulParentId, ULONG ulFlags, propValArray *lpModProps);
ECRESULT ProcessSubmitFlag(ECDatabase *lpDatabase, ULONG ulSyncId, ULONG ulStoreId, ULONG ulObjId, bool bNewItem, propValArray *lpModProps);
ECRESULT CreateNotifications(ULONG ulObjId, ULONG ulObjType, ULONG ulParentId, ULONG ulGrandParentId, bool bNewItem, propValArray *lpModProps, struct propVal *lpvCommitTime);
extern ECRESULT WriteSingleProp(ECDatabase *, unsigned int obj_id, unsigned int folder_id, const struct propVal *, bool column_prop, unsigned int max_qsize, std::string &insert_query, bool replace = true);
extern ECRESULT WriteProp(ECDatabase *, unsigned int obj_id, unsigned int parent_id, const struct propVal *, bool replace = true);
extern ECRESULT InsertProps(ECDatabase *, unsigned int obj_id, unsigned int parent_id, const std::list<propVal> &, bool replace = false);
ECRESULT GetNamesFromIDs(struct soap *soap, ECDatabase *lpDatabase, struct propTagArray *lpPropTags, struct namedPropArray *lpsNames);
ECRESULT ResetFolderCount(ECSession *lpSession, unsigned int ulObjId, unsigned int *lpulUpdates = NULL);
extern ECRESULT RemoveStaleIndexedProp(ECDatabase *, unsigned int tag, const unsigned char *data, unsigned int size);
ECRESULT ApplyFolderCounts(ECDatabase *lpDatabase, const std::map<unsigned int, PARENTINFO> &mapFolderCounts);

#define LOCK_SHARED 	0x00000001
#define LOCK_EXCLUSIVE	0x00000002

// Lock folders and start transaction:
extern ECRESULT BeginLockFolders(ECDatabase *, unsigned int proptag, const std::set<std::string> &ids, unsigned int flags, kd_trans &, ECRESULT &);

struct NAMEDPROPDEF {
    GUID			guid;
    unsigned int	ulKind;
    unsigned int	ulId;
    std::string		strName;
};
typedef std::map<unsigned int, NAMEDPROPDEF> NamedPropDefMap;

struct CHILDPROPS {
	CHILDPROPS(struct soap *soap, unsigned int hint = 20);
	/* There may be fewer values cached in @lpPropVals than tags are present in @lpPropTags. */
	std::unique_ptr<DynamicPropTagArray> lpPropTags;
	std::unique_ptr<DynamicPropValArray> lpPropVals;
};
typedef std::map<unsigned int, CHILDPROPS> ChildPropsMap;

extern ECRESULT PrepareReadProps(struct soap *, ECDatabase *, bool do_query, unsigned int obj_id, unsigned int parent_id, unsigned int max_size, ChildPropsMap *, NamedPropDefMap *);
extern ECRESULT FixPropEncoding(struct propVal *);

} /* namespace */
