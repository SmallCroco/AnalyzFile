/*
 * CPatternUnitUTF32.h
 *
 *  Created on: 2015��9��28��
 *      Author: SmallCroco
 */

#ifndef RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF32_H_
#define RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF32_H_

class C_PatternUnit_UTF32: public C_PatternUnit {
public:
	C_PatternUnit_UTF32();
	~C_PatternUnit_UTF32();

	const void* getPcre();
	const void* getPcreExtra();

protected:
	int PcreCompile();

private:
	pcre32*			m_pPcre;
	pcre32_extra*	m_pPcreExtra;
};

#endif /* RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF32_H_ */
