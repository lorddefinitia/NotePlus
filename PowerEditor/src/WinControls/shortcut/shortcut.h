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

#include "shortcutrc.h"
#include "scintilla.h"

#ifndef SHORTCUTS_H
#define SHORTCUTS_H

using namespace std;

const size_t nameLenMax = 64;

class NppParameters;
class ScintillaEditView;

void getKeyStrFromVal(UCHAR keyVal, generic_string & str);
void getNameStrFromCmd(DWORD cmd, generic_string & str);
static int keyTranslate(int keyIn) {
	switch (keyIn) {
		case VK_DOWN:		return SCK_DOWN;
		case VK_UP:			return SCK_UP;
		case VK_LEFT:		return SCK_LEFT;
		case VK_RIGHT:		return SCK_RIGHT;
		case VK_HOME:		return SCK_HOME;
		case VK_END:		return SCK_END;
		case VK_PRIOR:		return SCK_PRIOR;
		case VK_NEXT:		return SCK_NEXT;
		case VK_DELETE:		return SCK_DELETE;
		case VK_INSERT:		return SCK_INSERT;
		case VK_ESCAPE:		return SCK_ESCAPE;
		case VK_BACK:		return SCK_BACK;
		case VK_TAB:		return SCK_TAB;
		case VK_RETURN:		return SCK_RETURN;
		case VK_ADD:		return SCK_ADD;
		case VK_SUBTRACT:	return SCK_SUBTRACT;
		case VK_DIVIDE:		return SCK_DIVIDE;
		case VK_OEM_2:		return '/';
		case VK_OEM_3:		return '`';
		case VK_OEM_4:		return '[';
		case VK_OEM_5:		return '\\';
		case VK_OEM_6:		return ']';
		default:			return keyIn;
	}
};

struct KeyCombo {
	bool _isCtrl;
	bool _isAlt;
	bool _isShift;
	UCHAR _key;
};

class Shortcut  : public StaticDialog {
public:
	Shortcut(): _canModifyName(false) {
		setName(TEXT(""));
		_keyCombo._isCtrl = false;
		_keyCombo._isAlt = false;
		_keyCombo._isShift = false;
		_keyCombo._key = 0;
	};

	Shortcut(const TCHAR *name, bool isCtrl, bool isAlt, bool isShift, UCHAR key) : _canModifyName(false) {
		_name[0] = '\0';
		if (name) {
			setName(name);
		} else {
			setName(TEXT(""));
		}
		_keyCombo._isCtrl = isCtrl;
		_keyCombo._isAlt = isAlt;
		_keyCombo._isShift = isShift;
		_keyCombo._key = key;
	};

	Shortcut(const Shortcut & sc) {
		setName(sc.getMenuName());
		_keyCombo = sc._keyCombo;
		_canModifyName = sc._canModifyName;
	}

BYTE  getAcceleratorModifiers ();

	Shortcut & operator=(const Shortcut & sc) {
		//Do not allow setting empty names
		//So either we have an empty name or the other name has to be set
		if (_name[0] == 0 || sc._name[0] != 0) {
			setName(sc.getMenuName());
		}
		_keyCombo = sc._keyCombo;
		this->_canModifyName = sc._canModifyName;
		return *this;
	}
	friend inline const bool operator==(const Shortcut & a, const Shortcut & b) {
		return ((lstrcmp(a.getMenuName(), b.getMenuName()) == 0) && 
			(a._keyCombo._isCtrl == b._keyCombo._isCtrl) && 
			(a._keyCombo._isAlt == b._keyCombo._isAlt) && 
			(a._keyCombo._isShift == b._keyCombo._isShift) && 
			(a._keyCombo._key == b._keyCombo._key)
			);
	};

	friend inline const bool operator!=(const Shortcut & a, const Shortcut & b) {
		return !(a == b);
	};

virtual int  doDialog ();

virtual bool  isValid () const;
virtual bool  isEnabled () const;

	virtual generic_string toString() const;					//the hotkey part
generic_string  toMenuItemString () const;
	const KeyCombo & getKeyCombo() const {
		return _keyCombo;
	};

const TCHAR *  getName () const;

const TCHAR * getMenuName () const ;

	void setName(const TCHAR * name);

protected :
	KeyCombo _keyCombo;
	virtual BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
	bool _canModifyName;
	TCHAR _name[nameLenMax];		//normal name is plain text (for display purposes)
	TCHAR _menuName[nameLenMax];	//menu name has ampersands for quick keys
};
		 
class CommandShortcut : public Shortcut {
public:
	CommandShortcut(Shortcut sc, long id) :	Shortcut(sc), _id(id) {};
long  getID () const;
void  setID (unsigned long id);

private :
	unsigned long _id;
};


class ScintillaKeyMap : public Shortcut {
public:
	ScintillaKeyMap(Shortcut sc, unsigned long scintillaKeyID, unsigned long id): Shortcut(sc), _menuCmdID(id), _scintillaKeyID(scintillaKeyID) {
		_keyCombos.clear();
		_keyCombos.push_back(_keyCombo);
		_keyCombo._key = 0;
		size = 1;
	};
long  getScintillaKeyID () const;
int  getMenuCmdID () const;
int  toKeyDef (int index) const;

