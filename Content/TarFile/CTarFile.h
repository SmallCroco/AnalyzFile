/*
 * CTarFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_TARFILE_CTARFILE_H_
#define CONTENT_TARFILE_CTARFILE_H_

class C_TarFile: public C_BaseFile {
public:
	C_TarFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_TarFile();
};

#endif /* CONTENT_TARFILE_CTARFILE_H_ */
