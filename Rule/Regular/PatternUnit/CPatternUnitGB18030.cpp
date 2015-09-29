/*
 * CPatternUnitGB18030.cpp
 *
 *  Created on: 2015Äê9ÔÂ28ÈÕ
 *      Author: SmallCroco
 */

#include "CPatternUnitGB18030.h"

C_PatternUnit_GB18030::C_PatternUnit_GB18030() {
	// TODO Auto-generated constructor stub

}

C_PatternUnit_GB18030::~C_PatternUnit_GB18030() {
	// TODO Auto-generated destructor stub
}

int C_PatternUnit_GB18030::PcreCompile() {

	const char* error;
	int erroffset;

	m_pPcre = pcre_compile((PCRE_SPTR)m_pContent, PCRE_NO_AUTO_CAPTURE |
			PCRE_MULTILINE | PCRE_NO_START_OPTIMIZE,
			&error, &erroffset, NULL);

	if (NULL == m_pPcre) {
		cout<<"PCRE gb18030 compilation failed at offset "<<erroffset<<": "<<error<<endl;
		return -1;
	}

	m_pPcreExtra = pcre_study(m_pPcre, PCRE_STUDY_JIT_COMPILE, &error);
	if (NULL == m_pPcreExtra) {
		cout<<"PCRE gb18030 pcre_study failed: "<<error<<endl;
	}

	return 0;
}
