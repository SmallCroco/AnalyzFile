/*
 * CPatternUnit.h
 *
 *  Created on: 2015��9��25��
 *      Author: SmallCroco
 */

#ifndef RULE_REGULAR_CPATTERNUNIT_H_
#define RULE_REGULAR_CPATTERNUNIT_H_

class C_PatternUnit {
public:
	C_PatternUnit();
	virtual ~C_PatternUnit();

	const void* getPcre() = 0;

	const void* getPcreExtra() = 0;

protected:
	virtual int PcreCompile() = 0;


protected:
	int				m_nPid;
	char*			m_pName;
	char*			m_pContent;
	int 			m_nContentLen;
};

#endif /* RULE_REGULAR_CPATTERNUNIT_H_ */
