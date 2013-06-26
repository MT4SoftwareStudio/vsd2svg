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

using namespace std;

char gszVersion[] = "vsd2svg-win 0.1.0";

int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	int drawingpageno = 0;
	struct stat statbuf;
	libvisio::VSDStringVector output;
	LPWSTR *szArglist = NULL;
	int nArgs;
	wchar_t visiopath[MAX_PATH] = {0};

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if(NULL == szArglist)
	{
		MessageBox(NULL, "CommandLineToArgW failed\n",
			gszVersion, MB_ICONERROR);
		return -1;
	}
	if (4 < nArgs) {
		MessageBox (NULL,
		    "USAGE: vsd2svg-win [visiofile] [svgfile] [drawingpagenumber]",
		    gszVersion, MB_ICONERROR );
	}
	if ( 1 < nArgs)
	{
		StringCbCopyW(visiopath, MAX_PATH, szArglist[0]);
	}
	else
	{
			OPENFILENAME ofn;
			HWND hwnd;
			
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = visiopath;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFilter = "All\0*.*\0Visio\0*.VSD\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&ofn) != TRUE) 
	    			return -1;			
	}

	if(-1 == wstat(visiofile, &statbuf))
	{
		MessageBox (NULL,
			"ERROR: File does not exist",
			gszVersion, MB_ICONERROR);
		return 1;
	} 

	WPXFileStream input(visiofile);

	if (!libvisio::VisioDocument::isSupported(&input)) {
		cerr <<
		    "ERROR: Unsupported file format (unsupported version) or file is encrypted!"
		    << std::endl;
		return 1;
	}
/*
	if (!libvisio::VisioDocument::generateSVG(&input, output)) {
		std::cerr << "ERROR: SVG Generation failed!" << std::endl;
		return 1;
	}

	if (output.empty()) {
		std::cerr << "ERROR: No SVG document generated!" << std::
		    endl;
		return 1;
	}

	if (2 == argc)
		std::cout << output.
		    size() << " drawing pages in VSD document " << std::
		    endl;
	else {
		unsigned page = 0;
		if (4 == argc) {
			page = atoi(argv[3]) - 1;
			if ((0 > page) | (page >= output.size())) {
			      std:cerr <<
				    "ERROR: Please choose a drawing page number between 1 and "
				    << output.size() << "." << std::endl;
				return 1;
			}
		}
		ofstream svgfile;
		svgfile.open(argv[2]);
		svgfile <<
		    "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
		svgfile <<
		    "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"";
		svgfile <<
		    " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";

		svgfile << output[page].cstr() << std::endl;
		svgfile.close();
	} */

	return 0; 
}
