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

#pragma once

#include "scintilla.h"
#include "scintillaref.h"
#include "scilexer.h"
#include "buffer.h"
#include "colors.h"
#include "xpm_icons.h"


#ifndef SCINTILLA_EDIT_VIEW_H
#define SCINTILLA_EDIT_VIEW_H

using namespace std;

class UserDefineDialog;
class NppParameters;
struct Style;
struct Lang;
class Buffer;
typedef Buffer* BufferID;

/*
#ifndef RESOURCE_H
#include "resource.h"
#endif //RESOURCE_H
*/

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif //WM_MOUSEWHEEL

#ifndef WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif //WM_MOUSEHWHEEL

#ifndef WM_APPCOMMAND
#define WM_APPCOMMAND                   0x0319
#define APPCOMMAND_BROWSER_BACKWARD       1
#define APPCOMMAND_BROWSER_FORWARD        2
#define FAPPCOMMAND_MASK  0xF000
#define GET_APPCOMMAND_LPARAM(lParam) ((short)(HIWORD(lParam) & ~FAPPCOMMAND_MASK))
#endif //WM_APPCOMMAND

#define NB_WORD_LIST 4
#define WORD_LIST_LEN 256

typedef int (* SCINTILLA_FUNC) (void*, int, int, int);
typedef void * SCINTILLA_PTR;

#define WM_DOCK_USERDEFINE_DLG      (SCINTILLA_USER + 1)
#define WM_UNDOCK_USERDEFINE_DLG    (SCINTILLA_USER + 2)
#define WM_CLOSE_USERDEFINE_DLG		(SCINTILLA_USER + 3)
#define WM_REMOVE_USERLANG		    (SCINTILLA_USER + 4)
#define WM_RENAME_USERLANG			(SCINTILLA_USER + 5)
#define WM_REPLACEALL_INOPENEDDOC	(SCINTILLA_USER + 6)
#define WM_FINDALL_INOPENEDDOC  	(SCINTILLA_USER + 7)
#define WM_DOOPEN				  	(SCINTILLA_USER + 8)
#define WM_FINDINFILES			  	(SCINTILLA_USER + 9)
#define WM_REPLACEINFILES		  	(SCINTILLA_USER + 10)
#define WM_FINDALL_INCURRENTDOC	  	(SCINTILLA_USER + 11)
#define WM_FRSAVE_INT	  	(SCINTILLA_USER + 12)
#define WM_FRSAVE_STR	  	(SCINTILLA_USER + 13)

const int NB_FOLDER_STATE = 7;

// Codepage
const int CP_CHINESE_TRADITIONAL = 950;
const int CP_CHINESE_SIMPLIFIED = 936;
const int CP_JAPANESE = 932;
const int CP_KOREAN = 949;
const int CP_GREEK = 1253;

//wordList
#define LIST_NONE 0
#define LIST_0 1
#define LIST_1 2
#define LIST_2 4
#define LIST_3 8
#define LIST_4 16
#define LIST_5 32
#define LIST_6 64

const bool fold_uncollapse = true;
const bool fold_collapse = false;

const bool UPPERCASE = true;
const bool LOWERCASE = false;


const UCHAR MASK_FORMAT = 0x03;
const UCHAR MASK_ZERO_LEADING = 0x04;
const UCHAR BASE_10 = 0x00; // Dec
const UCHAR BASE_16 = 0x01; // Hex
const UCHAR BASE_08 = 0x02; // Oct
const UCHAR BASE_02 = 0x03; // Bin


const int MARK_BOOKMARK = 24;
const int MARK_HIDELINESBEGIN = 23;
const int MARK_HIDELINESEND = 22;
//const int MARK_LINEMODIFIEDUNSAVED = 21;
//const int MARK_LINEMODIFIEDSAVED = 20;
// 24 - 16 reserved for Notepad++ internal used
// 15 - 0  are free to use for plugins


int getNbDigits(int aNum, int base);

TCHAR * int2str(TCHAR *str, int strLen, int number, int base, int nbChiffre, bool isZeroLeading);

typedef LRESULT (WINAPI *CallWindowProcFunc) (WNDPROC,HWND,UINT,WPARAM,LPARAM);

const bool L2R = true;
const bool R2L = false;

