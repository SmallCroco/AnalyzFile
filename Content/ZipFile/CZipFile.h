/*
 * CZipFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_ZIPFILE_CZIPFILE_H_
#define CONTENT_ZIPFILE_CZIPFILE_H_

#include "CBaseFile.h"

class C_ZipFile: public C_BaseFile {

public:
	// 构造函数
	C_ZipFile(const char* pszFilePath, const char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);

	// 析构函数
	~C_ZipFile();

private:
	// 文本提取
	bool ExtractTxt();

	// 解压zip包
	bool UnZipFile(const char* pszPassword = NULL);

	// 判断是否是办公文件
	bool isOffFile();
};

#endif /* CONTENT_ZIPFILE_CZIPFILE_H_ */
