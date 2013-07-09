/**
* vsd2svg-win.cpp Convert VSD files into SVG files with Windows GUI
*
* (c) 2011-2013 Steffen Macke <sdteffen@sdteffen.de>
*
* http://dia-installer.de/vsd2svg
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
* 
* Uses code from libvisio
* Copyright (C) 2011 Fridrich Strba <fridrich.strba@bluewin.ch>
* Copyright (C) 2011 Eilidh McAdam <tibbylickle@gmail.com>
*/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <libvisio/libvisio.h>
#include <libwpd-stream/libwpd-stream.h>
#include <libwpd/libwpd.h>
#include <windows.h>
#include <config.h>
#include <vsd2svg-win.h>

using namespace std;

char gszVersion[] = "vsd2svg-win 0.1.0";
unsigned giDrawingPageCount = 0;
libvisio::VSDStringVector output;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   LPSTR lpCmdLine, int nCmdShow)
{
	struct stat statbuf;
	LPWSTR *szArglist = NULL;
	int nArgs;
	wchar_t visiopathw[MAX_PATH] = { 0 };
	wchar_t lpwTmpVisio[MAX_PATH];
	char szTmpVisio[MAX_PATH];
	int iRetVal = 0;
	UINT uiACP = GetACP();
	HANDLE hReadTest = INVALID_HANDLE_VALUE;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (NULL == szArglist) {
		MessageBox(NULL, "CommandLineToArgW failed\n",
			   gszVersion, MB_ICONERROR);
		return -1;
	}
	if (2 < nArgs) {
		MessageBox(NULL,
			   "USAGE: vsd2svg-win [visiofile]",
			   gszVersion, MB_ICONERROR);
	}
	if (1 < nArgs) {
		hReadTest =
		    CreateFileW(szArglist[1], GENERIC_READ, 0, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
				NULL);
		if (INVALID_HANDLE_VALUE != hReadTest) {
			if (!CloseHandle(hReadTest))
				ExitWithError("CloseHandle failed");
			wcsncpy(visiopathw, szArglist[1], MAX_PATH);
		}
	}
	if (INVALID_HANDLE_VALUE == hReadTest) {
		OPENFILENAMEW ofn;
		HWND hwnd;

		ZeroMemory(&ofn, sizeof(ofn));
		ZeroMemory(&hwnd, sizeof(hwnd));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = visiopathw;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter =
		    L"Visio (*.VSD)\0*.VSD\0All (*.*)\0*.*\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileNameW(&ofn) != TRUE)
			return 1;
	}

	GetTempFilePath(szTmpVisio);

	iRetVal =
	    MultiByteToWideChar(uiACP, 0, szTmpVisio, -1, lpwTmpVisio,
				MAX_PATH);
	if (iRetVal > MAX_PATH || 0 == iRetVal)
		ExitWithError("ERROR: MultiByteToWideChar failed");

	if (0 == CopyFileW(visiopathw, lpwTmpVisio, FALSE))
		ExitWithError("ERROR: CopyFileW failed");

	if (-1 == stat(szTmpVisio, &statbuf)) {
		MessageBox(NULL,
			   "ERROR: File does not exist",
			   gszVersion, MB_ICONERROR);
		return 1;
	}

	WPXFileStream input(szTmpVisio);

	if (!libvisio::VisioDocument::isSupported(&input)) {
		MessageBox(NULL,
			   "ERROR: Unsupported file format (unsupported version) or file is encrypted!",
			   gszVersion, MB_ICONERROR);
		if (0 == DeleteFileA(szTmpVisio))
			MessageBox(NULL, "ERROR: DeleteFile failed",
				   gszVersion, MB_ICONERROR);
		return 1;
	}

	if (!libvisio::VisioDocument::generateSVG(&input, output)) {
		MessageBox(NULL,
			   "ERROR: SVG generation failed!",
			   gszVersion, MB_ICONERROR);
		if (0 == DeleteFileA(szTmpVisio))
			MessageBox(NULL, "ERROR: DeleteFile failed",
				   gszVersion, MB_ICONERROR);
		return 1;
	}
	delete(&input);
	if (0 == DeleteFileA(szTmpVisio))
		MessageBox(NULL, "ERROR: DeleteFile failed",
			   gszVersion, MB_ICONERROR);

	if (output.empty()) {
		ExitWithError("ERROR: No SVG document generated!");
	}

	giDrawingPageCount = output.size();

	if (0 < giDrawingPageCount) {
		HINSTANCE hinst = NULL;
		HWND hwndOwner = NULL;
		const char *lpszMessage = "Select a drawing page";
		HGLOBAL hgbl;
		LPDLGTEMPLATE lpdt;
		LPDLGITEMTEMPLATE lpdit;
		LPWORD lpw;
		LPWSTR lpwsz;
		LRESULT ret;
		int nchar;

		hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
		if (!hgbl)
			return -1;

		lpdt = (LPDLGTEMPLATE) GlobalLock(hgbl);

		lpdt->style =
		    WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME |
		    WS_CAPTION;
		lpdt->cdit = 4;	// Number of controls
		lpdt->x = 0;
		lpdt->y = 0;
		lpdt->cx = 155;
		lpdt->cy = 50;

		lpw = (LPWORD) (lpdt + 1);
		*lpw++ = 0;
		*lpw++ = 0;

		lpwsz = (LPWSTR) lpw;
		nchar =
		    1 + MultiByteToWideChar(CP_ACP, 0, gszVersion, -1,
					    lpwsz, 50);
		lpw += nchar;

		lpw = lpwAlign(lpw);
		lpdit = (LPDLGITEMTEMPLATE) lpw;
		lpdit->x = 45;
		lpdit->y = 35;
		lpdit->cx = 50;
		lpdit->cy = 12;
		lpdit->id = IDOK;
		lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;

		lpw = (LPWORD) (lpdit + 1);
		*lpw++ = 0xFFFF;
		*lpw++ = 0x0080;	// Button class

		lpwsz = (LPWSTR) lpw;
		nchar =
		    1 + MultiByteToWideChar(CP_ACP, 0, "OK", -1, lpwsz,
					    50);
		lpw += nchar;
		*lpw++ = 0;

		lpw = lpwAlign(lpw);
		lpdit = (LPDLGITEMTEMPLATE) lpw;
		lpdit->x = 100;
		lpdit->y = 35;
		lpdit->cx = 50;
		lpdit->cy = 12;
		lpdit->id = IDCANCEL;
		lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;

		lpw = (LPWORD) (lpdit + 1);
		*lpw++ = 0xFFFF;
		*lpw++ = 0x0080;	// Button class

		lpwsz = (LPWSTR) lpw;
		nchar =
		    1 + MultiByteToWideChar(CP_ACP, 0, "Cancel", -1, lpwsz,
					    50);
		lpw += nchar;
		*lpw++ = 0;

		lpw = lpwAlign(lpw);
		lpdit = (LPDLGITEMTEMPLATE) lpw;
		lpdit->x = 100;
		lpdit->y = 10;
		lpdit->cx = 50;
		lpdit->cy = 50;
		lpdit->id = ID_PAGE;
		lpdit->style =
		    CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD |
		    WS_OVERLAPPED | WS_VISIBLE;

		lpw = (LPWORD) (lpdit + 1);
		*lpw++ = 0xFFFF;
		*lpw++ = 0x0085;	// Combo box

		lpwsz = (LPWSTR) lpw;
		nchar =
		    1 + MultiByteToWideChar(CP_ACP, 0, "", -1, lpwsz, 50);
		lpw += nchar;
		*lpw++ = 0;

		lpw = lpwAlign(lpw);
		lpdit = (LPDLGITEMTEMPLATE) lpw;
		lpdit->x = 10;
		lpdit->y = 10;
		lpdit->cx = 80;
		lpdit->cy = 20;
		lpdit->id = ID_TEXT;
		lpdit->style = WS_CHILD | WS_VISIBLE | SS_LEFT;

		lpw = (LPWORD) (lpdit + 1);
		*lpw++ = 0xFFFF;
		*lpw++ = 0x0082;	// Static text

		for (lpwsz = (LPWSTR) lpw;
		     *lpwsz++ = (WCHAR) * lpszMessage++;);
		lpw = (LPWORD) lpwsz;
		*lpw++ = 0;

		GlobalUnlock(hgbl);
		ret = DialogBoxIndirect(hinst,
					(LPDLGTEMPLATE) hgbl,
					hwndOwner, (DLGPROC) PageDlgProc);
		GlobalFree(hgbl);

	}
	return WritePage(0);

	return 0;
}

