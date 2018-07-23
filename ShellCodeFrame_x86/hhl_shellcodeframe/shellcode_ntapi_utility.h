#pragma once

#include <windows.h>
#include <stdio.h>
#include "nativeapi.h"
#include "ShellCode.h"



#ifdef __cplusplus
extern "C"
{
#endif

	int			my_sh_strcmp(const char *dst, const char *src);
	int			my_sh_stricmp(char *dst, char *src);				//�Ƚϴ�Сд������ char
	int			my_sh_wcsicmp(wchar_t * dst1,wchar_t * src1);		//�Ƚϴ�Сд������ wchar
	ULONG		my_sh_wcslen (wchar_t * wcs);
	int			my_sh_strlen ( char* str );
	char*		my_sh_strstr (char * str1,char * str2);				//������Сд����
	char*		my_sh_stristr(char* pString,char* pFind);			//������Сд������
	char *		my_sh_strupr(char *str);							//ת���ɴ�д�ַ�
	char *		my_sh_strlwr(char *s);								//ת����Сд�ַ�

	wchar_t*	my_sh_wcscat (wchar_t * dst,wchar_t * src);
	char*		my_sh_strcat (char * dst,const char * src);		

	int			my_sh_memcmp(void* pv1,void* pv2,size_t  cb);
	void*		my_sh_memcpy(void* pvDest,void* pvSrc,size_t cb);
	void*		my_sh_memset(void* pv,int c,size_t cb);
	void		my_sh_zeromem(PVOID Destination,SIZE_T Length);

	BOOLEAN		Is64Os();
#ifdef __cplusplus 
}
#endif



























void ShellCode_Ntapi_Utility_End();




