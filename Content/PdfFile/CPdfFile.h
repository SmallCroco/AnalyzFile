/*
 * CPdfFile.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef CONTENT_PDFFILE_CPDFFILE_H_
#define CONTENT_PDFFILE_CPDFFILE_H_

class C_PdfFile: public C_BaseFile {
public:
	C_PdfFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_PdfFile();
};

#endif /* CONTENT_PDFFILE_CPDFFILE_H_ */
