/*
 * CXmlFile.h
 *
 *  Created on: 2015年10月8日
 *      Author: smallcroco
 */

#ifndef CONTENT_XMLFILE_CXMLFILE_H_
#define CONTENT_XMLFILE_CXMLFILE_H_

#include "CBaseFile.h"

class C_XmlFile: public C_BaseFile {
public:
	C_XmlFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_XmlFile();

private:
	bool ExtractTxt();
};

#endif /* CONTENT_XMLFILE_CXMLFILE_H_ */
