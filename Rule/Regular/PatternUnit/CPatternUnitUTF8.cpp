/*
 * CPatternUnitUTF8.cpp
 *
 *  Created on: 2015Äê9ÔÂ28ÈÕ
 *      Author: SmallCroco
 */

#include "CPatternUnitUTF8.h"

C_PatternUnit_UTF8::C_PatternUnit_UTF8() {
	// TODO Auto-generated constructor stub

}

C_PatternUnit_UTF8::~C_PatternUnit_UTF8() {
	// TODO Auto-generated destructor stub
}

int C_PatternUnit_UTF8::PcreCompile() {

	const char* error;
	int errorffset;

	m_pPcre = pcre_compile((PCRE_SPTR)m_pContent, PCRE_NO_AUTO_CAPTURE |
				PCRE_UTF8 | PCRE_NO_UTF8_CHECK | PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE,
				&error, &erroffset, NULL);

	if (NULL == m_pPcre) {
		cout<<"PCRE UTF8 compilation failed at offset "<<erroffset<<": "<<error<<endl;
		return -1;
	}

	m_pPcreExtra = pcre_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, #error);
	if (NULL == m_pPcreExtra) {
		cout<<"PCRE UTF8 pcre_study failed: "<<error<<endl;
	}

	return 0;
}
