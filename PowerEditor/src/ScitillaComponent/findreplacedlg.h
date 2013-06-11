// This file is part of Notepad++ project
// Copyright (C)2003 Don HO <don.h@free.fr>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid      
// misunderstandings, we consider an application to constitute a          
// "derivative work" for the purpose of this license if it does any of the
// following:                                                             
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//    installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.



#include "findreplacedlg_rc.h"
#include "buffer.h"
#include "oldcrud.h"
#include "dockingdlginterface.h"
#include "boostregexsearch.h"


#ifndef FIND_REPLACE_DLG_H
#define FIND_REPLACE_DLG_H

#define FIND_RECURSIVE 1
#define FIND_INHIDDENDIR 2

#define FINDREPLACE_MAXLENGTH 2048

enum DIALOG_TYPE {FIND_DLG, REPLACE_DLG, FINDINFILES_DLG, MARK_DLG};

#define DIR_DOWN true
#define DIR_UP false

//#define FIND_REPLACE_STR_MAX 256

enum InWhat{ALL_OPEN_DOCS, FILES_IN_DIR, CURRENT_DOC};

struct FoundInfo {
	FoundInfo(int start, int end, const TCHAR *fullPath)
		: _start(start), _end(end), _fullPath(fullPath) {};
	int _start;
	int _end;
	generic_string _fullPath;
};

struct TargetRange {
	int targetStart;
	int targetEnd;
};

enum SearchIncrementalType { NotIncremental, FirstIncremental, NextIncremental };
enum SearchType { FindNormal, FindExtended, FindRegex };
enum ProcessOperation { ProcessFindAll, ProcessReplaceAll, ProcessCountAll, ProcessMarkAll, ProcessMarkAll_2, ProcessMarkAll_IncSearch, ProcessMarkAllExt };

struct FindOption
{
	bool _isWholeWord;
	bool _isMatchCase;
	bool _isWrapAround;
	bool _whichDirection;
	SearchIncrementalType _incrementalType;
	SearchType _searchType;
	bool _doPurge;
	bool _doMarkLine;
	bool _isInSelection;
	generic_string _str2Search;
	generic_string _str4Replace;
	generic_string _filters;
	generic_string _directory;
	bool _isRecursive;
	bool _isInHiddenDir;
	bool _dotMatchesNewline;
	FindOption() : _isWholeWord(true), _isMatchCase(true), _searchType(FindNormal),\
		_isWrapAround(true), _whichDirection(DIR_DOWN), _incrementalType(NotIncremental), 
		_doPurge(false), _doMarkLine(false),
		_isInSelection(false),  _isRecursive(true), _isInHiddenDir(false),
		_dotMatchesNewline(false),
		_filters(TEXT("")), _directory(TEXT("")) {};
};

//This class contains generic search functions as static functions for easy access
class Searching {
public:
	static int convertExtendedToString(const TCHAR * query, TCHAR * result, int length);
	static TargetRange t;
static int  buildSearchFlags (const FindOption * option) ;
	static void displaySectionCentered(int posStart, int posEnd, ScintillaEditView * pEditView, bool isDownwards = true);

private:
	static bool readBase(const TCHAR * str, int * value, int base, int size);

};

//Finder: Dockable window that contains search results
class Finder : public DockingDlgInterface {
  friend class FindReplaceDlg;
public:
	Finder() : DockingDlgInterface(IDD_FINDRESULT), _pMainFoundInfos(&_foundInfos1), _pMainMarkings(&_markings1) {
		_MarkingsStruct._length = 0;
		_MarkingsStruct._markings = NULL;
	};

	~Finder() {
		_scintView.destroy();
	}
  virtual void init (HINSTANCE hInst, HWND hPere, ScintillaEditView **ppEditView) ;

	void addSearchLine(const TCHAR *searchName);
	void addFileNameTitle(const TCHAR * fileName);
	void addFileHitCount(int count);
	void addSearchHitCount(int count);
	void add(FoundInfo fi, SearchResultMarking mi, const TCHAR* foundline, int lineNb);
	void setFinderStyle();
	void removeAll();
	void openAll();
	void beginNewFilesSearch();
	void finishFilesSearch(int count);
	void gotoNextFoundResult(int direction);
	void GotoFoundLine();
	void DeleteResult();

protected :
	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
	bool notify(SCNotification *notification);

private:

	enum { searchHeaderLevel = SC_FOLDLEVELBASE + 1, fileHeaderLevel, resultLevel };

	ScintillaEditView **_ppEditView;
	std::vector<FoundInfo> _foundInfos1;
	std::vector<FoundInfo> _foundInfos2;
	std::vector<FoundInfo>* _pMainFoundInfos;
	std::vector<SearchResultMarking> _markings1;
	std::vector<SearchResultMarking> _markings2;
	std::vector<SearchResultMarking>* _pMainMarkings;
	SearchResultMarkings _MarkingsStruct;

	ScintillaEditView _scintView;
	unsigned int nFoundFiles;

	int _lastFileHeaderPos;
	int _lastSearchHeaderPos;

void  setFinderReadOnly (bool isReadOnly) ;

	static FoundInfo EmptyFoundInfo;
	static SearchResultMarking EmptySearchResultMarking;
};


enum FindStatus { FSFound, FSNotFound, FSTopReached, FSEndReached};


enum FindNextType {
	FINDNEXTTYPE_FINDNEXT,
	FINDNEXTTYPE_REPLACENEXT,
	FINDNEXTTYPE_FINDNEXTFORREPLACE
};


