/*
 * CRarFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CRarFile.h"

C_RarFile::C_RarFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow):
	C_BaseFile(pszFileData, ulFileLen, emEncode){

}

C_RarFile::~C_RarFile() {

}

