/*
 * CPatternUnit.h
 *
 *  Created on: 2015Äê9ÔÂ25ÈÕ
 *      Author: SmallCroco
 */

#ifndef RULE_REGULAR_CPATTERNUNIT_H_
#define RULE_REGULAR_CPATTERNUNIT_H_

class C_PatternUnit {
public:
	C_PatternUnit();
	virtual ~C_PatternUnit();

	const void* getPcre();

	const void* getPcreExtra();

protected:
	virtual int PcreCompile() = 0;


protected:
	int			m_nPid;
	char*		m_pName;
	char*		m_pContent;
	int 		m_nContentLen;

	pcre*		m_pPcre;
	pcre_extra*	m_pPcreExtra;
};

#endif /* RULE_REGULAR_CPATTERNUNIT_H_ */
