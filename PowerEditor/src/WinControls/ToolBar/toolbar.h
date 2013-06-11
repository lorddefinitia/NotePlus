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


#ifndef TOOL_BAR_H
#define TOOL_BAR_H

#ifndef NOTEPAD_PLUS_MSGS_H
#include "notepad_plus_msgs.h"
#endif //NOTEPAD_PLUS_MSGS_H

#define REBAR_BAR_TOOLBAR		0
#define REBAR_BAR_SEARCH		1

#define REBAR_BAR_EXTERNAL		10
#ifndef _WIN32_IE
#define _WIN32_IE	0x0600
#endif //_WIN32_IE

using namespace std;

enum toolBarStatusType {/*TB_HIDE, */TB_SMALL, TB_LARGE, TB_STANDARD};

#include "imagelistset.h"


typedef struct {
	UINT		message;		// identification of icon in tool bar (menu ID)
	HBITMAP		hBmp;			// bitmap for toolbar
	HICON		hIcon;			// icon for toolbar
} tDynamicList;

struct iconLocator {
	int listIndex;
	int iconIndex;
	generic_string iconLocation;

	iconLocator(int iList, int iIcon, const generic_string iconLoc) 
		: listIndex(iList), iconIndex(iIcon), iconLocation(iconLoc){};
};

class ReBar;
class TiXmlDocument;
class TiXmlNode;

class ToolBar : public Window
{
public :
	ToolBar():Window(), _pTBB(NULL), _nrButtons(0), _nrDynButtons(0), _nrTotalButtons(0), _nrCurrentButtons(0), _pRebar(NULL) {};
virtual  ~ToolBar ();

    void initTheme(TiXmlDocument *toolIconsDocRoot);
	virtual bool init(HINSTANCE hInst, HWND hPere, toolBarStatusType type, 
		ToolBarButtonUnit *buttonUnitArray, int arraySize);

	virtual void destroy();
void  enable (int cmdID, bool doEnable) const;

	int getWidth() const;
	int getHeight() const;

void  reduce ();
void  enlarge ();
void  setToUglyIcons ();

bool  getCheckState (int ID2Check) const;

void  setCheck (int ID2Check, bool willBeChecked) const;

toolBarStatusType  getState () const;

bool  changeIcons ();

bool  changeIcons (int whichLst, int iconIndex, const TCHAR *iconLocation);

	void registerDynBtn(UINT message, toolbarIcons* hBmp);

	void doPopop(POINT chevPoint);	//show the popup if buttons are hidden

	void addToRebar(ReBar * rebar);

private :
	TBBUTTON *_pTBB;
	ToolBarIcons _toolBarIcons;
	toolBarStatusType _state;
	vector<tDynamicList> _vDynBtnReg;
	size_t _nrButtons;
	size_t _nrDynButtons;
	size_t _nrTotalButtons;
	size_t _nrCurrentButtons;
	ReBar * _pRebar;
	REBARBANDINFO _rbBand;
    vector<iconLocator> _customIconVect;
    TiXmlNode *_toolIcons;


void  setDefaultImageList ();
void  setHotImageList ();
void  setDisableImageList ();

	void reset(bool create = false);
void  setState (toolBarStatusType state);
	
};

class ReBar : public Window
{
public :
	ReBar():Window() { usedIDs.clear(); };

virtual void  destroy ();

	void init(HINSTANCE hInst, HWND hPere);
	bool addBand(REBARBANDINFO * rBand, bool useID);	//useID true if ID from info should be used (false for plugins). wID in bandinfo will be set to used ID
	void reNew(int id, REBARBANDINFO * rBand);					//wID from bandinfo is used for update
	void removeBand(int id);

	void setIDVisible(int id, bool show);
	bool getIDVisible(int id);
	void setGrayBackground(int id);

private:
	vector<int> usedIDs;

	int getNewID();
	void releaseID(int id);
	bool isIDTaken(int id);
};

#endif // TOOL_BAR_H
