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

protected:
	int PcreCompile();
};

#endif /* RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF32_H_ */
