/*
 * CFileAnalyze.cpp
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#include "CFileAnalyze.h"
#include "FileStruct.h"
#include <iostream>
#include <stdio.h>

C_FileAnalyze::C_FileAnalyze(const char* pszFilePath) {

	m_pszFileData = NULL;
	m_ulFileLen = 0;
	m_emFileType = en_unknow;
	m_pFile = NULL;
	m_pRule = NULL;
	m_pResult = NULL;

	if (NULL != pszFilePath) {

		FILE* fp = fopen(pszFilePath, "rb");
		if (NULL == fp) {
			break;
		}

		fseek(fp, 0L, SEEK_END);
		long len = ftell(fp);
		if (-1L == len) {
			fclose(fp);
			break;
		} else {
			m_ulFileLen = len;
			rewind(fp);
		}

		m_pszFileData = (unsigned char*)malloc(sizeof(unsigned char) * m_ulFileLen);
		if (NULL == m_pszFileData) {

			m_ulFileLen = 0;

			fclose(fp);
			break;
		}
		if (m_ulFileLen != (unsigned long)fread(m_pszFileData, sizeof(unsigned char), m_ulFileLen, fp)) {

			m_ulFileLen = 0;
			free(m_pszFileData);

			fclose(fp);
			break;
		}

		fclose(fp);
	}
}

C_FileAnalyze::C_FileAnalyze(const char* pszFileContent, unsigned long int ulFileLen) {

	m_pszFileData = NULL;
	m_ulFileLen = 0;
	m_emFileType = en_unknow;
	m_pFile = NULL;
	m_pRule = NULL;
	m_pResult = NULL;

	m_ulFileLen = ulFileLen;
	m_pszFileData = new unsigned char[m_ulFileLen];
	if (NULL == m_pszFileData) {
		m_ulFileLen = 0;
	}

	memcpy(m_pszFileData, pszFileContent, m_ulFileLen);
}

C_FileAnalyze::~C_FileAnalyze() {

}

bool C_FileAnalyze::SetRule(const C_BaseRule* pRule) {

	m_pRule = pRule->CreateObject();
	if (NULL == m_pRule) {
		return false;
	} else {
		return true;
	}
}

const C_BaseRule* C_FileAnalyze::GetRule() {

	return (const C_BaseRule*)m_pRule;
}

void C_FileAnalyze::Analyze() {

	m_emFileType = this->GetFileType();

	switch (m_emFileType) {
	case en_txt: m_pFile = new C_TxtFile(); break;
	case en_off: m_pFile = new C_OffFile(); break;
	case en_rar: m_pFile = new C_RarFile(); break;
	case en_zip: m_pFile = new C_ZipFile(); break;
	case en_gz: m_pFile  = new C_GzFile(); break;
	case en_pdf: m_pFile = new C_PdfFile(); break;
	case en_tar: m_pFile = new C_TarFile(); break;
	case en_7zip: m_pFile = new C_7zipFile(); break;
	default: m_pFile = NULL;
	}

	m_pFile->Match(m_pRule, m_pResult);
}

