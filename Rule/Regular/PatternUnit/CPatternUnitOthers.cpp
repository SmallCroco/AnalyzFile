/*
 * CPatternUnitOthers.cpp
 *
 *  Created on: 2015Äê9ÔÂ28ÈÕ
 *      Author: SmallCroco
 */

#include "CPatternUnitOthers.h"

C_PatternUnit_Others::C_PatternUnit_Others() {
	// TODO Auto-generated constructor stub

}

C_PatternUnit_Others::~C_PatternUnit_Others() {
	// TODO Auto-generated destructor stub
}

int C_PatternUnit_Others::PcreCompile() {

	const char* error;
	int erroffset;

	m_pPcre = pcre_compile((PCRE_SPTR)m_pPcontent, PCRE_NO_AUTO_CAPTURE | PCRE_UTF8 |
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
