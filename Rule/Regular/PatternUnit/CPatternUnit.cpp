/*
 * CPatternUnit.cpp
 *
 *  Created on: 2015��9��25��
 *      Author: SmallCroco
 */

#include "CPatternUnit.h"
#include <stdlib.h>

/*
 * @Function Name	: C_PatternUnit
 * @Description		: 构造函数
 */
C_PatternUnit::C_PatternUnit() {
	m_nPid = 0;
	m_pName = NULL;
	m_pContent = NULL;
	m_nContentLen = 0;
}

/*
 * @Function Name	: ~C_PatternUnit
 * @Description		: 析构函数
 */
C_PatternUnit::~C_PatternUnit() {
	m_nPid = 0;
	m_nContentLen = 0;

	if (NULL != m_pName) {
		free(m_pName);
		m_pName = NULL;
	}

	if (NULL != m_pContent) {
		free(m_pContent);
		m_pContent = NULL;
	}
}

