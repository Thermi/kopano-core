virtual HRESULT __stdcall GetLastError(HRESULT hResult, ULONG flags, LPMAPIERROR *lppMAPIError) _kc_override;
virtual HRESULT __stdcall Advise(ULONG ulEventMask, LPMAPIADVISESINK lpAdviseSink, ULONG *lpulConnection) _kc_override;
virtual HRESULT __stdcall Unadvise(ULONG ulConnection) _kc_override;
virtual HRESULT __stdcall GetStatus(ULONG *lpulTableStatus, ULONG *lpulTableType) _kc_override;
virtual HRESULT __stdcall SetColumns(LPSPropTagArray lpPropTagArray, ULONG flags) _kc_override;
virtual HRESULT __stdcall QueryColumns(ULONG flags, LPSPropTagArray *lpPropTagArray) _kc_override;
virtual HRESULT __stdcall GetRowCount(ULONG flags, ULONG *lpulCount) _kc_override;
virtual HRESULT __stdcall SeekRow(BOOKMARK bkOrigin, LONG lRowCount, LONG *lplRowsSought) _kc_override;
virtual HRESULT __stdcall SeekRowApprox(ULONG ulNumerator, ULONG ulDenominator) _kc_override;
virtual HRESULT __stdcall QueryPosition(ULONG *lpulRow, ULONG *lpulNumerator, ULONG *lpulDenominator) _kc_override;
virtual HRESULT __stdcall FindRow(LPSRestriction lpRestriction, BOOKMARK bkOrigin, ULONG flags) _kc_override;
virtual HRESULT __stdcall Restrict(LPSRestriction lpRestriction, ULONG flags) _kc_override;
virtual HRESULT __stdcall CreateBookmark(BOOKMARK *lpbkPosition) _kc_override;
virtual HRESULT __stdcall FreeBookmark(BOOKMARK bkPosition) _kc_override;
virtual HRESULT __stdcall SortTable(LPSSortOrderSet lpSortCriteria, ULONG flags) _kc_override;
virtual HRESULT __stdcall QuerySortOrder(LPSSortOrderSet *lppSortCriteria) _kc_override;
virtual HRESULT __stdcall QueryRows(LONG lRowCount, ULONG flags, LPSRowSet *lppRows) _kc_override;
virtual HRESULT __stdcall Abort(void) _kc_override;
virtual HRESULT __stdcall ExpandRow(ULONG cbInstanceKey, LPBYTE pbInstanceKey, ULONG ulRowCount, ULONG flags, LPSRowSet *lppRows, ULONG *lpulMoreRows) _kc_override;
virtual HRESULT __stdcall CollapseRow(ULONG cbInstanceKey, LPBYTE pbInstanceKey, ULONG flags, ULONG *lpulRowCount) _kc_override;
virtual HRESULT __stdcall WaitForCompletion(ULONG flags, ULONG ulTimeout, ULONG *lpulTableStatus) _kc_override;
virtual HRESULT __stdcall GetCollapseState(ULONG flags, ULONG cbInstanceKey, LPBYTE lpbInstanceKey, ULONG *lpcbCollapseState, LPBYTE *lppbCollapseState) _kc_override;
virtual HRESULT __stdcall SetCollapseState(ULONG flags, ULONG cbCollapseState, LPBYTE pbCollapseState, BOOKMARK *lpbkLocation) _kc_override;
