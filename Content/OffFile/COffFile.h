/*
 * COffFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_OFFFILE_COFFFILE_H_
#define CONTENT_OFFFILE_COFFFILE_H_

#include "CBaseFile.h"

class C_OffFile: public C_BaseFile {

public:
	// 构造函数
	C_OffFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	// 析构函数
	~C_OffFile();

	// 文件分析
	bool AnalyzeFile();

private:
	// 文本提取
	bool ExtractTxt();

	// 获取文本编码方式
	bool GetFileEncode();
};

#endif /* CONTENT_OFFFILE_COFFFILE_H_ */
