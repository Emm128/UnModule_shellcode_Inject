// Unmodule_Inject.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include<Windows.h>
#include"UnModuleInject.h"
//EnablePriviledge(SE_DEBUG_NAME);
BOOL WINAPI EnablePriviledge(LPCTSTR lpSystemName/*��Ȩ����*/)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp = { 1 };
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY | TOKEN_QUERY_SOURCE, &hToken))
	{
		if (LookupPrivilegeValue(NULL, lpSystemName, &tkp.Privileges[0].Luid))
		{
			tkp.PrivilegeCount = 1;
			tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
			if (GetLastError() != ERROR_SUCCESS)
			{
				CloseHandle(hToken);
				return FALSE;
			}
		}
		CloseHandle(hToken);
	}
	return TRUE;
}


int _tmain(int argc, _TCHAR* argv[])
{
	//ȷ�������� �Ƕ���λ�ģ�
	//ȷ��Ŀ������Ƕ���λ��

	//HMODULE h = LoadLibraryA("C:\\Users\\storm\\Desktop\\Desktop\\Desktop\\Unmodule_Inject\\Debug\\Dll1.dll");
	char szFileName[] = "C:\\DLLtest.dll";
	//char szFileName[] ="C:\\Users\\storm\\Desktop\\Desktop\\Desktop\\Unmodule_Inject\\x64\\Debug\\Dll1.dll";
	DWORD dwProcessId = 7480;
	EnablePriviledge(SE_DEBUG_NAME);
	HANDLE hFile = CreateFileA(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		DWORD filesize = GetFileSize(hFile, NULL);
		if(filesize != NULL)
		{
			UCHAR *buffer = new UCHAR[filesize];        //���һλΪ'\0',C-Style�ַ����Ľ�������
			DWORD readsize;
			if(ReadFile(hFile, buffer, filesize, &readsize, NULL) == TRUE && readsize == filesize)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
				//ModuleLessInject(hProcess, buffer, filesize, NULL, NULL, NULL);
				Wow64ModuleLessInjectToX64(hProcess, buffer, filesize, NULL, "P", NULL);

				//X64ModuleLessInjectToWow64(hProcess, buffer, filesize, NULL, NULL, NULL);
			}
		}
	}
	
	system("pause");
	return 0;
}

