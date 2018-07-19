// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "atlstr.h"
#include "detours.h"
#include <tlhelp32.h> 
//#include "..\\ThreadLess\\ThreadLess.h"

#include "injector.h"

#if _WIN64
#pragma comment(lib,"injector64.lib")
#else
#pragma comment(lib,"injector32.lib")
#endif

#pragma comment(lib, "user32.lib")

//#if defined(WIN64) || defined(_WIN64)
//#pragma comment(lib,"detours64.lib")
//#else
//#pragma comment(lib,"detours.lib")
//#endif

typedef LONG NTSTATUS;  



HANDLE g_hLock = NULL;


HANDLE CreateRunLock()
{
	HANDLE	hEvent;
	DWORD	dwProcessId;
	WCHAR	szEventName[MAX_PATH];

	ZeroMemory(szEventName,sizeof(WCHAR)*MAX_PATH);

	dwProcessId = GetCurrentProcessId();
	swprintf_s(szEventName,MAX_PATH,L"Event_Index_%X",dwProcessId);

	hEvent = CreateEvent(NULL,FALSE,FALSE,szEventName);
	return hEvent;
}



#pragma region ������������
#ifdef  _WINDLL
// _����_stdcall(WINAPI) �����_fastcall��ô����@�滻_ @4�������ռ���ֽ���, ע�⵼��������extern "C" ������
/* __stdcall��ʹ������������ǰ���һ���»��ߣ������һ��@�ټ��ϲ������ֽ�����
����_MyFunction@4�Ĳ�����int iVariant������4���ֽ� __fastcall�� __stdcall���ƣ�
����ǰ��û���»��ߣ�����һ��@������@MyFunction@4 __cdecl����ʼ��������*/
#pragma comment(linker, "/EXPORT:RunDll=_RunDll@4,PRIVATE")
#endif
#pragma endregion

DWORD SecondThreadRoutine()
{
	CString strTemp;
	strTemp.Format(L"SecondThreadRoutine Thread Id is %d\r\n", GetCurrentThreadId());
	OutputDebugString(strTemp);
	int cnt = 0;
	while(TRUE)
	{
		strTemp.Format(L"SecondThreadRoutine cnt Id is %d\r\n", cnt++);
		OutputDebugString(strTemp);
		Sleep(5000);
	}
}

extern "C"
void WINAPI RunDll(LPCWSTR pszRunCmd)
{
	CString strTemp;
	strTemp.Format(L"szCommandLine: %s\r\n", pszRunCmd);
	OutputDebugString(strTemp);

	CThreadDisguiser::CreateDisguiseThread((LPTHREAD_START_ROUTINE)SecondThreadRoutine, NULL);
}



DWORD WINAPI FirstThreadRoutine( PVOID pParam )
{
	CString strTemp;
	strTemp.Format(L"FirstThreadRoutine Thread Id is %d\r\n", GetCurrentThreadId());
	OutputDebugString(strTemp);
	int cnt = 0;
	while(TRUE)
	{
		strTemp.Format(L"FirstThreadRoutine cnt Id is %d\r\n", cnt++);
		OutputDebugString(strTemp);
		Sleep(5000);
	}
	return 0;
}

DWORD WINAPI TestThread( PVOID pParam )
{
	CThreadDisguiser::CreateDisguiseThread((LPTHREAD_START_ROUTINE)FirstThreadRoutine, NULL);

	return 0;
}

BOOL EnableDebugPrivilege()
{  
	HANDLE hToken;  
	LUID sedebugnameValue;  
	TOKEN_PRIVILEGES tkp;  
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{  
		return   FALSE;  
	}  
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))  
	{  
		CloseHandle(hToken);  
		return FALSE;  
	}  
	tkp.PrivilegeCount = 1;  
	tkp.Privileges[0].Luid = sedebugnameValue;  
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{  
		CloseHandle(hToken);  
		return FALSE;  
	}  
	return TRUE;  
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
// 			DWORD dwProcessId = GetCurrentProcessId();
// 			CString strTemp;
// 			g_hLock = CreateRunLock();
// 			if (g_hLock == NULL)
// 			{
// 				break;
// 			}
// 
// 			if(lpReserved != NULL)
// 			{
// 				strTemp.Format(L"lpRevert: %s ProcessId: %d\r\n", (wchar_t*)lpReserved, dwProcessId);
// 				OutputDebugString(strTemp);
// 			}
// 			else
// 			{
// 				strTemp.Format(L"lpReserved is Null ProcessId: %d, FirstThreadRoutine: %X\r\n", dwProcessId, (DWORD)FirstThreadRoutine);
// 				OutputDebugString(strTemp);
// 			}
// 			
			static BOOL baaa = FALSE;
			if ( FALSE == baaa )
			{
				EnableDebugPrivilege();
				baaa = TRUE;
				//CreateThread(NULL,0,TestThread,NULL,0,NULL); // DllMain�в���ֱ�Ӵ���αװ�̣߳���������
				CThreadDisguiser::CreateDisguiseThread((LPTHREAD_START_ROUTINE)FirstThreadRoutine, NULL);
				//Sleep(10000000);
			}
			

			//ThreadLess::CreateHiddenThread((LPTHREAD_START_ROUTINE)FirstThreadRoutine, NULL);
			//ThreadLess::CreateHiddenThread((LPTHREAD_START_ROUTINE)SecondThreadRoutine, NULL);
			//Sleep(60000);
			
			//CThreadDisguiser::CreateDisguiseThread((LPTHREAD_START_ROUTINE)FirstThreadRoutine, NULL);
			//Sleep(2000);
		}
		
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

