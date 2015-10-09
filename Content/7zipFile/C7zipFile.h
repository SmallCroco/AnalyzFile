/*
 * C7zipFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_7ZIPFILE_C7ZIPFILE_H_
#define CONTENT_7ZIPFILE_C7ZIPFILE_H_

class C_7zipFile: public C_BaseFile {
public:
	C_7zipFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_7zipFile();
};

#endif /* CONTENT_7ZIPFILE_C7ZIPFILE_H_ */
