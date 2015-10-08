/*
 * CBaseRule.h
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#ifndef RULE_CBASERULE_H_
#define RULE_CBASERULE_H_

class C_BaseRule {
public:

	virtual ~C_BaseRule() = 0;

	virtual int InitRules(const char* filePath, int encode) = 0;

	virtual C_BaseRule* CreateObj(void) = 0;

protected:
	bool ChangeTextEncode(EM_FileEncode emSrcEncode, EM_FileEncode emDestEncode,
			char* pszSrcText, size_t* pSrcLen, char* pszDestText, size_t* pDestLen);
};

#endif /* RULE_CBASERULE_H_ */
