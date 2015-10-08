/*
 * CFileAnalyze.h
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#ifndef CFILEANALYZE_H_
#define CFILEANALYZE_H_

#include "CResult.h"

class C_FileAnalyze {
public:
	C_FileAnalyze(const char* pszFilePath);
	C_FileAnalyze(const char* pszFileContent, unsigned long ulFileLen);
	~C_FileAnalyze();

	bool SetRule(const C_BaseRule* pRule);
	const C_BaseRule* GetRule();

	void SetFileType(EM_FileType emFileType);
	const EM_FileType GetFileType();

	const C_Result* GetResult();

	bool Analyze();

private:
	bool GetType();

private:
	unsigned char*	m_pszFileData;
	unsigned long	m_ulFileLen;
	EM_FileType		m_emFileType;
	C_BaseFile*		m_pFile;
	C_BaseRule*		m_pRule;
	C_Result*			m_pResult;
};

#endif /* CFILEANALYZE_H_ */
