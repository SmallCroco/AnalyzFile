/*
 * CTarFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_TARFILE_CTARFILE_H_
#define CONTENT_TARFILE_CTARFILE_H_

#include "CBaseFile.h"

class C_TarFile: public C_BaseFile {

public:
	// 构造函数
	C_TarFile(const char* pszFilePath, const char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);

	// 析构函数
	~C_TarFile();

private:
	// 文本提取
	bool ExtractTxt();
};

#endif /* CONTENT_TARFILE_CTARFILE_H_ */
