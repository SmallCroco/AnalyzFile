/*
 * CPatternUnitUTF32.cpp
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#include "CPatternUnitUTF32.h"

C_PatternUnit_UTF32::C_PatternUnit_UTF32() {
	// TODO Auto-generated constructor stub

}

C_PatternUnit_UTF32::~C_PatternUnit_UTF32() {
	// TODO Auto-generated destructor stub
}

int C_PatternUnit_UTF32::PcreCompile() {

	const char* error;
	int erroffset;

	m_pPcre = pcre32_compile((PCRE_SPTR32)m_pContent, PCRE_NO_AUTO_CAPTURE | PCRE_UTF32 |
				PCRE_NO_UTF32_CHECK | PCRE_UCP | PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE,
				&error, &erroffset, NULL);

	if (NULL == m_pPcre) {
		cout<<"PCRE UTF32 compilation failed at offset "<<erroffset<<": "<<error<<endl;
		return -1;
	}

	m_pPcreExtra = pcre32_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
	if (NULL == m_pPcreExtra) {
		cout<<"PCRE UTF32 pcre_study failed: "<<error<<endl;
	}

	return 0;

}