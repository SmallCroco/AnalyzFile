/*
 * CPatternUnitUTF8.h
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#ifndef RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF8_H_
#define RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF8_H_

class C_PatternUnit_UTF8: public C_PatternUnit {
public:
	C_PatternUnit_UTF8();
	~C_PatternUnit_UTF8();

	const void* getPcre();
	const void* getPcreExtra();

protected:
	int PcreCompile();

private:
	pcre*			m_pPcre;
	pcre_extra*	m_pPcreExtra;
};

#endif /* RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF8_H_ */
