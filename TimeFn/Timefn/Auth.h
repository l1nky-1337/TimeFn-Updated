#include <string>
#include <stdlib.h> 
#include <windows.h>
#include <tlhelp32.h>
#include <time.h>

struct App {
	std::string Name;
	std::string Path;
	const void* Data;
	int Size;
};

namespace Regedit {
	void Create(HKEY Path, LPCTSTR SubKey, LPCTSTR Name, DWORD Type, std::string Data) {
		HKEY NewKey;
		RegCreateKeyEx(Path, SubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_32KEY, NULL, &NewKey, NULL);
		RegSetValueEx(NewKey, Name, 0, Type, (LPBYTE)Data.c_str(), strlen(Data.c_str()) * sizeof(char));
		RegCloseKey(NewKey);
	}

	void Delete(HKEY Path, LPCTSTR SubKey) {
		RegDeleteKeyEx(Path, SubKey, KEY_ALL_ACCESS | KEY_WOW64_32KEY, 0);
	}

	void Write(HKEY Path, LPCTSTR SubKey, LPCTSTR Name, DWORD Type, std::string Data) {
		HKEY NewKey;
		RegOpenKey(Path, SubKey, &NewKey);
		RegSetValueEx(NewKey, Name, 0, Type, (LPBYTE)Data.c_str(), strlen(Data.c_str()) * sizeof(char));
		RegCloseKey(NewKey);
	}

	std::string Read(HKEY Path, LPCTSTR SubKey, LPCTSTR Name, DWORD Type) {
		HKEY CurrentKey;
		TCHAR Value[255];
		DWORD Length = sizeof(Value);
		RegOpenKey(Path, SubKey, &CurrentKey);
		RegQueryValueEx(CurrentKey, Name, NULL, &Type, (LPBYTE)&Value, &Length);
		RegCloseKey(CurrentKey);
		return Value;
	}
}

namespace Process {
	void Start(std::string Path, std::string CommandLine = "", bool WaitForExit = false) {
		STARTUPINFO StartInfo = { sizeof(StartInfo) };
		PROCESS_INFORMATION ProcessInfo;
		if (CreateProcess(Path.c_str(), NULL, NULL, NULL, TRUE, 0, NULL, NULL, &StartInfo, &ProcessInfo)) {
			if (WaitForExit == true) {
				WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
				CloseHandle(ProcessInfo.hProcess);
				CloseHandle(ProcessInfo.hThread);
			}
		}
	}

	void Stop(std::string ProcessName) {
		DWORD ProcessID = 0;
		{
			PROCESSENTRY32 ProcessEntry;
			HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
			if (Process32First(Snapshot, &ProcessEntry)) {
				do {
					if (!lstrcmpi(ProcessEntry.szExeFile, ProcessName.c_str())) {
						CloseHandle(Snapshot);
						ProcessID = ProcessEntry.th32ProcessID;
					}
				} while (Process32Next(Snapshot, &ProcessEntry));
			}
		}
		if (ProcessID != 0) {
			HANDLE Process = OpenProcess(PROCESS_TERMINATE, FALSE, ProcessID);
			if (Process != NULL) {
				TerminateProcess(Process, 0);
				CloseHandle(Process);
			}
		}
	}
}

namespace HEX {
	std::string Encrypt(std::string Text) {
		static const char HexDigits[] = "0123456789ABCDEF";
		std::string Output;
		Output.reserve(Text.length() * 2);
		for (unsigned char c : Text) {
			Output.push_back(HexDigits[c >> 4]);
			Output.push_back(HexDigits[c & 15]);
		}
		return Output;
	}

	int HexValue(unsigned char HexDigits) {
		static const signed char HexValues[256] = {
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
			-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		};
		return HexValues[HexDigits];
	}

	std::string Decrypt(std::string Text) {
		const auto len = Text.length();
		std::string Output;
		Output.reserve(len / 2);
		for (auto it = Text.begin(); it != Text.end();) {
			int hi = HexValue(*it++);
			int lo = HexValue(*it++);
			Output.push_back(hi << 4 | lo);
		}
		return Output;
	}
}


std::string GetProcessName() {
	std::string ProcessName;
	PROCESSENTRY32 ProcessEntry;
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(Snapshot, &ProcessEntry)) {
		do {
			if (GetCurrentProcessId() == ProcessEntry.th32ProcessID) {
				CloseHandle(Snapshot);
				ProcessName = ProcessEntry.szExeFile;
			}

		} while (Process32Next(Snapshot, &ProcessEntry));
	}
	return ProcessName;
}

std::string CreateKey() {
	std::string Time = std::to_string(((time(0) * 98765) / 2));
	Time = HEX::Encrypt(Time);
	std::string Key(Time.rbegin(), Time.rend());
	return Key;
}

bool CheckKey() {
	std::string KeySubPath = "Hardware\\Description\\System\\CentralProcessor\\";
	KeySubPath += GetProcessName();
	std::string Key = Regedit::Read(HKEY_LOCAL_MACHINE, KeySubPath.c_str(), "AuthKey", REG_SZ);

	std::string newKey(Key.rbegin(), Key.rend());
	newKey = HEX::Decrypt(newKey);

	unsigned long long Time;
	try
	{
		Time = std::stoull(newKey);
	}
	catch (const std::exception&)
	{
		return false;
	}

	Time = (Time * 2) / 98765;

	time_t NowTime = time(0);
	time_t OldTime = Time;
	int CheckMinute = difftime(NowTime, OldTime) / (60);

	Regedit::Delete(HKEY_LOCAL_MACHINE, KeySubPath.c_str());
	if (CheckMinute <= 2) {
		return true;
	}
	else {
		return false;
	}
}

void StartApp(App CurrentApp) {
	std::string Path = CurrentApp.Path + CurrentApp.Name;
	{
		FILE* pFile;
		pFile = fopen(Path.c_str(), "wb");
		fwrite(CurrentApp.Data, sizeof(char), CurrentApp.Size, pFile);
		fclose(pFile);
	}
	std::string KeySubPath = "Hardware\\Description\\System\\CentralProcessor\\";
	KeySubPath += CurrentApp.Name;
	Regedit::Create(HKEY_LOCAL_MACHINE, KeySubPath.c_str(), "AuthKey", REG_SZ, CreateKey());
	Process::Start(Path);
}