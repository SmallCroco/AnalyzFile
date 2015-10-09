/*
 * CXmlFile.cpp
 *
 *  Created on: 2015年10月8日
 *      Author: smallcroco
 */

#include "CXmlFile.h"
#include "uchardet.h"
#include "metadata.h"
#include "plain_text_extractor.h"

C_XmlFile::C_XmlFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFileData, ulFileLen, emEncode){

}

C_XmlFile::~C_XmlFile() {

}

bool C_XmlFile::ExtractTxt() {

	PlainTextExtractor extractor;
	extractor.setVerboseLogging(true);

	if (!extractor.processFile(m_pFileData, m_lFileLength, m_strText)) {
		return false;
	}

	return true;
}

