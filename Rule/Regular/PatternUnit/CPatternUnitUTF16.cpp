/*
 * CPatternUnitUTF16.cpp
 *
 *  Created on: 2015Äê9ÔÂ28ÈÕ
 *      Author: SmallCroco
 */

#include "CPatternUnitUTF16.h"

C_PatternUnit_UTF16::C_PatternUnit_UTF16() {
	// TODO Auto-generated constructor stub

}

C_PatternUnit_UTF16::~C_PatternUnit_UTF16() {
	// TODO Auto-generated destructor stub
}

int C_PatternUnit_UTF16::PcreCompile() {

	const char* error;
	int erroffset;

	m_pPcre = pcre16_compile((PCRE_SPTR16)m_pContent, PCRE_NO_AUTO_CAPTURE |
			 PCRE_NO_UTF16_CHECK | PCRE_MULTILINE | PCRE_NO_START_OPTIME, &error,
			 &erroffset, NULL);

	if (NULL == m_pPcre) {
		cout("PCRE UTF16 compilation failed at offset "<<erroffset<<": "<<error<<endl;
		return -1;
	}

	m_pPcreExtra = pcre16_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
	if (NULL == m_pPcreExtra) {
		cout<<"PCRE UTF16 pcre_study failed: "<<error<<endl;
	}

	return 0;
}
