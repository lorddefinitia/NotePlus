int FileManager::getNrBuffers()  { return _nrBufs; };
Buffer * FileManager::getBufferByID(BufferID id)  {return (Buffer*)id;}
 FileManager * FileManager::getInstance()  {return _pSelf;};
void FileManager::destroyInstance()  { delete _pSelf; };
void FileManager::increaseDocNr()  {_nextNewNumber++;};
const TCHAR * FileManager::getFullPathName() const  {
		return _fullPathName.c_str();
	};

const TCHAR * FileManager::getFileName() const  { return _fileName; };
BufferID FileManager::getID() const  {
		return _id;
	};

void FileManager::increaseRecentTag()  {
		_recentTag = ++_recentTagCtr;
		doNotify(BufferChangeRecentTag);
	};

long FileManager::getRecentTag() const  {
		return _recentTag;
	};

bool FileManager::isDirty() const  {
        return _isDirty;
    };

bool FileManager::isReadOnly() const  {
        return (_isUserReadOnly || _isFileReadOnly);
    };

bool FileManager::isUntitled() const  {
		return (_currentStatus == DOC_UNNAMED);
	};

bool FileManager::getFileReadOnly() const  {
        return _isFileReadOnly;
    };

void FileManager::setFileReadOnly(bool ro)  {
		_isFileReadOnly = ro;
		doNotify(BufferChangeReadonly);
	};

bool FileManager::getUserReadOnly() const  {
        return _isUserReadOnly;
    };

void FileManager::setUserReadOnly(bool ro)  {
		_isUserReadOnly = ro;
		doNotify(BufferChangeReadonly);
    };

formatType FileManager::getFormat() const  {
		return _format;
	};

void FileManager::setFormat(formatType format)  {
		_format = format;
		doNotify(BufferChangeFormat);
	};

LangType FileManager::getLangType() const  {
		return _lang;
	};

UniMode FileManager::getUnicodeMode() const  {
		return _unicodeMode;
	};

void FileManager::setUnicodeMode(UniMode mode)  {
		_unicodeMode = mode;
		doNotify(BufferChangeUnicode | BufferChangeDirty);
	};

int FileManager::getEncoding() const  {
		return _encoding;
	};

void FileManager::setEncoding(int encoding)  {
		_encoding = encoding;
        doNotify(BufferChangeUnicode | BufferChangeDirty);
	};

DocFileStatus FileManager::getStatus() const  {
		return _currentStatus;
	};

Document FileManager::getDocument()  {
		return _doc;
	};

void FileManager::setDirty(bool dirty)  {
		_isDirty = dirty;
		doNotify(BufferChangeDirty);
	};

bool FileManager::isUserDefineLangExt() const  {
		return (_userLangExt[0] != '\0');
	};

const TCHAR * FileManager::getUserDefineLangName() const  {
		return _userLangExt.c_str();
	};

const TCHAR * FileManager::getCommentLineSymbol() const  {
		Lang *l = getCurrentLang();
		if (!l)
			return NULL;
		return l->_pCommentLineSymbol;

	};

const TCHAR * FileManager::getCommentStart() const  {
		Lang *l = getCurrentLang();
		if (!l)
			return NULL;
		return l->_pCommentStart;
	};

const TCHAR * FileManager::getCommentEnd() const  {
		Lang *l = getCurrentLang();
		if (!l)
			return NULL;
		return l->_pCommentEnd;
	};

bool FileManager::getNeedsLexing() const  {
		return _needLexer;
	};

void FileManager::setNeedsLexing(bool lex)  {
		_needLexer = lex;
		doNotify(BufferChangeLexing);
	};

bool FileManager::getNeedReload()  {
		return _needReloading;
	}

void FileManager::setNeedReload(bool reload)  {
		_needReloading = reload;
	}

int FileManager::docLength() const  {
		return _pManager->docLength(_id);
	};

void FileManager::setStatus(DocFileStatus status)  {
		_currentStatus = status;
		doNotify(BufferChangeStatus);
	}

void FileManager::doNotify(int mask)  {
		if (_canNotify)
			_pManager->beNotifiedOfBufferChange(this, mask); 
	};

