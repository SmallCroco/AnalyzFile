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
	C_TxtFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_TxtFile();

private:
	bool ExtractTxt();
};

#endif /* CONTENT_TXTFILE_CTXTFILE_H_ */