struct ColumnModeInfo {
	int _selLpos; 
	int _selRpos;
	int _order; // 0 based index
	bool _direction; // L2R or R2L
	int _nbVirtualCaretSpc;
	int _nbVirtualAnchorSpc;

	ColumnModeInfo() : _selLpos(0), _selRpos(0), _order(-1), _direction(L2R), _nbVirtualAnchorSpc(0), _nbVirtualCaretSpc(0){};
	ColumnModeInfo(int lPos, int rPos, int order, bool dir = L2R, int vAnchorNbSpc = 0, int vCaretNbSpc = 0)
		: _selLpos(lPos), _selRpos(rPos), _order(order), _direction(dir), _nbVirtualAnchorSpc(vAnchorNbSpc), _nbVirtualCaretSpc(vCaretNbSpc){};

	bool isValid() const {
		return (_order >= 0 && _selLpos >= 0 && _selRpos >= 0 && _selLpos <= _selRpos);
	};
};

//
// SortClass for vector<ColumnModeInfo>
// sort in _order : increased order
struct SortInSelectOrder {
	bool operator() (ColumnModeInfo & l, ColumnModeInfo & r) {
		return (l._order < r._order);
	}
};

//
// SortClass for vector<ColumnModeInfo>
// sort in _selLpos : increased order
struct SortInPositionOrder {
	bool operator() (ColumnModeInfo & l, ColumnModeInfo & r) {
		return (l._selLpos < r._selLpos);
	}
};

typedef vector<ColumnModeInfo> ColumnModeInfos;

struct LanguageName {
	const TCHAR * lexerName;
	const TCHAR * shortName;
	const TCHAR * longName;
	LangType LangID;
	int lexerID;
};

class ScintillaEditView : public Window
{
friend class Finder;
friend class UserDefineDialog;
friend class UserLangContainer;
public:
	ScintillaEditView()
		: Window(), _pScintillaFunc(NULL),_pScintillaPtr(NULL),
		  _lineNumbersShown(false), _wrapRestoreNeeded(false)
	{
		++_refCount;
	};

	virtual ~ScintillaEditView();
	virtual void destroy()
	{
		::DestroyWindow(_hSelf);
		_hSelf = NULL;
	};

	virtual void init(HINSTANCE hInst, HWND hPere);

LRESULT  execute (UINT Msg, WPARAM wParam=0, LPARAM lParam=0) const ;
	
	void activateBuffer(BufferID buffer);

	void getCurrentFoldStates(std::vector<size_t> & lineStateVector);
	void syncFoldStateWith(const std::vector<size_t> & lineStateVectorNew);

	void getText(char *dest, int start, int end) const;
	void getGenericText(TCHAR *dest, size_t destlen, int start, int end) const;
#if (defined(UNICODE) || defined(LINUX))
	void getGenericText(TCHAR *dest, size_t deslen, int start, int end, int *mstart, int *mend) const;
#else
    void getGenericText(TCHAR *dest, int start, int end, int *, int *) const;
#endif
	void insertGenericTextFrom(int position, const TCHAR *text2insert) const;
	void replaceSelWith(const char * replaceText);

int  getSelectedTextCount () ;

	void getVisibleStartAndEndPosition(int * startPos, int * endPos);
    char * getWordFromRange(char * txt, int size, int pos1, int pos2);
	char * getSelectedText(char * txt, int size, bool expand = true);
    char * getWordOnCaretPos(char * txt, int size);
    TCHAR * getGenericWordOnCaretPos(TCHAR * txt, int size);
	TCHAR * getGenericSelectedText(TCHAR * txt, int size, bool expand = true);
	int searchInTarget(const TCHAR * Text2Find, int lenOfText2Find, int fromPos, int toPos) const;
	void appandGenericText(const TCHAR * text2Append) const;
	void addGenericText(const TCHAR * text2Append) const;
	void addGenericText(const TCHAR * text2Append, long *mstart, long *mend) const;
	int replaceTarget(const TCHAR * str2replace, int fromTargetPos = -1, int toTargetPos = -1) const;
	int replaceTargetRegExMode(const TCHAR * re, int fromTargetPos = -1, int toTargetPos = -1) const;
	void showAutoComletion(int lenEntered, const TCHAR * list);
	void showCallTip(int startPos, const TCHAR * def);
	void getLine(int lineNumber, TCHAR * line, int lineBufferLen);
	void addText(int length, const char *buf);

