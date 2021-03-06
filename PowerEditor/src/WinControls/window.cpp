#include "precompiledheaders.h"

Window::Window(): _hInst(NULL), _hParent(NULL), _hSelf(NULL) {};
Window::~Window() {};

void Window::init(HINSTANCE hInst, HWND parent) {
	_hInst = hInst;
	_hParent = parent;
}

void Window::reSizeTo(RECT & rc) {
	::MoveWindow(_hSelf, rc.left, rc.top, rc.right, rc.bottom, TRUE);
	redraw();
};

void Window::reSizeToWH(RECT & rc) {
	::MoveWindow(_hSelf, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);
	redraw();
};

void Window::display(bool toShow) const {
	::ShowWindow(_hSelf, toShow?SW_SHOW:SW_HIDE);
};

void Window::redraw(bool forceUpdate) const {
	::InvalidateRect(_hSelf, NULL, TRUE);
	if (forceUpdate)
		::UpdateWindow(_hSelf);
};

void Window::getClientRect(RECT & rc) const {
	::GetClientRect(_hSelf, &rc);
};

void Window::getWindowRect(RECT & rc) const {
	::GetWindowRect(_hSelf, &rc);
};

int Window::getWidth() const  {
	RECT rc;
	::GetClientRect(_hSelf, &rc);
	return (rc.right - rc.left);
};

int Window::getHeight() const  {
	RECT rc;
	::GetClientRect(_hSelf, &rc);
	if (::IsWindowVisible(_hSelf) == TRUE)
		return (rc.bottom - rc.top);
	return 0;
};

bool Window::isVisible() const  {
  	return (::IsWindowVisible(_hSelf)?true:false);
};

HWND Window::getHSelf() const  {
	//assert(_hSelf != 0);
	return _hSelf;
};

HWND Window::getHParent() const  {
	return _hParent;
};

void Window::getFocus() const  {
	::SetFocus(_hSelf);
};

HINSTANCE Window::getHinst() const  {
	//assert(_hInst != 0);
	return _hInst;
};
