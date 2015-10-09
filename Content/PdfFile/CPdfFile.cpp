/*
 * CPdfFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CPdfFile.h"

C_PdfFile::C_PdfFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFileData, ulFileLen, emEncode){

}

C_PdfFile::~C_PdfFile() {

}

