ProcessThread::ProcessThread(const TCHAR *appName, const TCHAR *cmd, const TCHAR *cDir, HWND hwnd) : _hwnd(hwnd)  {
		lstrcpy(_command, cmd);
		lstrcpy(_curDir, cDir);
	};

BOOL ProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPI ProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

bool ProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};

ProcessThread::ProcessThread(const TCHAR *appName, const TCHAR *cmd, const TCHAR *cDir, HWND hwnd) : _hwnd(hwnd)  {
		lstrcpy(_command, cmd);
		lstrcpy(_curDir, cDir);
	};

BOOL ProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPI ProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

bool ProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};

ProcessThread::ProcessThread(const TCHAR *appName, const TCHAR *cmd, const TCHAR *cDir, HWND hwnd) : _hwnd(hwnd)  {
		lstrcpy(_command, cmd);
		lstrcpy(_curDir, cDir);
	};

BOOL ProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPI ProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

bool ProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};

ProcessThread::ProcessThread(const TCHAR *appName, const TCHAR *cmd, const TCHAR *cDir, HWND hwnd) : _hwnd(hwnd)  {
		lstrcpy(_command, cmd);
		lstrcpy(_curDir, cDir);
	};

BOOL ProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPI ProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

bool ProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};

ProcessThread::ProcessThread(const TCHAR *appName, const TCHAR *cmd, const TCHAR *cDir, HWND hwnd) : _hwnd(hwnd)  {
		lstrcpy(_command, cmd);
		lstrcpy(_curDir, cDir);
	};

BOOL ProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPI ProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

bool ProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};

ProcessThread::ProcessThread(const TCHAR *appName, const TCHAR *cmd, const TCHAR *cDir, HWND hwnd) : _hwnd(hwnd)  {
		lstrcpy(_command, cmd);
		lstrcpy(_curDir, cDir);
	};

BOOL ProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPI ProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

bool ProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};

BOOLProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPIProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

boolProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};

BOOLProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPIProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

boolProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};

BOOL ProcessThread::run() {

		_hProcessThread = ::CreateThread(NULL, 0, staticLauncher, this, 0, NULL);

		::WaitForSingleObject(hEvent, INFINITE);

		::CloseHandle(hEvent);
		return TRUE;
	};

WINAPI ProcessThread::staticLauncher(void *myself)  {
		return TRUE;
	};

bool ProcessThread::launch()  {
		HWND hwnd = _hwnd;
		TCHAR appName[256];
		lstrcpy(appName, _appName);
		HANDLE hMyself = _hProcessThread;

		Process process(_command, _curDir);

		if(!::SetEvent(hEvent))
		{
			systemMessage(TEXT("Thread launcher"));
		}

		process.run();
		
		int code = process.getExitCode();
		TCHAR codeStr[256];
		generic_sprintf(codeStr, TEXT("%s : %0.4X"), appName, code);
		::MessageBox(hwnd, process.getStdout(), codeStr, MB_OK);
		
		if (process.hasStderr())
			::MessageBox(hwnd, process.getStderr(), codeStr, MB_OK);

		::CloseHandle(hMyself);
		return true;
	};
