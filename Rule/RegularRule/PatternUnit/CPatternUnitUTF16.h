/*
 * CPatternUnitUTF16.h
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#ifndef RULE_REGULARRULE_PATTERNUNIT_CPATTERNUNITUTF16_H_
#define RULE_REGULARRULE_PATTERNUNIT_CPATTERNUNITUTF16_H_

#include "CPatternUnit.h"

class C_PatternUnit_UTF16: public C_PatternUnit {
public:
	C_PatternUnit_UTF16(const C_PatternUnit_UTF16& unit);
	C_PatternUnit_UTF16();
	~C_PatternUnit_UTF16();

	const void* getPcre();
	const void* getPcreExtra();

	int PcreCompile();

private:
	pcre16*			m_pPcre;
	pcre16_extra*	m_pPcreExtra;
};

#endif /* RULE_REGULARRULE_PATTERNUNIT_CPATTERNUNITUTF16_H_ */
