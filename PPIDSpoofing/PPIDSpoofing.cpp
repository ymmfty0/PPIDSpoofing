#include <Windows.h>
#include <cstdio>
#include <Psapi.h>

int main()
{

	STARTUPINFOEXA si;
	PROCESS_INFORMATION pi;

	SIZE_T attributeSize; 

	ZeroMemory(&si, sizeof(STARTUPINFOEXA));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	HANDLE parentProcessHandle = OpenProcess(MAXIMUM_ALLOWED, false, 19484);
	InitializeProcThreadAttributeList(NULL, 1, 0, &attributeSize);

	si.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, attributeSize);

	InitializeProcThreadAttributeList(si.lpAttributeList, 1, 0, &attributeSize);
	UpdateProcThreadAttribute(si.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_PARENT_PROCESS, &parentProcessHandle, sizeof(HANDLE), NULL, NULL);
	
	si.StartupInfo.cb = sizeof(STARTUPINFOEXA);
	CreateProcessA(NULL, (LPSTR)"Notepad", NULL, NULL, FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &si.StartupInfo, &pi);

	HANDLE hProc = pi.hProcess;
	DWORD childProcessId = GetProcessId(pi.hProcess);

	printf("[+] Current process ID %i\n", GetCurrentProcessId());
	printf("[+] Created process ID %i\n", childProcessId);

}

