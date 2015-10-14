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
	C_TxtFile(const char* pszFilePath, const char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);

	//　析构函数
	~C_TxtFile();

private:
	// 提取文本
	bool ExtractTxt();
};

#endif /* CONTENT_TXTFILE_CTXTFILE_H_ */