int WritePage(unsigned page)
{
	ofstream svgfile;
	char szTmpSvg[MAX_PATH];
	wchar_t lpwTmpSvg[MAX_PATH];
	wchar_t lpwSvg[MAX_PATH] = { 0 };
	int iRetVal = 0;
	OPENFILENAMEW ofn;
	HWND hwnd;

	GetTempFilePath(szTmpSvg);

	svgfile.open(szTmpSvg);
	svgfile <<
	    "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
	svgfile << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"";
	svgfile <<
	    " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";

	svgfile << output[page].cstr() << std::endl;
	svgfile.close();

	iRetVal =
	    MultiByteToWideChar(CP_ACP, 0, szTmpSvg, -1, lpwTmpSvg,
				MAX_PATH);
	if (iRetVal > MAX_PATH || 0 == iRetVal) {
		DeleteFileWithMessage(szTmpSvg);
		ExitWithError("ERROR: MultiByteToWideChar failed");
	}

	ZeroMemory(&ofn, sizeof(ofn));
	ZeroMemory(&hwnd, sizeof(hwnd));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = lpwSvg;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter =
	    L"Scalable Vector Graphics (*.SVG)\0*.SVG\0All (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileNameW(&ofn) != TRUE)
		exit(1);

	if (0 == CopyFileW(lpwTmpSvg, lpwSvg, FALSE)) {
		DeleteFileWithMessage(szTmpSvg);
		ExitWithError("ERROR: CopyFileW failed");
	}

	DeleteFileWithMessage(szTmpSvg);

	exit(0);
}

