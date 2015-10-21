/*
 * CRarFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_RARFILE_CRARFILE_H_
#define CONTENT_RARFILE_CRARFILE_H_

#include "CBaseFile.h"

class C_RarFile: public C_BaseFile {

public:
	// 构造函数
	C_RarFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	// 析构函数
	~C_RarFile();

	// 文件分析
	bool AnalyzeFile();

private:
	// 提取压缩文件
	bool ExtractTxt();

	// 回调函数
	static int function(unsigned int msg, long int UserData, long int P1, long int P2);
};

#endif /* CONTENT_RARFILE_CRARFILE_H_ */
