/*
 * CTxtFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_TXTFILE_CTXTFILE_H_
#define CONTENT_TXTFILE_CTXTFILE_H_

#include "CBaseFile.h"

class C_TxtFile: public C_BaseFile {

public:
	// 构造函数
	C_TxtFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	//　析构函数
	~C_TxtFile();

	// 文件分析
	bool AnalyzeFile();

private:
	// 提取文本内容
	bool ExtractTxt();

	// 获取文本编码方式
	bool GetFileEncode();
};

#endif /* CONTENT_TXTFILE_CTXTFILE_H_ */
