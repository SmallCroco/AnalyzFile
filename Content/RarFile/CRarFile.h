/*
 * CRarFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_RARFILE_CRARFILE_H_
#define CONTENT_RARFILE_CRARFILE_H_

class C_RarFile: public C_BaseFile {
public:
	C_RarFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_RarFile();
};

#endif /* CONTENT_RARFILE_CRARFILE_H_ */
