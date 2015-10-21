/*
 * CPatternUnitUTF16.cpp
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#include <RegularRule/PatternUnit/CPatternUnitUTF16.h>
#include "pcre.h"
#include <string.h>
#include <iostream>

using namespace std;

C_PatternUnit_UTF16::C_PatternUnit_UTF16() {

	m_pPcre = NULL;
	m_pPcreExtra = NULL;
}

C_PatternUnit_UTF16::C_PatternUnit_UTF16(const C_PatternUnit_UTF16& unit) {
	this->m_nContentLen = unit.m_nContentLen;
	this->m_nPid = unit.m_nPid;
	this->m_pContent = new char[m_nContentLen];
	memset(m_pContent, 0, m_nContentLen);
	memcpy(m_pContent, unit.m_pContent, m_nContentLen);

	this->m_pName = new char[strlen(unit.m_pName)];
	memset(m_pName, 0, strlen(unit.m_pName));
	memcpy(m_pName, unit.m_pName, strlen(unit.m_pName));

	const char* error;
	int erroffset;

	if (unit.m_pPcre != NULL) {
		this->m_pPcre = pcre16_compile((PCRE_SPTR16)m_pContent,
				PCRE_NO_AUTO_CAPTURE | PCRE_NO_UTF16_CHECK
						| PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE, &error,
				&erroffset,
				NULL);
	} else {
		this->m_pPcre = NULL;
	}

	if (unit.m_pPcreExtra != NULL) {
		this->m_pPcreExtra = pcre16_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
	} else {
		this->m_pPcreExtra = NULL;
	}
}

C_PatternUnit_UTF16::~C_PatternUnit_UTF16() {

	if (NULL != m_pPcre) {
		pcre16_free(m_pPcre);
		m_pPcre = NULL;
	}

	if (NULL != m_pPcreExtra) {
		pcre16_free_study(m_pPcreExtra);
		m_pPcreExtra = NULL;
	}
}

int C_PatternUnit_UTF16::PcreCompile() {

	const char* error;
	int erroffset;

	m_pPcre = pcre16_compile((PCRE_SPTR16)m_pContent,
			PCRE_NO_AUTO_CAPTURE | PCRE_NO_UTF16_CHECK
					| PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE, &error,
			&erroffset,
			NULL);

	if (NULL == m_pPcre) {
		cout<<"PCRE UTF16 compilation failed at offset "<<erroffset<<": "<<error<<endl;
		return -1;
	}

	m_pPcreExtra = pcre16_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
	if (NULL == m_pPcreExtra) {
		cout<<"PCRE UTF16 pcre_study failed: "<<error<<endl;
	}

	return 0;
}

/*
 * @Function Name	: getPcre
 * @Description		: 获取pcre正则表达式指针
 */
const void* C_PatternUnit_UTF16::getPcre() {

		return (const void*)m_pPcre;
}

/*
 * @Function Name	: getPcreExtra
 * @Description		: 获取pcreExtra指针
 */
const void* C_PatternUnit_UTF16::getPcreExtra() {

		return (const void*)m_pPcreExtra;
}