BOOL DeleteFileWithMessage(const char *file)
{
	BOOL result = DeleteFileA(file);
	if (0 == result)
		MessageBox(NULL, "ERROR: DeleteFile failed", gszVersion,
			   MB_ICONERROR);
	return result;
}

void ExitWithError(const char *msg)
{
	MessageBox(NULL, msg, gszVersion, MB_ICONERROR);
	exit(1);
}

void GetTempFilePath(char *path)
{
	char lpTempPathBuffer[MAX_PATH];
	DWORD dwRetVal = 0;

	dwRetVal = GetTempPathA(MAX_PATH, lpTempPathBuffer);
	if (dwRetVal > MAX_PATH || 0 == dwRetVal) {
		ExitWithError("ERROR: GetTempPath failed.");
	}

	if (0 == GetTempFileNameA(lpTempPathBuffer, "vsd2svg", 0, path)) {
		ExitWithError("ERROR: GetTempFileName failed.");
	}
}

BOOL CALLBACK PageDlgProc(HWND hDlg, UINT msg, WPARAM wParam,
			  LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		HWND hwndOwner;
		RECT rc, rcDlg, rcOwner;

		if ((hwndOwner = GetParent(hDlg)) == NULL) {
			hwndOwner = GetDesktopWindow();
		}

		GetWindowRect(hwndOwner, &rcOwner);
		GetWindowRect(hDlg, &rcDlg);
		CopyRect(&rc, &rcOwner);

		OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
		OffsetRect(&rc, -rc.left, -rc.top);
		OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

		SetWindowPos(hDlg,
			     HWND_TOP,
			     rcOwner.left + (rc.right / 2),
			     rcOwner.top + (rc.bottom / 2),
			     0, 0, SWP_NOSIZE);
		for (unsigned i = 0; i < giDrawingPageCount; i++) {
			char szPages[10];
			wchar_t lpwPages[10];
			int iRetVal = 0;

			snprintf(szPages, 10, "%d", i + 1);
			iRetVal =
			    MultiByteToWideChar(CP_ACP, 0, szPages, -1,
						lpwPages, 10);
			if (iRetVal > 10 || 0 == iRetVal) {
				ExitWithError
				    ("ERROR: MultiByteToWideChar failed");
			}
			SendMessage(GetDlgItem(hDlg, ID_PAGE),
				    (UINT) CB_ADDSTRING, (WPARAM) 0,
				    (LPARAM) lpwPages);
		}
		SendMessage(GetDlgItem(hDlg, ID_PAGE), (UINT) CB_SETCURSEL,
			    (WPARAM) 0, (LPARAM) 0);
		SetFocus(GetDlgItem(hDlg, ID_PAGE));
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			unsigned page;
			page =
			    SendMessage(GetDlgItem(hDlg, ID_PAGE),
					CB_GETCURSEL, (WPARAM) 0,
					(LPARAM) 0);
			DestroyWindow(hDlg);
			if (CB_ERR == page) {
				ExitWithError
				    ("ERROR: No item is selected");
			}
			WritePage(page);
			return TRUE;
			break;
		case IDCANCEL:
			DestroyWindow(hDlg);
			exit(1);
			break;
		}
		break;
	}
	return FALSE;
}

LPWORD lpwAlign(LPWORD lpIn)
{
	ULONG ul;

	ul = (ULONG) lpIn;
	ul++;
	ul >>= 1;
	ul <<= 1;
	return (LPWORD) ul;
}
