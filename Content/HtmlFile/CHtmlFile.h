/*
 * CHtmlFile.h
 *
 *  Created on: 2015年10月8日
 *      Author: smallcroco
 */

#ifndef CONTENT_HTMLFILE_CHTMLFILE_H_
#define CONTENT_HTMLFILE_CHTMLFILE_H_

class C_HtmlFile: public C_BaseFile {
public:
	C_HtmlFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_HtmlFile();
};

#endif /* CONTENT_HTMLFILE_CHTMLFILE_H_ */
