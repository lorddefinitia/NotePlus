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


#ifndef WORD_STYLE_H
#define WORD_STYLE_H

#ifndef COLOUR_PICKER_H
#include "colourpicker.h"
#endif //COLOUR_PICKER_H

#ifndef WORD_STYLE_DLG_RES_H
#include "wordstyledlgres.h"
#endif //WORD_STYLE_DLG_RES_H

#ifndef PARAMETERS_H
#include "parameters.h"
#endif //PARAMETERS_H

#define WM_UPDATESCINTILLAS			(WORDSTYLE_USER + 1) //GlobalStyleDlg's msg 2 send 2 its parent

enum fontStyleType {BOLD_STATUS, ITALIC_STATUS, UNDERLINE_STATUS};

const bool C_FOREGROUND = false;
const bool C_BACKGROUND = true;


class ColourStaticTextHooker {
public :
	ColourStaticTextHooker() : _colour(RGB(0x00, 0x00, 0x00)) {};

COLORREF  setColour (COLORREF colour2Set);
void  hookOn (HWND staticHandle);
private :
	COLORREF _colour;
	WNDPROC _oldProc;

CALLBACK int staticProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK colourStaticProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
};

class WordStyleDlg : public StaticDialog
{
public :
	WordStyleDlg():_isDirty(false), _isThemeDirty(false), _restoreInvalid(false), /*_isSync(true),*/ _isShownGOCtrls(false){};

void  init (HINSTANCE hInst, HWND parent);

	virtual void create(int dialogID, bool isRTL = false);

void  doDialog (bool isRTL = false);

void  prepare2Cancel ();

virtual void  redraw () const;
	
void  restoreGlobalOverrideValues ();

	void apply();

void  addLastThemeEntry ();



private :
    ColourPicker *_pFgColour;
    ColourPicker *_pBgColour;

    int _currentLexerIndex;
	int _currentThemeIndex;

    HWND _hCheckBold;
    HWND _hCheckItalic;
	HWND _hCheckUnderline;
    HWND _hFontNameCombo;
    HWND _hFontSizeCombo;
	HWND _hSwitch2ThemeCombo;

	HWND _hFgColourStaticText;
	HWND _hBgColourStaticText;
	HWND _hFontNameStaticText;
	HWND _hFontSizeStaticText;
	HWND _hStyleInfoStaticText;
	//TCHAR _originalWarning[256];

	LexerStylerArray _lsArray;
    StyleArray _globalStyles;
	generic_string _themeName;

	LexerStylerArray _styles2restored;
	StyleArray _gstyles2restored;
	GlobalOverride _gOverride2restored;
	bool _restoreInvalid;

	ColourStaticTextHooker colourHooker;

	bool _isDirty;
	bool _isThemeDirty;
    //bool _isSync;
	bool _isShownGOCtrls;

	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);


	Style & getCurrentStyler() {
		int styleIndex = ::SendDlgItemMessage(_hSelf, IDC_STYLES_LIST, LB_GETCURSEL, 0, 0);
		if (styleIndex == LB_ERR) styleIndex = 0;

        if (_currentLexerIndex == 0)
		{
            return _globalStyles.getStyler(styleIndex);
		}
        else
        {
		    LexerStyler & lexerStyler = _lsArray.getLexerFromIndex(_currentLexerIndex - 1);
		    return lexerStyler.getStyler(styleIndex);
        }
	};

	int whichTabColourIndex();

	void updateColour(bool which);
	void updateFontStyleStatus(fontStyleType whitchStyle);
	void updateExtension();
	void updateFontName();
	void updateFontSize();
	void updateUserKeywords();
	void switchToTheme();
	void updateThemeName(generic_string themeName);

	void loadLangListFromNppParam();

void  enableFg (bool isEnable);

void  enableBg (bool isEnable);

void  enableFontName (bool isEnable);

void  enableFontSize (bool isEnable);

void  enableFontStyle (bool isEnable);
long  notifyDataModified ();
	void setStyleListFromLexer(int index);
    void setVisualFromStyleList();

	void updateGlobalOverrideCtrls();

void  showGlobalOverrideCtrls (bool show);
};

#endif //WORD_STYLE_H
