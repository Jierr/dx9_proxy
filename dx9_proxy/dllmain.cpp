// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"

#define MAX_PNAME_LEN 2048

extern HINSTANCE hLib;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
				hLib = NULL;
			break;

		case DLL_PROCESS_DETACH:
		{
			FILE* flog = NULL;
			char pname[MAX_PNAME_LEN] = { 0, };
			int plen = MAX_PNAME_LEN - 1;
		
			fopen_s(&flog, "C:\\logs\\d3d9.txt", "a+");
			if (flog)
			{
				if (GetModuleFileNameA(NULL, pname, plen) > 0)
				{
					pname[plen] = 0;
					fprintf(flog, "%s", pname);
				}
				fclose(flog);
				flog = NULL;
			}
			/*
			wstringstream wmsg;
			wmsg.str(L"");
			wmsg << left << setw(25) << L"DrawPrimitive"; wmsg << MI3dDevice::stat.DrawPrimitive << L"\r\n";
			wmsg << left << setw(25) << L"DrawIndexedPrimitive"; wmsg << MI3dDevice::stat.DrawIndexedPrimitive << L"\r\n";
			wmsg << left << setw(25) << L"DrawPrimitiveUP"; wmsg << MI3dDevice::stat.DrawPrimitiveUP << L"\r\n";
			wmsg << left << setw(25) << L"DrawIndexedPrimitiveUP"; wmsg << MI3dDevice::stat.DrawIndexedPrimitiveUP << L"\r\n";
			wmsg << left << setw(25) << L"DrawRectPatch"; wmsg << MI3dDevice::stat.DrawRectPatch << L"\r\n";
			wmsg << left << setw(25) << L"DrawTriPatch"; wmsg << MI3dDevice::stat.DrawTriPatch << L"\r\n";
			wmsg << left << setw(25) << L"SetStreamSource"; wmsg << MI3dDevice::stat.SetStreamSource << L"\r\n";
			wmsg << L"Draw: " << (MI3dDevice::stat.DrawPrimitive + MI3dDevice::stat.DrawIndexedPrimitive + MI3dDevice::stat.DrawPrimitiveUP +
				MI3dDevice::stat.DrawIndexedPrimitiveUP + MI3dDevice::stat.DrawRectPatch + MI3dDevice::stat.DrawTriPatch);
			wmsg << L" == Set: " << MI3dDevice::stat.SetStreamSource;
			MessageBoxW(NULL, wmsg.str().c_str(), L"Calls", MB_OK);
			*/
			//MessageBoxA(NULL, "DLL detached!", "Done", MB_OK);
			if (hLib != NULL)
				FreeLibrary(hLib);
			//MessageBoxA(NULL, "D3D9 freed!", "Done", MB_OK);
			break;
		}


		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}

