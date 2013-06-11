//
//          Copyright (c) 1990-2011, Scientific Toolworks, Inc.
//
// The License.txt file describes the conditions under which this software may be distributed.
//
// Author: Jason Haslam
//
// Additions Copyright (c) 2011 Archaeopteryx Software, Inc. d/b/a Wingware
// ScintillaQt.h - Qt specific subclass of ScintillaBase

#ifndef SCINTILLAQT_H
#define SCINTILLAQT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string>
#include <vector>
#include <map>

#include "scintilla.h"
#include "Platform.h"
#include "ilexer.h"
#include "svector.h"
#include "splitvector.h"
#include "partitioning.h"
#include "runstyles.h"
#include "contractionstate.h"
#include "cellbuffer.h"
#include "calltip.h"
#include "keymap.h"
#include "indicator.h"
#include "xpm.h"
#include "linemarker.h"
#include "style.h"
#include "autocomplete.h"
#include "viewstyle.h"
#include "charclassify.h"
#include "decoration.h"
#include "document.h"
#include "selection.h"
#include "positioncache.h"
#include "editor.h"
#include "scintillabase.h"

#ifdef SCI_LEXER
#include "SciLexer.h"
#include "propsetsimple.h"
#endif

#include <qobject>
#include <qabstractscrollarea>
#include <qaction>
#include <qclipboard>
#include <qpaintevent>

#ifdef SCI_NAMESPACE
namespace Scintilla {
#endif

class ScintillaQt : public QObject, public ScintillaBase {
	Q_OBJECT

public:
	ScintillaQt(QAbstractScrollArea *parent);
	virtual ~ScintillaQt();

signals:
	void horizontalScrolled(int value);
	void verticalScrolled(int value);
	void horizontalRangeChanged(int max, int page);
	void verticalRangeChanged(int max, int page);

	void notifyParent(SCNotification scn);
	void notifyChange();

	// Clients can use this hook to add additional
	// formats (e.g. rich text) to the MIME data.
	void aboutToCopy(QMimeData *data);

	void command(uptr_t wParam, sptr_t lParam);

private slots:
	void tick();
	void onIdle();
	void execCommand(QAction *action);
	void SelectionChanged();

private:
	virtual void Initialise();
	virtual void Finalise();
	virtual bool DragThreshold(Point ptStart, Point ptNow);
	virtual bool ValidCodePage(int codePage) const;

private:
	virtual void ScrollText(int linesToMove);
	virtual void SetVerticalScrollPos();
	virtual void SetHorizontalScrollPos();
	virtual bool ModifyScrollBars(int nMax, int nPage);
	virtual void ReconfigureScrollBars();
	void CopyToModeClipboard(const SelectionText &selectedText, QClipboard::Mode clipboardMode_);
	virtual void Copy();
	virtual void CopyToClipboard(const SelectionText &selectedText);
	void PasteFromMode(QClipboard::Mode clipboardMode_);
	virtual void Paste();
	virtual void ClaimSelection();
	virtual void NotifyChange();
	virtual void NotifyFocus(bool focus);
	virtual void NotifyParent(SCNotification scn);
	virtual void SetTicking(bool on);
	virtual bool SetIdle(bool on);
	virtual void SetMouseCapture(bool on);
	virtual bool HaveMouseCapture();
	virtual void StartDrag();
	int CharacterSetOfDocument() const;
	const char *CharacterSetIDOfDocument() const;
	QString StringFromDocument(const char *s) const;
	QByteArray BytesForDocument(const QString &text) const;
	virtual CaseFolder *CaseFolderForEncoding();
	virtual std::string CaseMapString(const std::string &s, int caseMapping);

	virtual void CreateCallTipWindow(PRectangle rc);
	virtual void AddToPopUp(const char *label, int cmd = 0, bool enabled = true);
	virtual sptr_t WndProc(unsigned int iMessage, uptr_t wParam, sptr_t lParam);
	virtual sptr_t DefWndProc(unsigned int iMessage, uptr_t wParam, sptr_t lParam);

	static sptr_t DirectFunction(ScintillaQt *sciThis,
				     unsigned int iMessage, uptr_t wParam, sptr_t lParam);

protected:

	void PartialPaint(const PRectangle &rect);

	void DragEnter(const Point &point);
	void DragMove(const Point &point);
	void DragLeave();
	void Drop(const Point &point, const QMimeData *data, bool move);

private:
	QAbstractScrollArea *scrollArea;

	int vMax, hMax;   // Scroll bar maximums.
	int vPage, hPage; // Scroll bar page sizes.

	bool haveMouseCapture;
	bool dragWasDropped;
	int rectangularSelectionModifier;

	friend class ScintillaEditBase;
};

#ifdef SCI_NAMESPACE
}
#endif

#endif // SCINTILLAQT_H