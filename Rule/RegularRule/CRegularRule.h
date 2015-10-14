/*
 * CRegularRule.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef RULE_REGULARRULE_CREGULARRULE_H_
#define RULE_REGULARRULE_CREGULARRULE_H_

#include "CBaseRule.h"
#include "CPatternUnitGB18030.h"
#include "CPatternUnitOthers.h"
#include "CPatternUnitUTF16.h"
#include "CPatternUnitUTF32.h"
#include "CPatternUnitUTF8.h"
#include <vector>

using std::vector;

class C_RegularRule: public C_BaseRule {
public:
	C_RegularRule();
	~C_RegularRule();

	int InitRules(const char* filePath, int encode);

	C_BaseRule* CreateObj();

	bool isUtf8();
	bool isUtf16();
	bool isUtf16le();
	bool isUtf16be();
	bool isUtf32();
	bool isUtf32le();
	bool isUtf32be();
	bool isGb18030();

private:
	vector<C_PatternUnit_UTF8*> 		m_utf8Patterns;
	vector<C_PatternUnit_UTF16*> 	m_utf16Patterns;
	vector<C_PatternUnit_UTF16*> 	m_utf16lePatterns;
	vector<C_PatternUnit_UTF16*> 	m_utf16bePatterns;
	vector<C_PatternUnit_UTF32*> 	m_utf32Patterns;
	vector<C_PatternUnit_UTF32*> 	m_utf32lePatterns;
	vector<C_PatternUnit_UTF32*> 	m_utf32bePatterns;
	vector<C_PatternUnit_GB18030*> 	m_gb18030Patterns;
};

#endif /* RULE_REGULARRULE_CREGULARRULE_H_ */
