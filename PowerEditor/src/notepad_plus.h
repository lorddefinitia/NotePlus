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

#include "buffer.h"
#include "doctabview.h"
#include "splittercontainer.h"
#include "findreplacedlg.h"
#include "aboutdlg.h"
#include "rundlg.h"
#include "statusbar.h"
#include "lastrecentfilelist.h"
#include "gotolinedlg.h"
#include "findcharsinrange.h"
#include "columneditor.h"
#include "wordstyledlg.h"
#include "trayiconcontroler.h"
#include "pluginsmanager.h"
/*
#ifndef NOTEPAD_PLUS_MSGS_H
#include "notepad_plus_msgs.h"
#endif //NOTEPAD_PLUS_MSGS_H
*/
#include "preferencedlg.h"
#include "windowsdlg.h"
#include "runmacrodlg.h"
#include "dockingmanager.h"
#include "process.h"
#include "autocompletion.h"
#include "smarthighlighter.h"
#include "scintillactrls.h"
#include "lesdlgs.h"
#include "localization.h"


#ifndef NOTEPAD_PLUS_H
#define NOTEPAD_PLUS_H


#define MENU 0x01
#define TOOLBAR 0x02

#define URL_REG_EXPR "[A-Za-z]+://[A-Za-z0-9_\\-\\+~.:?&@=/%#,;\\{\\}\\(\\)\\[\\]\\|\\*\\!\\\\]+"

enum FileTransferMode {
	TransferClone		= 0x01,
	TransferMove		= 0x02
};

enum WindowStatus {	//bitwise mask
	WindowMainActive	= 0x01,
	WindowSubActive		= 0x02,
	WindowBothActive	= 0x03,	//little helper shortcut
	WindowUserActive	= 0x04,
	WindowMask			= 0x07
};

enum trimOp {
	lineHeader = 0,
	lineTail = 1,
	lineEol = 2
};

enum spaceTab {
	tab2Space = 0,
	space2TabLeading = 1,
	space2TabAll = 2
};

struct TaskListInfo;

struct VisibleGUIConf {
	bool isPostIt;
	bool isFullScreen;
	
	//Used by both views
	bool isMenuShown;
	//bool isToolbarShown;	//toolbar forcefully hidden by hiding rebar
	DWORD_PTR preStyle;

	//used by postit only
	bool isTabbarShown;
	bool isAlwaysOnTop;
	bool isStatusbarShown;

	//used by fullscreen only
	WINDOWPLACEMENT _winPlace;

	VisibleGUIConf() : isPostIt(false), isFullScreen(false),
		isAlwaysOnTop(false), isMenuShown(true), isTabbarShown(true),
		isStatusbarShown(true), preStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN)
	{
		_winPlace.length = 0;
	};
};


class FileDialog;
class Notepad_plus_Window;
class AnsiCharPanel;
class ClipboardHistoryPanel;
class VerticalFileSwitcher;
class ProjectPanel;
class DocumentMap;
class FunctionListPanel;

