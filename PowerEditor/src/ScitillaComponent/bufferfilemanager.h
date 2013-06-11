#include "buffer.h"
#include "notepad_plus.h"


#ifndef _BUFFER_FILE_MANAGER_H
#define _BUFFER_FILE_MANAGER_H
//File manager class maintains all buffers
class FileManager {
public:
	void init(Notepad_plus * pNotepadPlus, ScintillaEditView * pscratchTilla);

	//void activateBuffer(int index);	
	void checkFilesystemChanges();

    int  getNrBuffers () ;
	int getBufferIndexByID(BufferID id);
	Buffer * getBufferByIndex(int index);	//generates exception if index is invalid
Buffer *  getBufferByID (BufferID id) ;

	void beNotifiedOfBufferChange(Buffer * theBuf, int mask);

	void closeBuffer(BufferID, ScintillaEditView * identifer);		//called by Notepad++

	void addBufferReference(BufferID id, ScintillaEditView * identifer);	//called by Scintilla etc indirectly

	BufferID loadFile(const TCHAR * filename, Document doc = NULL, int encoding = -1);	//ID == BUFFER_INVALID on failure. If Doc == NULL, a new file is created, otherwise data is loaded in given document
	BufferID newEmptyDocument();
	//create Buffer from existing Scintilla, used from new Scintillas. If dontIncrease = true, then the new document number isnt increased afterwards.
	//usefull for temporary but neccesary docs
	//If dontRef = false, then no extra reference is added for the doc. Its the responsibility of the caller to do so
	BufferID bufferFromDocument(Document doc,  bool dontIncrease = false, bool dontRef = false);

	BufferID getBufferFromName(const TCHAR * name);
	BufferID getBufferFromDocument(Document doc);

	bool reloadBuffer(BufferID id);
	bool reloadBufferDeferred(BufferID id);
	bool saveBuffer(BufferID id, const TCHAR * filename, bool isCopy = false, generic_string * error_msg = NULL);
	bool deleteFile(BufferID id);
	bool moveFile(BufferID id, const TCHAR * newFilename);

	bool createEmptyFile(const TCHAR * path);

static FileManager *  getInstance () ;
void  destroyInstance () ;

void  increaseDocNr () ;

	int getFileNameFromBuffer(BufferID id, TCHAR * fn2copy);
	
	int docLength(Buffer * buffer) const;

	int getEOLFormatForm(const char *data) const;

private:
	FileManager() : _nextNewNumber(1), _nextBufferID(0), _pNotepadPlus(NULL), _nrBufs(0), _pscratchTilla(NULL){};
	~FileManager();
	static FileManager *_pSelf;

	Notepad_plus * _pNotepadPlus;
	ScintillaEditView * _pscratchTilla;
	Document _scratchDocDefault;

	int _nextNewNumber;

	std::vector<Buffer *> _buffers;
	BufferID _nextBufferID;
	size_t _nrBufs;

	bool loadFileData(Document doc, const TCHAR * filename, Utf8_16_Read * UnicodeConvertor, LangType language, int & encoding, formatType *pFormat = NULL);
};

#define MainFileManager FileManager::getInstance()

class Buffer
{
friend class FileManager;
public :
	//Loading a document: 
	//constructor with ID.
	//Set a reference (pointer to a container mostly, like DocTabView or ScintillaEditView)
	//Set the position manually if needed
	//Load the document into Scintilla/add to TabBar
	//The entire lifetime if the buffer, the Document has reference count of _atleast_ one
	//Destructor makes sure its purged
	Buffer(FileManager * pManager, BufferID id, Document doc, DocFileStatus type, const TCHAR *fileName);

	// this method 1. copies the file name
	//             2. determinates the language from the ext of file name
	//             3. gets the last modified time
	void setFileName(const TCHAR *fn, LangType defaultLang = L_TEXT);

const TCHAR *  getFullPathName () const ;

const TCHAR *  getFileName () const ;

BufferID  getID () const ;

void  increaseRecentTag () ;

long  getRecentTag () const ;

	bool checkFileState();

bool  isDirty () const ;

bool  isReadOnly () const ;

bool  isUntitled () const ;

bool  getFileReadOnly () const ;

void  setFileReadOnly (bool ro) ;

bool  getUserReadOnly () const ;

void  setUserReadOnly (bool ro) ;

formatType  getFormat () const ;

void  setFormat (formatType format) ;

LangType  getLangType () const ;

	void setLangType(LangType lang, const TCHAR * userLangName = TEXT(""));

UniMode  getUnicodeMode () const ;

void  setUnicodeMode (UniMode mode) ;

int  getEncoding () const ;

void  setEncoding (int encoding) ;

DocFileStatus  getStatus () const ;

Document  getDocument () ;

void  setDirty (bool dirty) ;

    void setPosition(const Position & pos, ScintillaEditView * identifier);
	Position & getPosition(ScintillaEditView * identifier);

	void setHeaderLineState(const std::vector<size_t> & folds, ScintillaEditView * identifier);
	const std::vector<size_t> & getHeaderLineState(const ScintillaEditView * identifier) const;

bool  isUserDefineLangExt () const ;

const TCHAR *  getUserDefineLangName () const ;

const TCHAR *  getCommentLineSymbol () const ;

const TCHAR *  getCommentStart () const ;

const TCHAR *  getCommentEnd () const ;

bool  getNeedsLexing () const ;

void  setNeedsLexing (bool lex) ;

	//these two return reference count after operation
	int addReference(ScintillaEditView * identifier);		//if ID not registered, creates a new Position for that ID and new foldstate
	int removeReference(ScintillaEditView * identifier);		//reduces reference. If zero, Document is purged

	void setHideLineChanged(bool isHide, int location);

	void setDeferredReload();

bool  getNeedReload () ;

void  setNeedReload (bool reload) ;

	/*
	pair<size_t, bool> getLineUndoState(size_t currentLine) const;
	void setLineUndoState(size_t currentLine, size_t undoLevel, bool isSaved = false);
	*/

int  docLength () const ;

	int getFileLength(); // return file length. -1 if file is not existing.

	enum fileTimeType {ft_created, ft_modified, ft_accessed};
	generic_string getFileTime(fileTimeType ftt);

    Lang * getCurrentLang() const;
private :
	FileManager * _pManager;
	bool _canNotify;
	int _references;							//if no references file inaccessible, can be closed
	BufferID _id;

	//document properties
	Document _doc;	//invariable
	LangType _lang;
	generic_string _userLangExt; // it's useful if only (_lang == L_USER)
	bool _isDirty;
	formatType _format;
	UniMode _unicodeMode;
	int _encoding;
	bool _isUserReadOnly;
	bool _needLexer;	//initially true
	//these properties have to be duplicated because of multiple references
	//All the vectors must have the same size at all times
	vector< ScintillaEditView * > _referees;
	vector< Position > _positions;
	vector< vector<size_t> > _foldStates;

	//vector< pair<size_t, pair<size_t, bool> > > _linesUndoState;

	//Environment properties
	DocFileStatus _currentStatus;
	time_t _timeStamp; // 0 if it's a new doc
	bool _isFileReadOnly;
	generic_string _fullPathName;
	TCHAR * _fileName;	//points to filename part in _fullPathName
	bool _needReloading;	//True if Buffer needs to be reloaded on activation

	long _recentTag;
	static long _recentTagCtr;

	void updateTimeStamp();

	int indexOfReference(const ScintillaEditView * identifier) const;

void  setStatus (DocFileStatus status) ;

void  doNotify (int mask) ;
};

#endif