	void saveCurrentPos();
	void restoreCurrentPos();
	void saveCurrentFold();
	void restoreCurrentFold();

int  getCurrentDocLen () const ;

CharacterRange  getSelection () const ;

void  getWordToCurrentPos (TCHAR * str, int strLen) const ;

void  doUserDefineDlg (bool willBeShown = true, bool isRTL = false) ;

static UserDefineDialog *  getUserDefineDlg () ;

void  setCaretColorWidth (int color, int width = 1) const ;

void  beSwitched () ;

    //Marge member and method
    static const int _SC_MARGE_LINENUMBER;
    static const int _SC_MARGE_SYBOLE;
    static const int _SC_MARGE_FOLDER;
	//static const int _SC_MARGE_MODIFMARKER;

void  showMargin (int whichMarge, bool willBeShowed = true) ;

bool  hasMarginShowed (int witchMarge) ;
    
    void marginClick(int position, int modifiers);

void  setMakerStyle (folderStyle style) ;


void  setWrapMode (lineWrapMethod meth) ;


void  showWSAndTab (bool willBeShowed = true) ;

void  showEOL (bool willBeShowed = true) ;

bool  isEolVisible () ;
void  showInvisibleChars (bool willBeShowed = true) ;

bool  isInvisibleCharsShown () ;

void  showIndentGuideLine (bool willBeShowed = true) ;

bool  isShownIndentGuide () const ;

void  wrap (bool willBeWrapped = true) ;

bool  isWrap () const ;

bool  isWrapSymbolVisible () const ;

void  showWrapSymbol (bool willBeShown = true) ;

long  getCurrentLineNumber ()const ;

long  lastZeroBasedLineNumber () const ;

long  getCurrentXOffset ()const;

void  setCurrentXOffset (long xOffset);

void  scroll (int column, int line);

long  getCurrentPointX ()const;

long  getCurrentPointY ()const;

long  getTextHeight ()const;
	
void  gotoLine (int line);

long  getCurrentColumnNumber () const ;

bool  getSelectedCount (int & selByte, int & selLine) const ;

long  getLineLength (int line) const ;

long  getLineIndent (int line) const ;

	void setLineIndent(int line, int indent) const;

void  showLineNumbersMargin (bool show);

void  updateLineNumberWidth () ;

void  setCurrentLineHiLiting (bool isHiliting, COLORREF bgColor) const ;

bool  isCurrentLineHiLiting () const ;

	void performGlobalStyles();

	void expand(int &line, bool doExpand, bool force = false, int visLevels = 0, int level = -1);
		
	void currentLineUp() const;
	void currentLineDown() const;

	pair<int, int> getSelectionLinesRange() const;
    void currentLinesUp() const;
    void currentLinesDown() const;

	void convertSelectedTextTo(bool Case);
	void setMultiSelections(const ColumnModeInfos & cmi);

void  convertSelectedTextToLowerCase () ;

void  convertSelectedTextToUpperCase () ;
    
	void collapse(int level2Collapse, bool mode);
	void foldAll(bool mode);
	void fold(int line, bool mode);
bool  isFolded (int line);
	void foldCurrentPos(bool mode);
int  getCodepage () const ;

NppParameters *  getParameter () ;
	
	ColumnModeInfos getColumnModeSelectInfo();

	void columnReplace(ColumnModeInfos & cmi, const TCHAR *str);
	void columnReplace(ColumnModeInfos & cmi, int initial, int incr, UCHAR format);

	void foldChanged(int line, int levelNow, int levelPrev);
void  clearIndicator (int indicatorNumber) ;

	static LanguageName langNames[L_EXTERNAL+1];

	void bufferUpdated(Buffer * buffer, int mask);
BufferID  getCurrentBufferID () ;
Buffer *  getCurrentBuffer () ;
void  setCurrentBuffer (Buffer *buf2set) ;
	void styleChange();

	void hideLines();