class Notepad_plus {

friend class Notepad_plus_Window;

public:
	Notepad_plus();
	virtual ~Notepad_plus();
	LRESULT init(HWND hwnd);
	LRESULT process(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	void killAllChildren();
    /*
HWND  getWindowHandle () const ;
    */

	enum comment_mode {cm_comment, cm_uncomment, cm_toggle};

	void setTitle();
	void getTaskListInfo(TaskListInfo *tli);

	// For filtering the modeless Dialog message

// fileOperations
	//The doXXX functions apply to a single buffer and dont need to worry about views, with the excpetion of doClose, since closing one view doesnt have to mean the document is gone
	BufferID doOpen(const TCHAR *fileName, bool isReadOnly = false, int encoding = -1);
	bool doReload(BufferID id, bool alert = true);
	bool doSave(BufferID, const TCHAR * filename, bool isSaveCopy = false);
	void doClose(BufferID, int whichOne);
bool  doDelete (const TCHAR *fileName) const ;

	void fileOpen();
	void fileNew();

bool  fileReload () ;

	bool fileClose(BufferID id = BUFFER_INVALID, int curView = -1);	//use curView to override view to close from
	bool fileCloseAll();
	bool fileCloseAllButCurrent();
	bool fileSave(BufferID id = BUFFER_INVALID);
	bool fileSaveAll();
	bool fileSaveAs(BufferID id = BUFFER_INVALID, bool isSaveCopy = false);
	bool fileDelete(BufferID id = BUFFER_INVALID);
	bool fileRename(BufferID id = BUFFER_INVALID);

	bool addBufferToView(BufferID id, int whichOne);
	bool moveBuffer(BufferID id, int whereTo);	//assumes whereFrom is otherView(whereTo)
	bool switchToFile(BufferID buffer);			//find buffer in active view then in other view.
// end fileOperations

	bool isFileSession(const TCHAR * filename);
	void filePrint(bool showDialog);
	bool saveScintillaParams();

	bool saveGUIParams();
	bool saveProjectPanelsParams();
	void saveDockingParams();
void  saveUserDefineLangs () ;
void  saveShortcuts ();
	void saveSession(const Session & session);
void  saveFindHistory ();

	void getCurrentOpenedFiles(Session & session);

	bool fileLoadSession(const TCHAR *fn = NULL);
	const TCHAR * fileSaveSession(size_t nbFile, TCHAR ** fileNames, const TCHAR *sessionFile2save);
	const TCHAR * fileSaveSession(size_t nbFile = 0, TCHAR ** fileNames = NULL);
	void changeToolBarIcons();

	bool doBlockComment(comment_mode currCommentMode);
	bool doStreamComment();
	//--FLS: undoStreamComment: New function unDoStreamComment()
	bool undoStreamComment();
	
	bool addCurrentMacro();
	void macroPlayback(Macro);
    
void  loadLastSession ();

	bool loadSession(Session & session);

	

	void notifyBufferChanged(Buffer * buffer, int mask);
	bool findInFiles();
	bool replaceInFiles();
	void setFindReplaceFolderFilter(const TCHAR *dir, const TCHAR *filters);
	vector<generic_string> addNppComponents(const TCHAR *destDir, const TCHAR *extFilterName, const TCHAR *extFilter);
    int getHtmlXmlEncoding(const TCHAR *fileName) const;
HACCEL  getAccTable () const;
	bool emergency(generic_string emergencySavedDir);

	
private:
	Notepad_plus_Window *_pPublicInterface;
    Window *_pMainWindow;
	DockingManager _dockingManager;
	vector<int> _internalFuncIDs;

	AutoCompletion _autoCompleteMain;
	AutoCompletion _autoCompleteSub;	//each Scintilla has its own autoComplete

	SmartHighlighter _smartHighlighter;
    NativeLangSpeaker _nativeLangSpeaker;
    DocTabView _mainDocTab;
    DocTabView _subDocTab;
    DocTabView *_pDocTab;
	DocTabView *_pNonDocTab;

    ScintillaEditView _subEditView;
    ScintillaEditView _mainEditView;
	ScintillaEditView _invisibleEditView;	//for searches
	ScintillaEditView _fileEditView;		//for FileManager

    ScintillaEditView *_pEditView;
	ScintillaEditView *_pNonEditView;

    SplitterContainer *_pMainSplitter;
    SplitterContainer _subSplitter;

    ContextMenu _tabPopupMenu, _tabPopupDropMenu, _fileSwitcherMultiFilePopupMenu;

	ToolBar	_toolBar;
	IconList _docTabIconList;
	
    StatusBar _statusBar;
	bool _toReduceTabBar;
	ReBar _rebarTop;
	ReBar _rebarBottom;

	// Dialog
	FindReplaceDlg _findReplaceDlg;
	FindIncrementDlg _incrementFindDlg;
    AboutDlg _aboutDlg;
	RunDlg _runDlg;
    GoToLineDlg _goToLineDlg;
	ColumnEditorDlg _colEditorDlg;
	WordStyleDlg _configStyleDlg;
	PreferenceDlg _preference;
	FindCharsInRangeDlg _findCharsInRangeDlg;
	
	// a handle list of all the Notepad++ dialogs
	vector<HWND> _hModelessDlgs;

	LastRecentFileList _lastRecentFileList;

	//vector<iconLocator> _customIconVect;

	WindowsMenu _windowsMenu;
	HMENU _mainMenuHandle;

	bool _sysMenuEntering;
	

	// For FullScreen/PostIt features
	VisibleGUIConf	_beforeSpecialView;
	void fullScreenToggle();
	void postItToggle();

	// Keystroke macro recording and playback
	Macro _macro;
	bool _recordingMacro;
	RunMacroDlg _runMacroDlg;

	// For hotspot
	bool _linkTriggered;
	bool _isHotspotDblClicked;
	bool _isFolding;

	//For Dynamic selection highlight
	CharacterRange _prevSelectedRange;

	struct ActivateAppInfo {
		bool _isActivated;
		int _x;
		int _y;
		ActivateAppInfo() : _isActivated(false), _x(0), _y(0){};
	} _activeAppInf;

	//Synchronized Scolling
	
	struct SyncInfo {
		int _line;
		int _column;
		bool _isSynScollV;
		bool _isSynScollH;
		SyncInfo():_line(0), _column(0), _isSynScollV(false), _isSynScollH(false){};
        bool doSync() const  {return (_isSynScollV || _isSynScollH); };
	} _syncInfo;

	bool _isUDDocked;

	trayIconControler *_pTrayIco;
	int _zoomOriginalValue;

	Accelerator _accelerator;
	ScintillaAccelerator _scintaccelerator;

	PluginsManager _pluginsManager;
    ButtonDlg _restoreButton;

	bool _isFileOpening;

	ScintillaCtrls _scintillaCtrls4Plugins;

	vector<pair<int, int> > _hideLinesMarks;
	StyleArray _hotspotStyles;
    bool _rememberThisSession; // always true. except -nosession is indicated on the launch time


	AnsiCharPanel *_pAnsiCharPanel;
	ClipboardHistoryPanel *_pClipboardHistoryPanel;
	VerticalFileSwitcher *_pFileSwitcherPanel;
	ProjectPanel *_pProjectPanel_1;
	ProjectPanel *_pProjectPanel_2;
	ProjectPanel *_pProjectPanel_3;

	DocumentMap *_pDocMap;
	FunctionListPanel *_pFuncList;

	BOOL notify(SCNotification *notification);
	void specialCmd(int id);
	void command(int id);

//Document management
	UCHAR _mainWindowStatus;	//For 2 views and user dialog if docked
	int _activeView;

	//User dialog docking
	void dockUserDlg();
    void undockUserDlg();

	//View visibility
	void showView(int whichOne);
	bool viewVisible(int whichOne);
	void hideView(int whichOne);
	void hideCurrentView();
bool  bothActive () ;
	bool reloadLang();
	bool loadStyles();

int  currentView ();

int  otherView ();

int  otherFromView (int whichOne);

	bool canHideView(int whichOne);	//true if view can safely be hidden (no open docs etc)

	int switchEditViewTo(int gid);	//activate other view (set focus etc)

	void docGotoAnotherEditView(FileTransferMode mode);	//TransferMode
	void docOpenInNewInstance(FileTransferMode mode, int x = 0, int y = 0);

	void loadBufferIntoView(BufferID id, int whichOne, bool dontClose = false);		//Doesnt _activate_ the buffer
	bool removeBufferFromView(BufferID id, int whichOne);	//Activates alternative of possible, or creates clean document if not clean already

	bool activateBuffer(BufferID id, int whichOne);			//activate buffer in that view if found
	void notifyBufferActivated(BufferID bufid, int view);
	void performPostReload(int whichOne);
//END: Document management

	int doSaveOrNot(const TCHAR *fn);
	int doReloadOrNot(const TCHAR *fn, bool dirty);
	int doCloseOrNot(const TCHAR *fn);
	int doDeleteOrNot(const TCHAR *fn);
	int doActionOrNot(const TCHAR *title, const TCHAR *displayText, int type);

	void enableMenu(int cmdID, bool doEnable) const;
	void enableCommand(int cmdID, bool doEnable, int which) const;
	void checkClipboard();
	void checkDocState();
	void checkUndoState();
	void checkMacroState();
	void checkSyncState();
	void dropFiles(HDROP hdrop);
	void checkModifiedDocument();

    void getMainClientRect(RECT & rc) const;
	void staticCheckMenuAndTB() const;
	void dynamicCheckMenuAndTB() const;
	void enableConvertMenuItems(formatType f) const;
	void checkUnicodeMenuItems() const;

	generic_string getLangDesc(LangType langType, bool getName = false);

void  setLangStatus (LangType langType);

	void setDisplayFormat(formatType f);
	int getCmdIDFromEncoding(int encoding) const;
	void setUniModeText();

	void checkLangsMenu(int id) const ;
    void setLanguage(LangType langType);
	enum LangType menuID2LangType(int cmdID);

void  checkMenuItem (int itemID, bool willBeChecked) const ;
	void MaintainIndentation(TCHAR ch);
	
	void addHotSpot();

void  bookmarkAdd (int lineno) const ;
void  bookmarkDelete (int lineno) const ;
bool  bookmarkPresent (int lineno) const ;
void  bookmarkToggle (int lineno) const ;
    void bookmarkNext(bool forwardScan);
void  bookmarkClearAll () const ;

	void copyMarkedLines();
	void cutMarkedLines();
	void deleteMarkedLines(bool isMarked);
	void pasteToMarkedLines();
	void deleteMarkedline(int ln);
	void inverseMarks();
	void replaceMarkedline(int ln, const TCHAR *str);
	generic_string getMarkedLine(int ln);
    void findMatchingBracePos(int & braceAtCaret, int & braceOpposite);
    bool braceMatch();

    void activateNextDoc(bool direction);
	void activateDoc(int pos);

	void updateStatusBar();
	size_t getSelectedCharNumber(UniMode);
	size_t getCurrentDocCharCount(UniMode u);
	int getSelectedAreas();
	size_t getSelectedBytes();
	bool isFormatUnicode(UniMode);
	int getBOMSize(UniMode);

	void showAutoComp();
	void autoCompFromCurrentFile(bool autoInsert = true);
	void showFunctionComp();

	//void changeStyleCtrlsLang(HWND hDlg, int *idArray, const char **translatedText);
	bool replaceAllFiles();
	bool findInOpenedFiles();
	bool findInCurrentFile();

	bool matchInList(const TCHAR *fileName, const vector<generic_string> & patterns);
	void getMatchedFileNames(const TCHAR *dir, const vector<generic_string> & patterns, vector<generic_string> & fileNames, bool isRecursive, bool isInHiddenDir);

	void doSynScorll(HWND hW);
	void setWorkingDir(const TCHAR *dir);
	bool str2Cliboard(const TCHAR *str2cpy);
	bool bin2Cliboard(const UCHAR *uchar2cpy, size_t length);

	bool getIntegralDockingData(tTbData & dockData, int & iCont, bool & isVisible);
	int getLangFromMenuName(const TCHAR * langName);
	generic_string getLangFromMenu(const Buffer * buf);

    generic_string exts2Filters(generic_string exts) const;
	int setFileOpenSaveDlgFilters(FileDialog & fDlg, int langType = -1);
	void markSelectedTextInc(bool enable);
	Style * getStyleFromName(const TCHAR *styleName);
	bool dumpFiles(const TCHAR * outdir, const TCHAR * fileprefix = TEXT(""));	//helper func
	void drawTabbarColoursFromStylerArray();

	void loadCommandlineParams(const TCHAR * commandLine, CmdLineParams * pCmdParams);
	bool noOpenedDoc() const;
	bool goToPreviousIndicator(int indicID2Search, bool isWrap = true) const;
	bool goToNextIndicator(int indicID2Search, bool isWrap = true) const;
	int wordCount();
	
	void wsTabConvert(spaceTab whichWay);
	void doTrim(trimOp whichPart);
	void removeEmptyLine(bool isBlankContained);
	void launchAnsiCharPanel();
	void launchClipboardHistoryPanel();
	void launchFileSwitcherPanel();
	void launchProjectPanel(int cmdID, ProjectPanel ** pProjPanel, int panelID);
	void launchDocMap();
	void launchFunctionList();
	int getQuoteIndexFrom(const char *quoter) const;
	void showQuoteFromIndex(int index) const;
	void showAllQuotes() const;
	static DWORD WINAPI threadTextPlayer(void *text2display);
	static DWORD WINAPI threadTextTroller(void *params);
	static int getRandomAction(int ranNum);
	static bool deleteBack(ScintillaEditView *pCurrentView, BufferID targetBufID);
	static bool deleteForward(ScintillaEditView *pCurrentView, BufferID targetBufID);
	static bool selectBack(ScintillaEditView *pCurrentView, BufferID targetBufID);
	
static int  getRandomNumber (int rangeMax = -1) ;
};


#endif //NOTEPAD_PLUS_H