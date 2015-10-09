/*
 * CRtfFile.h
 *
 *  Created on: 2015年10月8日
 *      Author: smallcroco
 */

#ifndef CONTENT_RTFFILE_CRTFFILE_H_
#define CONTENT_RTFFILE_CRTFFILE_H_

class C_RtfFile: public C_BaseFile {
public:
	C_RtfFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	~C_RtfFile();
};

#endif /* CONTENT_RTFFILE_CRTFFILE_H_ */
