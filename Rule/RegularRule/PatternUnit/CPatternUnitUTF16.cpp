/*
 * CPatternUnitUTF16.cpp
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#include <RegularRule/PatternUnit/CPatternUnitUTF16.h>
#include "pcre.h"
#include <iostream>

using namespace std;

C_PatternUnit_UTF16::C_PatternUnit_UTF16() {

	m_pPcre = NULL;
	m_pPcreExtra = NULL;
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
