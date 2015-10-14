/*
 * CPatternUnitUTF8.cpp
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#include <RegularRule/PatternUnit/CPatternUnitUTF8.h>
#include "pcre.h"
#include <iostream>

using namespace std;

C_PatternUnit_UTF8::C_PatternUnit_UTF8() {
	// TODO Auto-generated constructor stub
	m_pPcre = NULL;
	m_pPcreExtra = NULL;
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