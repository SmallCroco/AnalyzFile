/*
 * CRtfFile.h
 *
 *  Created on: 2015年10月8日
 *      Author: smallcroco
 */

#ifndef CONTENT_RTFFILE_CRTFFILE_H_
#define CONTENT_RTFFILE_CRTFFILE_H_

#include "CBaseFile.h"

class C_RtfFile: public C_BaseFile {

public:
	// 构造函数
	C_RtfFile(const char* pszFilePath, const char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);

	// 析构函数
	~C_RtfFile();

private:
	// 文本提取
	bool ExtractTxt();
};

#endif /* CONTENT_RTFFILE_CRTFFILE_H_ */
