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
	C_RegularRule(C_RegularRule &rule);
	C_RegularRule();
	~C_RegularRule();

	int InitRules(const char* filePath, int encode);

	C_BaseRule* CreateObj();

	void asciiMatch(const char* pszFileText, int bufLen, C_RegularResult* result);
	void iso8599Match(const char* pszFileText, int bufLen,  C_RegularResult* result);
	void utf7Match(const char* pszFileText, int bufLen, C_RegularResult* result);
	void utf8Match(const char* pszFileText, int bufLen, C_RegularResult* result);
	void utf16Match(const char* pszFileText, int bufLen, C_RegularResult* result);
	void utf16leMatch(const char* pszFileText, int bufLen, C_RegularResult* result);
	void utf16beMatch(const char* pszFileText, int bufLen, C_RegularResult* result);
	void utf32Match(const char* pszFileText, int bufLen, C_RegularResult* result);
	void utf32leMatch(const char* pszFileText, int bufLen, C_RegularResult* result);
	void utf32beMatch(const char* pszFileText, int bufLen, C_RegularResult* result);
	void gbkMatch(const char* pszFileText, int bufLen, C_RegularResult* result);
	void gb2312Match(const char* pszFileText, int bufLen, C_RegularResult* result);
	void gb18030Match(const char* pszFileText, int bufLen, C_RegularResult* result);
	void big5Match(const char* pszFileText, int bufLen, C_RegularResult* result);

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
