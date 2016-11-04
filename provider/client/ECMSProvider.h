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

#ifndef MSPROVIDER_H
#define MSPROVIDER_H

#include <kopano/zcdefs.h>
#include <kopano/ECUnknown.h>
#include "WSTransport.h"

#include <string>

class ECMSProvider : public ECUnknown {
protected:
	ECMSProvider(ULONG ulFlags, const char *szClassName);
	virtual ~ECMSProvider();
public:
	static  HRESULT Create(ULONG ulFlags, ECMSProvider **lppECMSProvider);

	virtual HRESULT QueryInterface(REFIID refiid, void **lppInterface);

	virtual HRESULT Shutdown(ULONG * lpulFlags);
	virtual HRESULT Logon(LPMAPISUP lpMAPISup, ULONG ulUIParam, LPTSTR lpszProfileName, ULONG cbEntryID, LPENTRYID lpEntryID, ULONG ulFlags, LPCIID lpInterface, ULONG *lpcbSpoolSecurity, LPBYTE *lppbSpoolSecurity, LPMAPIERROR *lppMAPIError, LPMSLOGON *lppMSLogon, LPMDB *lppMDB);
	virtual HRESULT SpoolerLogon(LPMAPISUP lpMAPISup, ULONG ulUIParam, LPTSTR lpszProfileName, ULONG cbEntryID, LPENTRYID lpEntryID, ULONG ulFlags, LPCIID lpInterface, ULONG lpcbSpoolSecurity, LPBYTE lppbSpoolSecurity, LPMAPIERROR *lppMAPIError, LPMSLOGON *lppMSLogon, LPMDB *lppMDB);
	virtual HRESULT CompareStoreIDs(ULONG cbEntryID1, LPENTRYID lpEntryID1, ULONG cbEntryID2, LPENTRYID lpEntryID2, ULONG ulFlags, ULONG *lpulResult);

private:
	static HRESULT LogonByEntryID(WSTransport **lppTransport, sGlobalProfileProps *lpsProfileProps, ULONG cbEntryID, LPENTRYID lpEntryID);

private:
	class xMSProvider _kc_final : public IMSProvider {
		#include <kopano/xclsfrag/IUnknown.hpp>
		#include <kopano/xclsfrag/IMSProvider.hpp>
	} m_xMSProvider;

private:
	ULONG			m_ulFlags;
	std::string		m_strLastUser;
	std::string		m_strLastPassword;
};



#endif // MSPROVIDER_H
