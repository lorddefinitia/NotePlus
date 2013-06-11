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

#include "precompiledheaders.h"

#ifndef WINDOW_CONTROL_H
#define WINDOW_CONTROL_H

class Window
{
public:
	Window();
  virtual  ~Window ();

	virtual void init(HINSTANCE hInst, HWND parent);

	virtual void destroy() = 0;

  void display (bool toShow = true) const;
	
	virtual void reSizeTo(RECT & rc); // should NEVER be const !!!
	
	virtual void reSizeToWH(RECT & rc); // should NEVER be const !!!

  void  redraw (bool forceUpdate = false) const;
	
  void  getClientRect (RECT & rc) const;

  void  getWindowRect (RECT & rc) const;

  int  getWidth () const;

  int  getHeight () const;

  bool  isVisible () const;

  HWND  getHSelf () const;

  HWND  getHParent () const;

  void  getFocus () const;

  HINSTANCE  getHinst () const;
  protected:
	  HINSTANCE _hInst;
	  HWND _hParent;
	  HWND _hSelf;
  };

#endif //WINDOW_CONTROL_H


