/*
 * CPatternUnit.cpp
 *
 *  Created on: 2015Äê9ÔÂ25ÈÕ
 *      Author: SmallCroco
 */

#include "CPatternUnit.h"

C_PatternUnit::C_PatternUnit() {
	m_nPid = 0;
	m_pName = NULL;
	m_pContent = NULL;
	m_nContentLen = 0;

	m_pPcre = NULL;
	m_pPcreExtra = NULL;
}

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

	if (NULL != m_pPcre) {
		pcre_free(m_pPcre);
		m_pPcre = NULL;
	}

	if (NULL != m_pPcreExtra) {
		pcre_free_study(m_pPcreExtra);
		m_pPcreExtra = NULL;
	}
}

const void* C_PatternUnit::getPcre() {

		return (const void*)m_pPcre;
}

const void* C_PatternUnit::getPcreExtra() {

		return (const void*)m_pPcreExtra;
}

