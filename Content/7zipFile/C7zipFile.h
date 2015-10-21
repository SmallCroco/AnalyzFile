/*
 * C7zipFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_7ZIPFILE_C7ZIPFILE_H_
#define CONTENT_7ZIPFILE_C7ZIPFILE_H_

#include "CBaseFile.h"

class C_7zipFile: public C_BaseFile {

public:
	// 构造函数
	C_7zipFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	// 析构函数
	~C_7zipFile();

	// 文件分析
	bool AnalyzeFile();

private:
	// 提取压缩文件
	bool ExtractTxt();
};

#endif /* CONTENT_7ZIPFILE_C7ZIPFILE_H_ */
