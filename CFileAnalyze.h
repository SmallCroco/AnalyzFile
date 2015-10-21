/*
 * CFileAnalyze.h
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#ifndef CFILEANALYZE_H_
#define CFILEANALYZE_H_

#include "CBaseFile.h"
#include "CBaseResult.h"
#include "CBaseRule.h"

class C_FileAnalyze {
public:
	// 通过文件路径初始化
	C_FileAnalyze(const char* pszFilePath, EM_FileType emFileType = en_unknow);

	// 通过文件内容初始化
	C_FileAnalyze(const char* pszFileContent, unsigned long ulFileLen, EM_FileType emFileType = en_unknow);

	// 析构函数
	~C_FileAnalyze();

	// 设置匹配规则
	void SetRule(C_BaseRule* pRule);

	// 设置匹配结果
	void SetResult(C_RegularResult* pResult);

	// 获取文件类型
	const EM_FileType GetFileType();

	// 获取规则匹配结果
	const C_BaseResult* GetResult();

	// 文件分析
	bool Analyze();

private:
	// 判断文件类型
	bool GetType();

private:
	const char* 		m_pszFilePath;	//	文件路径
	unsigned char*	m_pszFileData;	// 文件内容
	unsigned long	m_ulFileLen;		// 文件内容长度
	EM_FileType		m_emFileType;	// 文件类型

	C_BaseFile*			m_pFile;			// 文件对象基指针
	C_RegularResult*	m_pResult;		// 文件结果基指针
	C_BaseRule*			m_pRule;			// 文件规则基指针
};

#endif /* CFILEANALYZE_H_ */
