/*
 * CBaseFile.h
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#ifndef CONTENT_CBASEFILE_H_
#define CONTENT_CBASEFILE_H_

#include <iostream>
#include "CBaseRule.h"
#include "CResult.h"

using namespace std;


class C_BaseFile {
public:
	C_BaseFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow);
	virtual ~C_BaseFile();

	const char* GetFileData();
	unsigned long GetFileLen();
	string GetFileTxt();
	unsigned long GetFileTxtLen();
	EM_FileEncode GetEncode();

	bool Match(const C_BaseRule* pRule, C_Result* pResult);

private:
	bool GetFileEncode();


protected:
	char*			m_pszFileData;
	unsigned long 	m_ulFileLen;
	string			m_strText;
	unsigned long	m_ulTextLen;
	EM_FileEncode	m_emEncode;
};

#endif /* CONTENT_CBASEFILE_H_ */
