#include "dockingdlginterface.h"

DockingDlgInterface::DockingDlgInterface(): StaticDialog(), _HSource(NULL),\
	_dlgID(-1), _isFloating(TRUE), _iDockedPos(0), _pluginName(TEXT("")) {};

DockingDlgInterface::DockingDlgInterface(int dlgID): StaticDialog(), _HSource(NULL),\
	_dlgID(dlgID), _isFloating(TRUE), _iDockedPos(0), _pluginName(TEXT("")) {};
	
DockingDlgInterface::~DockingDlgInterface() {};

void DockingDlgInterface::init(HINSTANCE hInst, HWND parent)	 {
	StaticDialog::init(hInst, parent);
	TCHAR temp[MAX_PATH];
	::GetModuleFileName((HMODULE)hInst, temp, MAX_PATH);
	_moduleName = PathFindFileName(temp);
};

void DockingDlgInterface::create(tTbData * data, bool isRTL) {
	StaticDialog::create(_dlgID, isRTL);
	TCHAR temp[MAX_PATH];
	::GetWindowText(_hSelf, temp, MAX_PATH);
	_pluginName = temp;
      // user information
	data->hClient		= _hSelf;
	data->pszName		= (TCHAR *)_pluginName.c_str();

	// supported features by plugin
	data->uMask			= 0;

	// additional info
	data->pszAddInfo	= NULL;
};

void DockingDlgInterface::updateDockingDlg()  {
	::SendMessage(_hParent, NPPM_DMMUPDATEDISPINFO, 0, (LPARAM)_hSelf);
}

void DockingDlgInterface::destroy()  {
};

void DockingDlgInterface::display(bool toShow) const  {
	::SendMessage(_hParent, toShow?NPPM_DMMSHOW:NPPM_DMMHIDE, 0, (LPARAM)_hSelf);
};

const TCHAR * DockingDlgInterface::getPluginFileName() const  {
	return _moduleName.c_str();
};
