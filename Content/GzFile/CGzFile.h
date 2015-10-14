/*
 * CGzFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_GZFILE_CGZFILE_H_
#define CONTENT_GZFILE_CGZFILE_H_

#include "CBaseFile.h"

class C_GzFile: public C_BaseFile {

public:
	// 构造函数
	C_GzFile(const char* pszFilePath, const char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);

	// 析构函数
	~C_GzFile();

private:
	// 文本提取
	bool ExtractTxt();
};

#endif /* CONTENT_GZFILE_CGZFILE_H_ */
