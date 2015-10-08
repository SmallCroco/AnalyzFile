/*
 * CPatternUnitGB18030.h
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#ifndef RULE_REGULAR_PATTERNUNIT_CPATTERNUNITGB18030_H_
#define RULE_REGULAR_PATTERNUNIT_CPATTERNUNITGB18030_H_

#include "CPatternUnit.h"

class C_PatternUnit_GB18030: public C_PatternUnit {
public:
	C_PatternUnit_GB18030();
	~C_PatternUnit_GB18030();

	const void* getPcre();
	const void* getPcreExtra();

protected:
	int PcreCompile();

private:
	pcre*			m_pPcre;
	pcre_extra*	m_pPcreExtra;
};

#endif /* RULE_REGULAR_PATTERNUNIT_CPATTERNUNITGB18030_H_ */