	KeyCombo getKeyComboByIndex(int index) const;
	void setKeyComboByIndex(int index, KeyCombo combo);
	void removeKeyComboByIndex(int index);
void  clearDups ();
	int addKeyCombo(KeyCombo combo);
	bool isEnabled() const;
	size_t getSize() const;

	generic_string toString() const;
	generic_string toString(int index) const;

int  doDialog ();

	//only compares the internal KeyCombos, nothing else
	friend inline const bool operator==(const ScintillaKeyMap & a, const ScintillaKeyMap & b) {
		bool equal = a.size == b.size;
		if (!equal)
			return false;
		size_t i = 0;
		while(equal && (i < a.size)) {
			equal = 
				(a._keyCombos[i]._isCtrl	== b._keyCombos[i]._isCtrl) && 
				(a._keyCombos[i]._isAlt		== b._keyCombos[i]._isAlt) && 
				(a._keyCombos[i]._isShift	== b._keyCombos[i]._isShift) && 
				(a._keyCombos[i]._key		== b._keyCombos[i]._key);
			i++;
		}
		return equal;
	};

	friend inline const bool operator!=(const ScintillaKeyMap & a, const ScintillaKeyMap & b) {
		return !(a == b);
	};

private:
	unsigned long _scintillaKeyID;
	int _menuCmdID;
	vector<KeyCombo> _keyCombos;
	size_t size;
	void applyToCurrentIndex();
	void validateDialog();
	void showCurrentSettings();
	void updateListItem(int index);
protected :
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);
};


class Window;

struct recordedMacroStep {
	enum MacroTypeIndex {mtUseLParameter, mtUseSParameter, mtMenuCommand, mtSavedSnR};
	
	int message;
	long wParameter;
	long lParameter;
	generic_string sParameter;
	MacroTypeIndex MacroType;
	
	recordedMacroStep(int iMessage, long wParam, long lParam, int codepage);
	recordedMacroStep(int iCommandID) : message(0), wParameter(iCommandID), lParameter(0), MacroType(mtMenuCommand) {};

	recordedMacroStep(int iMessage, long wParam, long lParam, const TCHAR *sParam, int type)
		: message(iMessage), wParameter(wParam), lParameter(lParam), MacroType(MacroTypeIndex(type)){
			sParameter = (sParam)?generic_string(sParam):TEXT("");	
	};

	bool isValid() const {
		return true;
	};
	bool isPlayable() const {return MacroType <= mtMenuCommand;};

	void PlayBack(Window* pNotepad, ScintillaEditView *pEditView);
};

typedef vector<recordedMacroStep> Macro;

class MacroShortcut : public CommandShortcut {
friend class NppParameters;
public:
	MacroShortcut(Shortcut sc, Macro macro, int id) : CommandShortcut(sc, id), _macro(macro) {_canModifyName = true;};
	Macro & getMacro() {return _macro;};
private:
	Macro _macro;
};


class UserCommand : public CommandShortcut {
friend class NppParameters;
public:
	UserCommand(Shortcut sc, const TCHAR *cmd, int id) : CommandShortcut(sc, id), _cmd(cmd) {_canModifyName = true;};
	const TCHAR* getCmd() const {return _cmd.c_str();};
private:
	generic_string _cmd;
};

class PluginCmdShortcut : public CommandShortcut {
//friend class NppParameters;
public:
	PluginCmdShortcut(Shortcut sc, int id, const TCHAR *moduleName, unsigned short internalID) :\
		CommandShortcut(sc, id), _id(id), _moduleName(moduleName), _internalID(internalID) {};
bool  isValid () const;
const TCHAR *  getModuleName () const;
int  getInternalID () const;
long  getID () const;

private :
	unsigned long _id;
	generic_string _moduleName;
	int _internalID;
};

class Accelerator { //Handles accelerator keys for Notepad++ menu, including custom commands
friend class ShortcutMapper;
public:
	Accelerator():_hAccelMenu(NULL), _hMenuParent(NULL), _hAccTable(NULL), _pAccelArray(NULL), _nbAccelItems(0){};
	~Accelerator(){
		if (_hAccTable)
			::DestroyAcceleratorTable(_hAccTable);
		if (_pAccelArray)
			delete [] _pAccelArray;
	};
void  init (HMENU hMenu, HWND menuParent);
HACCEL  getAccTable () const;

	void updateShortcuts();
	void updateFullMenu();

private:
	HMENU _hAccelMenu;
	HWND _hMenuParent;
	HACCEL _hAccTable;
	ACCEL *_pAccelArray;
	int _nbAccelItems;

void  reNew ();
	void updateMenuItemByCommand(CommandShortcut csc);
};

class ScintillaAccelerator {	//Handles accelerator keys for scintilla
public:
	ScintillaAccelerator() : _nrScintillas(0) {};
	void init(vector<HWND> * vScintillas, HMENU hMenu, HWND menuParent);
	void updateKeys();
	void updateKey(ScintillaKeyMap skmOld, ScintillaKeyMap skm);
private:
	HMENU _hAccelMenu;
	HWND _hMenuParent;
	vector<HWND> _vScintillas;
	int _nrScintillas;

	void updateMenuItemByID(ScintillaKeyMap skm, int id);
};

#endif //SHORTCUTS_H
