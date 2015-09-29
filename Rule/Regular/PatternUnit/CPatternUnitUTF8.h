/*
 * CPatternUnitUTF8.h
 *
 *  Created on: 2015Äê9ÔÂ28ÈÕ
 *      Author: SmallCroco
 */

#ifndef RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF8_H_
#define RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF8_H_

class C_PatternUnit_UTF8: public C_PatternUnit {
public:
	C_PatternUnit_UTF8();
	~C_PatternUnit_UTF8();

protected:
	int PcreCompile();
};

#endif /* RULE_REGULAR_PATTERNUNIT_CPATTERNUNITUTF8_H_ */
