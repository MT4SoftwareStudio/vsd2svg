/**
* vsd2svg.cpp Convert VSD files into SVG files
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
#include <sys/stat.h>
#include <librevenge-stream/librevenge-stream.h>
#include <librevenge-generators/librevenge-generators.h>
#include <librevenge/librevenge.h>
#include <libvisio/libvisio.h>
#include <strings.h>
#include <config.h>

using namespace std;
#define MAX_PATH 260

int main(int argc, char *argv[])
{
	int drawingpageno = 0;
	int allpages = 0;	// Either 0 or 1

	if ((2 > argc) || (4 < argc)
	    || ((2 == argc) && (((string) "-h") == argv[1])
		|| ((string) "--help" == argv[1]))) {
		cerr <<
		    "USAGE: vsd2svg [OPTION] visiofile [svgfile] [drawingpagenumber]"
		    << endl << endl << "  -a" << endl <<
		    "               extract all drawing pages, number svg files"
		    << endl << "  -v" << endl <<
		    "               display version number and exit" <<
		    endl << endl <<
		    "vsd2svg home page: <http://dia-installer.de/vsd2svg>"
		    << endl;
		return 1;
	}

	if ((string) "-v" == argv[1]) {
		cerr << "vsd2svg " << VERSION << endl;
		return 0;
	}

	if ((string) "-a" == argv[1]) {
		allpages = 1;
	}

	struct stat statbuf;
	if (-1 == stat(argv[1 + allpages], &statbuf)) {
		cerr <<
		    "ERROR: File '" << argv[1] << "' does not exist."
		    << endl;
		return 1;
	}

	librevenge::RVNGFileStream input(argv[1 + allpages]);

	if (!libvisio::VisioDocument::isSupported(&input)) {
		cerr <<
		    "ERROR: Unsupported file format (unsupported version) or file is encrypted!"
		    << endl;
		return 1;
	}

	librevenge::RVNGStringVector output;
	librevenge::RVNGSVGDrawingGenerator generator(output, "svg");
	if (!libvisio::VisioDocument::parse(&input, &generator)) {
		cerr << "ERROR: SVG Generation failed!" << endl;
		return 1;
	}

	if (output.empty()) {
		cerr << "ERROR: No SVG document generated!" << endl;
		return 1;
	}

	if (2 == argc)
		cout << output.size() <<
		    " drawing pages in VSD document " << endl;
	else {
		unsigned page = 0;
		unsigned lastpage = page;
		if (1 == allpages) {
			lastpage = output.size() - 1;
		} else {
			if ((4 == argc)) {
				page = atoi(argv[3]) - 1;
				if ((0 > page) | (page >= output.size())) {
					cerr <<
					    "ERROR: Please choose a drawing page number between 1 and "
					    << output.size() << "." <<
					    endl;
					return 1;
				}
				lastpage = page;
			}
		}
		for (; page <= lastpage; page++) {
			ofstream svgfile;
			if (0 == allpages) {
				svgfile.open(argv[2 + allpages]);
			} else {
				string base = argv[2 + allpages];

				if (0 !=
				    strncasecmp(".svg",
						base.substr(base.size() -
							    4, 4).c_str(),
						4)) {
					cerr <<
					    "ERROR: output filename does not end with '.svg'"
					    << endl;
					return 1;
				}
				string pagefilename =
				    base.substr(0, base.size() - 4);
				char buffer[MAX_PATH];
				snprintf(buffer, sizeof(buffer), "%d",
					 page + 1);
				pagefilename += string(buffer) + ".svg";
				svgfile.open(pagefilename.c_str());
			}
			svgfile <<
			    "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
			svgfile <<
			    "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"";
			svgfile <<
			    " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";

			svgfile << output[page].cstr() << endl;
			svgfile.close();
		}
	}

	return 0;
}
