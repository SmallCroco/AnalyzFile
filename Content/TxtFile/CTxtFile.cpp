/*
 * CTxtFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CTxtFile.h"

C_TxtFile::C_TxtFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFileData, ulFileLen, emEncode){

}

C_TxtFile::~C_TxtFile() {

}


bool C_TxtFile::ExtractTxt() {

	m_strText.append(m_pszFileData, m_ulFileLen);

	m_ulTextLen = m_ulFileLen;

	return true;
}