class FindReplaceDlg : public StaticDialog
{
friend class FindIncrementDlg;
public :
	static FindOption _options;
	static FindOption* _env;
	FindReplaceDlg() : StaticDialog(), _pFinder(NULL), _isRTL(false),\
		_fileNameLenMax(1024) {
		_uniFileName = new char[(_fileNameLenMax + 3) * 2];
		_winVer = (NppParameters::getInstance())->getWinVersion();
		_env = &_options;
	};
	~FindReplaceDlg();

void  init (HINSTANCE hInst, HWND hPere, ScintillaEditView **ppEditView) ;

	virtual void create(int dialogID, bool isRTL = false);
	
	void initOptionsFromDlg();

	void doDialog(DIALOG_TYPE whichType, bool isRTL = false, bool toShow = true);
	bool processFindNext(const TCHAR *txt2find, const FindOption *options = NULL, FindStatus *oFindStatus = NULL, FindNextType findNextType = FINDNEXTTYPE_FINDNEXT);
	bool processReplace(const TCHAR *txt2find, const TCHAR *txt2replace, const FindOption *options = NULL);

	int markAll(const TCHAR *txt2find, int styleID);
	//int markAll2(const TCHAR *str2find);
	int markAllInc(const FindOption *opt);
	

	int processAll(ProcessOperation op, const FindOption *opt, bool isEntire = false, const TCHAR *fileName = NULL, int colourStyleID = -1);
//	int processAll(ProcessOperation op, const TCHAR *txt2find, const TCHAR *txt2replace, bool isEntire = false, const TCHAR *fileName = NULL, const FindOption *opt = NULL, int colourStyleID = -1);
	int processRange(ProcessOperation op, const TCHAR *txt2find, const TCHAR *txt2replace, int startRange, int endRange, const TCHAR *fileName = NULL, const FindOption *opt = NULL, int colourStyleID = -1);
	void replaceAllInOpenedDocs();
	void findAllIn(InWhat op);
	void setSearchText(TCHAR * txt2find);

void  gotoNextFoundResult (int direction = 0) ;

void  putFindResult (int result) ;
const TCHAR *  getDir2Search () const ;

	void getPatterns(vector<generic_string> & patternVect);

void  launchFindInFilesDlg () ;

	void setFindInFilesDirFilter(const TCHAR *dir, const TCHAR *filters);

generic_string  getText2search () const ;

	const generic_string & getFilters() const {return _env->_filters;};
	const generic_string & getDirectory() const {return _env->_directory;};
	const FindOption & getCurrentOptions() const {return *_env;};
bool  isRecursive () const ;
bool  isInHiddenDir () const ;
	void saveFindHistory();
void  changeTabName (DIALOG_TYPE index, const TCHAR *name2change) ;
	void beginNewFilesSearch();

	void finishFilesSearch(int count);

void  focusOnFinder () ;

HWND  getHFindResults () ;

void  updateFinderScintilla () ;
	void execSavedCommand(int cmd, int intValue, generic_string stringValue);

protected :
	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
	void addText2Combo(const TCHAR * txt2add, HWND comboID, bool isUTF8 = false);
	generic_string getTextFromCombo(HWND hCombo, bool isUnicode = false) const;
	static LONG originalFinderProc;

	// Window procedure for the finder
	static LRESULT FAR PASCAL finderProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    void combo2ExtendedMode(int comboID);

private :

	DIALOG_TYPE _currentStatus;
	RECT _findClosePos, _replaceClosePos, _findInFilesClosePos;

	ScintillaEditView **_ppEditView;
	Finder  *_pFinder;
	bool _isRTL;

	int _findAllResult;
	TCHAR _findAllResultStr[1024];

	int _fileNameLenMax;
	char *_uniFileName;

	TabBar _tab;
	winVer _winVer;

	

	void enableReplaceFunc(bool isEnable);
	void enableFindInFilesControls(bool isEnable = true);
	void enableFindInFilesFunc();
	void enableMarkAllControls(bool isEnable);
	void enableMarkFunc();

void  setDefaultButton (int nID) ;

void  gotoCorrectTab () ;

	void updateCombos();
void  updateCombo (int comboID) ;
	void fillFindHistory();
    void fillComboHistory(int id, const std::vector<generic_string> & strings);
    int saveComboHistory(int id, int maxcount, vector<generic_string> & strings);
	static const int FR_OP_FIND = 1;
	static const int FR_OP_REPLACE = 2;
	static const int FR_OP_FIF = 4;
	static const int FR_OP_GLOBAL = 8;
	void saveInMacro(int cmd, int cmdType);


};

//FindIncrementDlg: incremental search dialog, docked in rebar
class FindIncrementDlg : public StaticDialog
{
public :
	FindIncrementDlg() : _pFRDlg(NULL), _pRebar(NULL), _FindStatus(FSFound) {};
	void init(HINSTANCE hInst, HWND hPere, FindReplaceDlg *pFRDlg, bool isRTL = false);
	virtual void destroy();
	virtual void display(bool toShow = true) const;
#ifdef UNICODE
void  setSearchText (const TCHAR * txt2find, bool) ;
#else
void  setSearchText (const TCHAR * txt2find, bool isUTF8 = false) ;
#endif

	void setFindStatus(FindStatus iStatus);
	
FindStatus  getFindStatus () ;

	void addToRebar(ReBar * rebar);
private :
	bool _isRTL;
	FindReplaceDlg *_pFRDlg;
	FindStatus _FindStatus;

	ReBar * _pRebar;
	REBARBANDINFO _rbBand;

	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
	void markSelectedTextInc(bool enable, FindOption *opt = NULL);
};




#endif //FIND_REPLACE_DLG_H
