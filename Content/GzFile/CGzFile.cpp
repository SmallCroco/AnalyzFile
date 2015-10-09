/*
 * CGzFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CGzFile.h"

C_GzFile::C_GzFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFileData, ulFileLen, emEncode){

}

C_GzFile::~C_GzFile() {
	// TODO Auto-generated destructor stub
}

