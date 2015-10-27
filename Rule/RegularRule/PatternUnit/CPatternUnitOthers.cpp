/*
 * CPatternUnitOthers.cpp
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#include <RegularRule/PatternUnit/CPatternUnitOthers.h>
#include "pcre.h"
#include <string.h>
#include <iostream>

using namespace std;

C_PatternUnit_Others::C_PatternUnit_Others() {

	m_pPcre = NULL;
	m_pPcreExtra = NULL;
}

C_PatternUnit_Others::C_PatternUnit_Others(const C_PatternUnit_Others& unit) {
	this->m_nContentLen = unit.m_nContentLen;
	this->m_nPid = unit.m_nPid;
	this->m_pContent = new char[m_nContentLen+1];
	memset(m_pContent, 0, (m_nContentLen+1)*sizeof(char));
	memcpy(m_pContent, unit.m_pContent, m_nContentLen*sizeof(char));

	int n = strlen(unit.m_pName);
	this->m_pName = new char[n + 1];
	memset(m_pName, 0, sizeof(char)*(n + 1));
	memcpy(m_pName, unit.m_pName, n * sizeof(char));

	const char* error;
	int erroffset;

	if (unit.m_pPcre != NULL) {
		this->m_pPcre = pcre_compile((PCRE_SPTR)m_pContent, PCRE_NO_AUTO_CAPTURE | PCRE_UTF8 |
				PCRE_NO_UTF8_CHECK | PCRE_UCP | PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE, &error,
				&erroffset, NULL);
		if (NULL == m_pPcre) {
				std::cout<<"PCRE Others compilation failed at offset"<<erroffset<<":"<<error<<std::endl;
			}
	} else {
		this->m_pPcre = NULL;
	}

	if (unit.m_pPcreExtra != NULL) {
		this->m_pPcreExtra = pcre_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
		if (NULL == m_pPcreExtra) {
			cout<<"PCRE Others pcre_study failed:"<<error<<std::endl;
		}
	} else {
		this->m_pPcreExtra = NULL;
	}
}

C_PatternUnit_Others::~C_PatternUnit_Others() {

	if (NULL != m_pPcre) {
		pcre_free(m_pPcre);
		m_pPcre = NULL;
	}

	if (NULL != m_pPcreExtra) {
		pcre_free_study(m_pPcreExtra);
		m_pPcreExtra = NULL;
	}
}

int C_PatternUnit_Others::PcreCompile() {

	const char* error;
	int erroffset;

	m_pPcre = pcre_compile((PCRE_SPTR)m_pContent, PCRE_NO_AUTO_CAPTURE | PCRE_UTF8 |
			PCRE_NO_UTF8_CHECK | PCRE_UCP | PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE, &error,
			&erroffset, NULL);

	if (NULL == m_pPcre) {
		cout<<"PCRE Others compilation failed at offset "<<erroffset<<": "<<error<<endl;
		return -1;
	}

	m_pPcreExtra = pcre_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
	if (NULL == m_pPcreExtra) {
		cout<<"PCRE Others pcre_study failed: "<<error<<endl;
	}

	return 0;
}

/*
 * @Function Name	: getPcre
 * @Description		: 获取pcre正则表达式指针
 */
const void* C_PatternUnit_Others::getPcre() {

		return (const void*)m_pPcre;
}

/*
 * @Function Name	: getPcreExtra
 * @Description		: 获取pcreExtra指针
 */
const void* C_PatternUnit_Others::getPcreExtra() {

		return (const void*)m_pPcreExtra;
}
