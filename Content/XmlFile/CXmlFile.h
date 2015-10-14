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
	// 构造函数
	C_XmlFile(const char* pszFilePath, const char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);

	// 析构函数
	~C_XmlFile();

private:
	// 提取文本
	bool ExtractTxt();
};

#endif /* CONTENT_XMLFILE_CXMLFILE_H_ */
