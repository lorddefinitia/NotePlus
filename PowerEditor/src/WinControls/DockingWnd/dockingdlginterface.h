// this file is part of Function List Plugin for Notepad++
// Copyright (C)2005 Jens Lorenz <jens.plugin.npp@gmx.de>
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

#include "precompiledheaders.h"
#include "dockingresource.h"
#include "docking.h"

#ifndef DOCKINGDLGINTERFACE_H
#define DOCKINGDLGINTERFACE_H

class DockingDlgInterface : public StaticDialog
{
public:
	DockingDlgInterface();

	DockingDlgInterface(int dlgID);
		
  ~DockingDlgInterface();
	
virtual void  init (HINSTANCE hInst, HWND parent);

void  create (tTbData * data, bool isRTL = false);

virtual void  updateDockingDlg ();

virtual void  destroy ();

virtual void  display (bool toShow = true) const;

const TCHAR *  getPluginFileName () const;

protected :
	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM, LPARAM lParam)
	{
		switch (message) 
		{

			case WM_NOTIFY: 
			{
				LPNMHDR	pnmh	= (LPNMHDR)lParam;

				if (pnmh->hwndFrom == _hParent)
				{
					switch (LOWORD(pnmh->code))
					{
						case DMN_CLOSE:
						{
							break;
						}
						case DMN_FLOAT:
						{
							_isFloating = true;
							break;
						}
						case DMN_DOCK:
						{
							_iDockedPos = HIWORD(pnmh->code);
							_isFloating = false;
							break;
						}
						default:
							break;
					}
				}
				break;
			}
			default:
				break;
		}
		return FALSE;
	};
	
	// Handles
    HWND			_HSource;
	int				_dlgID;
	bool            _isFloating;
	int				_iDockedPos;
	generic_string  _moduleName;
	generic_string  _pluginName;
};

#endif // DOCKINGDLGINTERFACE_H
