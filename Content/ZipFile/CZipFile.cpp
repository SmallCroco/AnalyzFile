/*
 * CZipFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CZipFile.h"
#include "unzip.h"
#include <sys/stat.h>

C_ZipFile::C_ZipFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFileData, ulFileLen, emEncode){

}

C_ZipFile::~C_ZipFile() {

}

bool C_ZipFile::ExtractTxt() {


}

