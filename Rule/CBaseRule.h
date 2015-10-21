/*
 * CBaseRule.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef RULE_CBASERULE_H_
#define RULE_CBASERULE_H_

#include <iostream>
#include "FileStruct.h"
#include "CRegularResult.h"

class C_BaseRule {
public:

	virtual ~C_BaseRule();

	virtual int InitRules(const char* filePath, int encode) = 0;

	virtual C_BaseRule* CreateObj() = 0;

	virtual void asciiMatch(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void iso8599Match(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void utf7Match(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void utf8Match(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void utf16Match(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void utf32Match(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void gbkMatch(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void gb2312Match(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void gb18030Match(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;
	virtual void big5Match(const char* pszFileText, int bufLen, C_RegularResult* result) = 0;

protected:
	bool ChangeTextEncode(EM_FileEncode emSrcEncode, EM_FileEncode emDestEncode,
			char* pszSrcText, size_t* pSrcLen, char* pszDestText, size_t* pDestLen);

};

#endif /* RULE_CBASERULE_H_ */
