/**
* vsd2svg-win.h Convert VSD files into SVG files with Windows GUI
*
* (c) 2013 Steffen Macke <sdteffen@sdteffen.de>
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
    
#define ID_PAGE   100
#define ID_TEXT   200

BOOL DeleteFileWithMessage(const char*);void ExitWithError(const char *);
void GetTempFilePath(char *);LPWORD lpwAlign(LPWORD);
BOOL CALLBACK PageDlgProc(HWND, UINT, WPARAM, LPARAM);
int WritePage(unsigned);