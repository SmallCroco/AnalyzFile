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

	virtual ~C_BaseRule();

	virtual int InitRules(const char* filePath, int encode) = 0;

	virtual C_BaseRule* CreateObj() = 0;

	virtual bool isUtf8() = 0;
	virtual bool isUtf16() = 0;
	virtual bool isUtf16le() = 0;
	virtual bool isUtf16be() = 0;
	virtual bool isUtf32() = 0;
	virtual bool isUtf32le() = 0;
	virtual bool isUtf32be() = 0;
	virtual bool isGb18030() = 0;

protected:
	bool ChangeTextEncode(EM_FileEncode emSrcEncode, EM_FileEncode emDestEncode,
			char* pszSrcText, size_t* pSrcLen, char* pszDestText, size_t* pDestLen);

};

#endif /* RULE_CBASERULE_H_ */
