/*
 * CPatternUnitUTF8.cpp
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#include "CPatternUnitUTF8.h"
#include "pcre.h"
#include <string.h>
#include <iostream>

using namespace std;

C_PatternUnit_UTF8::C_PatternUnit_UTF8() {
	// TODO Auto-generated constructor stub
	m_pPcre = NULL;
	m_pPcreExtra = NULL;
}

C_PatternUnit_UTF8::C_PatternUnit_UTF8(const C_PatternUnit_UTF8 &unit) {
	this->m_nContentLen = unit.m_nContentLen;
	this->m_nPid = unit.m_nPid;
	this->m_pContent = new char[m_nContentLen+1];
	memset(m_pContent, 0, sizeof(char)*(m_nContentLen+1));
	memcpy(m_pContent, unit.m_pContent, m_nContentLen*sizeof(char));

	int n = strlen(unit.m_pName);
	this->m_pName = new char[n+1];
	memset(m_pName, 0, sizeof(char)*(n+1));
	memcpy(m_pName, unit.m_pName, n*sizeof(char));

	const char* error;
	int erroffset;

	if (unit.m_pPcre != NULL) {
		this->m_pPcre = pcre_compile((PCRE_SPTR)m_pContent,
				PCRE_NO_AUTO_CAPTURE | PCRE_UTF8 | PCRE_NO_UTF8_CHECK
						| PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE, &error,
				&erroffset,
				NULL);
		if (NULL == m_pPcre) {
			std::cout<<"PCRE UTF8 compilation failed at offset"<<erroffset<<":"<<error<<std::endl;
		}
	} else {
		this->m_pPcre = NULL;
	}

	if (unit.m_pPcreExtra != NULL) {
		this->m_pPcreExtra = pcre_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
		if (NULL == m_pPcreExtra) {
				cout<<"PCRE UTF8 pcre_study failed:"<<error<<std::endl;
			}
	} else {
		this->m_pPcreExtra = NULL;
	}
}

C_PatternUnit_UTF8::~C_PatternUnit_UTF8() {
	// TODO Auto-generated destructor stub
	if (NULL != m_pPcre) {
		pcre_free(m_pPcre);
		m_pPcre = NULL;
	}

	if (NULL != m_pPcreExtra) {
		pcre_free_study(m_pPcreExtra);
		m_pPcreExtra = NULL;
	}
}

int C_PatternUnit_UTF8::PcreCompile() {

	const char* error;
	int erroffset;

	m_pPcre = pcre_compile((PCRE_SPTR)m_pContent,
				PCRE_NO_AUTO_CAPTURE | PCRE_UTF8 | PCRE_NO_UTF8_CHECK
						| PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE, &error,
				&erroffset,
				NULL);

	if (NULL == m_pPcre) {
		cout<<"PCRE UTF8 compilation failed at offset "<<erroffset<<": "<<error<<endl;
		return -1;
	}

	m_pPcreExtra = pcre_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
	if (NULL == m_pPcreExtra) {
		cout<<"PCRE UTF8 pcre_study failed: "<<error<<endl;
	}

	return 0;
}

/*
 * @Function Name	: getPcre
 * @Description		: 获取pcre正则表达式指针
 */
const void* C_PatternUnit_UTF8::getPcre() {

		return (const void*)m_pPcre;
}

/*
 * @Function Name	: getPcreExtra
 * @Description		: 获取pcreExtra指针
 */
const void* C_PatternUnit_UTF8::getPcreExtra() {

		return (const void*)m_pPcreExtra;
}
