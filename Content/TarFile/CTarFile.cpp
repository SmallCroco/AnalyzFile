/*
 * CTarFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CTarFile.h"

C_TarFile::C_TarFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFileData, ulFileLen, emEncode){

}

C_TarFile::~C_TarFile() {
	// TODO Auto-generated destructor stub
}

