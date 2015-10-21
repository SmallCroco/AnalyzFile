/*
 * CGzFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_GZFILE_CGZFILE_H_
#define CONTENT_GZFILE_CGZFILE_H_

#include "CBaseFile.h"
#include "zlib.h"

class C_GzFile: public C_BaseFile {

public:
	// 构造函数
	C_GzFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	// 析构函数
	~C_GzFile();

	// 文件分析
	bool AnalyzeFile();

private:
	// 提取压缩文件
	bool ExtractTxt();

	// 解压gzip文件
	bool ungzip(Bytef* pInputbuf, unsigned long inputlen, Bytef** pOutputbuf, unsigned long* pOutputlen);
};

#endif /* CONTENT_GZFILE_CGZFILE_H_ */
