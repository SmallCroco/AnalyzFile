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
	C_XmlFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	// 析构函数
	~C_XmlFile();

	// 文件分析
	bool AnalyzeFile();

private:
	// 提取文本
	bool ExtractTxt();

	// 获取文本编码方式
	bool GetFileEncode();
};

#endif /* CONTENT_XMLFILE_CXMLFILE_H_ */
