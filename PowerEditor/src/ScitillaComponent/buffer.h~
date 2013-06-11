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
#include "parameters.h"
#include "scintillaeditview.h"
#include "encodingmapper.h"

#ifndef BUFFER_H
#define BUFFER_H

class Buffer;
typedef Buffer* BufferID;	//each buffer has unique ID by which it can be retrieved
#define BUFFER_INVALID	(BufferID)0

typedef sptr_t Document;

enum DocFileStatus{
	DOC_REGULAR = 0x01,	//should not be combined with anything
	DOC_UNNAMED = 0x02,	//not saved (new ##)
	DOC_DELETED = 0x04, //doesn't exist in environment anymore, but not DOC_UNNAMED
	DOC_MODIFIED = 0x08	//File in environment has changed
};

enum BufferStatusInfo {
	BufferChangeLanguage	= 0x001,	//Language was altered
	BufferChangeDirty		= 0x002,	//Buffer has changed dirty state
	BufferChangeFormat		= 0x004,	//EOL type was changed
	BufferChangeUnicode		= 0x008,	//Unicode type was changed
	BufferChangeReadonly	= 0x010,	//Readonly state was changed, can be both file and user
	BufferChangeStatus		= 0x020,	//Filesystem Status has changed
	BufferChangeTimestamp	= 0x040,	//Timestamp was changed
	BufferChangeFilename	= 0x080,	//Filename was changed
	BufferChangeRecentTag	= 0x100,	//Recent tag has changed
	BufferChangeLexing		= 0x200,	//Document needs lexing
	BufferChangeMask		= 0x3FF		//Mask: covers all changes
};

//const int userLangNameMax = 16;
const TCHAR UNTITLED_STR[] = TEXT("new ");

#endif //BUFFER_H
