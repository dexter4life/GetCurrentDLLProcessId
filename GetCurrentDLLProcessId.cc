#include <tlhelp32.h>
#include <Windows.h>

DWORD GetCurrentDLLProcessId(DWORD dwPID, LPCTSTR lpModuleName)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	// Take a snapshot of all modules in the specified process.
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		return(FALSE);
	}

	// Set the size of the structure before using it.
	me32.dwSize = sizeof(MODULEENTRY32);

	// Retrieve information about the first module,
	// and exit if unsuccessful
	if (!Module32First(hModuleSnap, &me32))
	{
		CloseHandle(hModuleSnap);           // clean the snapshot object
		return(FALSE);
	}

	// Now walk the module list of the process,
	// and display information about each module
	do
	{
		if (wcsstr(me32.szModule, L"hookclient.dll")!=NULL) {
			return 	me32.th32ProcessID;
		}

	} while (Module32Next(hModuleSnap, &me32));

	CloseHandle(hModuleSnap);
	return(NULL);
}
