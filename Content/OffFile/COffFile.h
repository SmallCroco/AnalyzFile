/*
 * COffFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_OFFFILE_COFFFILE_H_
#define CONTENT_OFFFILE_COFFFILE_H_

class C_OffFile: public C_BaseFile {
public:
	C_OffFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_OffFile();
};

#endif /* CONTENT_OFFFILE_COFFFILE_H_ */
