/*
 * CGzFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_GZFILE_CGZFILE_H_
#define CONTENT_GZFILE_CGZFILE_H_

class C_GzFile: public C_BaseFile {
public:
	C_GzFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_GzFile();
};

#endif /* CONTENT_GZFILE_CGZFILE_H_ */
