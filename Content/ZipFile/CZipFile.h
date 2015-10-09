/*
 * CZipFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_ZIPFILE_CZIPFILE_H_
#define CONTENT_ZIPFILE_CZIPFILE_H_

class C_ZipFile: public C_BaseFile {
public:
	C_ZipFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_ZipFile();

private:
	bool ExtractTxt();
};

#endif /* CONTENT_ZIPFILE_CZIPFILE_H_ */
