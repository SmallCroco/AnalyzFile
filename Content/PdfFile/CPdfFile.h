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
	C_PdfFile(const char* pszFilePath, const char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);

	// 析构函数
	~C_PdfFile();

private:
	// 文本提取
	bool ExtractTxt();
};

#endif /* CONTENT_PDFFILE_CPDFFILE_H_ */
