/*
 * CHtmlFile.h
 *
 *  Created on: 2015年10月8日
 *      Author: smallcroco
 */

#ifndef CONTENT_HTMLFILE_CHTMLFILE_H_
#define CONTENT_HTMLFILE_CHTMLFILE_H_

#include "CBaseFile.h"

class C_HtmlFile: public C_BaseFile {

public:
	// 构造函数
	C_HtmlFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	// 析构函数
	~C_HtmlFile();

	// 文件分析
	bool AnalyzeFile();

private:
	//　文本提取
	bool ExtractTxt();

	// 获取文本编码方式
	bool GetFileEncode();
};

#endif /* CONTENT_HTMLFILE_CHTMLFILE_H_ */
