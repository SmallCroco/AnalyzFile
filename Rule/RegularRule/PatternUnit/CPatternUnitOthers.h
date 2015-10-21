/*
 * CPatternUnitOthers.h
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#ifndef RULE_REGULARRULE_PATTERNUNIT_CPATTERNUNITOTHERS_H_
#define RULE_REGULARRULE_PATTERNUNIT_CPATTERNUNITOTHERS_H_

#include "CPatternUnit.h"

class C_PatternUnit_Others: public C_PatternUnit {
public:
	C_PatternUnit_Others(const C_PatternUnit_Others& unit);
	C_PatternUnit_Others();
	~C_PatternUnit_Others();

	const void* getPcre();
	const void* getPcreExtra();

	int PcreCompile();

private:
	pcre*			m_pPcre;
	pcre_extra*	m_pPcreExtra;
};

#endif /* RULE_REGULARRULE_PATTERNUNIT_CPATTERNUNITOTHERS_H_ */
