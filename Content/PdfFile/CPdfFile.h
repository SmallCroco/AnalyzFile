/*
 * CPdfFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_PDFFILE_CPDFFILE_H_
#define CONTENT_PDFFILE_CPDFFILE_H_

#include "CBaseFile.h"

class C_PdfFile: public C_BaseFile {

public:
	// 构造函数
	C_PdfFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	// 析构函数
	~C_PdfFile();

	// 文件分析
	bool AnalyzeFile();

private:
	// 文本提取
	bool ExtractTxt();

	// 获取文本编码方式
	bool GetFileEncode();
};

#endif /* CONTENT_PDFFILE_CPDFFILE_H_ */
