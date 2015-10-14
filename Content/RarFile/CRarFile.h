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
	C_RarFile(const char* pszFilePath, const char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);

	// 析构函数
	~C_RarFile();

private:
	// 文本提取
	bool ExtractTxt();
};

#endif /* CONTENT_RARFILE_CRARFILE_H_ */
