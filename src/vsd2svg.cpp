#include <iostream>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libvisio/libvisio.h>
#include <libwpd-stream/libwpd-stream.h>
#include <libwpd/libwpd.h>

using namespace std;

int main (int argc, char *argv[])
{
	xmlDocPtr doc;
	xmlXPathContextPtr xpathCtx;
	xmlXPathObjectPtr xpathObj;
	int drawingpageno = 0;

	if((2 > argc)||(3 < argc))
	{
		cerr << "USAGE: vsd2svg visiofile svgfile [drawingpagenumber]" << endl;
		return 1;
	}

	WPXFileStream input(argv[1]);

  	if (!libvisio::VisioDocument::isSupported(&input))
  	{
    		cerr << "ERROR: Unsupported file format (unsupported version) or file is encrypted!" << std::endl;
    		return 1;
  	}

	xmlInitParser();
	LIBXML_TEST_VERSION
	doc = xmlParseFile(argv[1]);
	if(NULL == doc)
	{
		cerr << "ERROR: Unable to parse file " << argv[1] << endl;
		return 1;
	}

	xpathCtx = xmlXPathNewContext(doc);
	if(NULL == xpathCtx)
	{
		cerr << "ERROR: Unable to create new XPath context." << endl;
		xmlFreeDoc(doc);
		return 1;
	}	
	
	xmlXPathRegisterNs(xpathCtx, (const xmlChar *)"svg", (const xmlChar *)"http://www.w3.org/2000/svg");
	xmlXPathRegisterNs(xpathCtx, (const xmlChar *)"xhtml", (const xmlChar *)"http://www.w3.org/1999/xhtml");
	xmlXPathRegisterNs(xpathCtx, (const xmlChar *)"xlink", (const xmlChar *)"http://www.w3.org/1999/xlink");

	xpathObj = xmlXPathEvalExpression((const xmlChar *)argv[2], xpathCtx);
	if(NULL == xpathObj)
	{	
		cerr << "ERROR: Unable to evaluate xpath expression." << endl;
		return 1;
	}
	cout << "Number of SVG nodes: " << ((xpathObj->nodesetval) ? xpathObj->nodesetval->nodeNr : 0) << endl;

	return 0;
}

