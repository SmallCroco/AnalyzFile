/*
 * CRegularRule.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef RULE_REGULAR_CREGULARRULE_H_
#define RULE_REGULAR_CREGULARRULE_H_

#include <vector>
#include "CPatternUnitUTF8.h"
#include "CPatternUnitUTF16.h"
#include "CPatternUnitUTF32.h"
#include "CPatternUnitGB18030.h"
#include "CPatternUnitOthers.h"

using std::vector;

class C_RegularRule: public C_BaseRule {
public:
	C_RegularRule();
	~C_RegularRule();

	int InitRules(const char* filePath, int encode);

private:
	vector<C_PatternUnit_UTF8*> m_utf8Patterns;
	vector<C_PatternUnit_UTF16*> m_utf16Patterns;
	vector<C_PatternUnit_UTF16*> m_utf16lePatterns;
	vector<C_PatternUnit_UTF16*> m_utf16bePatterns;
	vector<C_PatternUnit_UTF32*> m_utf32Patterns;
	vector<C_PatternUnit_UTF32*> m_utf32lePatterns;
	vector<C_PatternUnit_UTF32*> m_utf32bePatterns;
	vector<C_PatternUnit_GB18030*> m_gb18030Patterns;
};

#endif /* RULE_REGULAR_CREGULARRULE_H_ */