	bool markerMarginClick(int lineNumber);	//true if it did something
	void notifyMarkers(Buffer * buf, bool isHide, int location, bool del);
	void runMarkers(bool doHide, int searchStart, bool endOfDoc, bool doDelete);

bool  isSelecting () const ;
	void setHiLiteResultWords(const TCHAR *keywords);
	void defineDocType(LangType typeDoc);	//setup stylers for active document
void  mouseWheel (WPARAM wParam, LPARAM lParam) ;
	
	void setHotspotStyle(Style& styleToSet);
    void setTabSettings(Lang *lang);
bool  isWrapRestoreNeeded () const ;
void  setWrapRestoreNeeded (bool isWrapRestoredNeeded) ;

bool  isCJK () const ;
	void scrollPosToCenter(int pos);

protected:
	static HINSTANCE _hLib;
	static int _refCount;
	
    static UserDefineDialog* _userDefineDlg;

    static const int _markersArray[][NB_FOLDER_STATE];

CALLBACK  scintillaStatic_Proc (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) ;

	LRESULT scintillaNew_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

	SCINTILLA_FUNC _pScintillaFunc;
	SCINTILLA_PTR  _pScintillaPtr;
	static WNDPROC _scintillaDefaultProc;
	CallWindowProcFunc _callWindowProc;
	BufferID attachDefaultDoc();

	//Store the current buffer so it can be retrieved later
	BufferID _currentBufferID;
	Buffer * _currentBuffer;
	
    NppParameters *_pParameter;
	int _codepage;
	bool _lineNumbersShown;
	bool _wrapRestoreNeeded;

	typedef std::map<int, Style> StyleMap;
	typedef std::map<BufferID, StyleMap*> BufferStyleMap;
	BufferStyleMap _hotspotStyles;

//Lexers and Styling
	void restyleBuffer();
	const char * getCompleteKeywordList(std::basic_string<char> & kwl, LangType langType, int keywordIndex);
	void setKeywords(LangType langType, const char *keywords, int index);
	void setLexer(int lexerID, LangType langType, int whichList);
	inline void makeStyle(LangType langType, const TCHAR **keywordArray = NULL);
	void setStyle(Style styleToSet);			//NOT by reference	(style edited)
	void setSpecialStyle(const Style & styleToSet);	//by reference
void  setSpecialIndicator (const Style & styleToSet) ;

	//Complex lexers (same lexer, different language)
	void setXmlLexer(LangType type);
 	void setCppLexer(LangType type);
	void setTclLexer();
    void setObjCLexer(LangType type);
	void setUserLexer(const TCHAR *userLangName = NULL);
	void setExternalLexer(LangType typeDoc);
	void setEmbeddedJSLexer();
    void setEmbeddedPhpLexer();
    void setEmbeddedAspLexer();
	//Simple lexers
void  setCssLexer () ;

void  setLuaLexer () ;

void  setMakefileLexer () ;

void  setIniLexer () ;


void  setSqlLexer () ;

void  setBashLexer () ;

void  setVBLexer () ;

void  setPascalLexer () ;

void  setPerlLexer () ;

void  setPythonLexer () ;

void  setBatchLexer () ;

void  setTeXLexer () ;

void  setNsisLexer () ;

void  setFortranLexer () ;

void  setLispLexer ();

void  setSchemeLexer ();

void  setAsmLexer ();

void  setDiffLexer ();

void  setPropsLexer ();

void  setPostscriptLexer ();

void  setRubyLexer ();

void  setSmalltalkLexer ();

void  setVhdlLexer ();

void  setKixLexer ();

void  setAutoItLexer ();

void  setCamlLexer ();

void  setAdaLexer ();

void  setVerilogLexer ();

void  setMatlabLexer ();

void  setHaskellLexer ();

void  setInnoLexer () ;

void  setCmakeLexer () ;

void  setYamlLexer () ;

    //--------------------

void  setCobolLexer () ;
void  setGui4CliLexer () ;
void  setDLexer () ;
void  setPowerShellLexer () ;
void  setRLexer () ;

    //--------------------

void  setSearchResultLexer () ;

bool  isNeededFolderMarge (LangType typeDoc) const ;
//END: Lexers and Styling

void  defineMarker (int marker, int markerType, COLORREF fore, COLORREF back, COLORREF foreActive) ;

int  codepage2CharSet () const ;

    pair<int, int> getWordRange();
	bool expandWordSelection();
};

#endif //SCINTILLA_EDIT_VIEW_H
