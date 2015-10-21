/*
 * CBaseFile.h
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#ifndef CONTENT_CBASEFILE_H_
#define CONTENT_CBASEFILE_H_

#include "CRegularResult.h"
#include <iostream>
#include "CBaseRule.h"

using std::string;

class C_BaseFile {
public:

	// 构造文件对象
	C_BaseFile(const char* pszFilePath, const unsigned char* pszFileData,
			unsigned long ulFileLen, EM_FileEncode emEncode = en_unknowEncode);

	// 析构函数
	virtual ~C_BaseFile();

	// 获取文件的内容
	const char* GetFileData();

	// 获取文件的内容长度
	unsigned long GetFileLen();

	// 获取文件的文本内容
	std::string GetFileTxt();

	// 获取文件文本长度
	unsigned long GetFileTxtLen();

	// 获取文件文本编码方式
	EM_FileEncode GetEncode();

	// 设置匹配规则
	void SetRule(C_BaseRule* pRule);

	// 设置匹配结果
	void SetResult(C_RegularResult* pResult);

	// 分析文件
	virtual bool AnalyzeFile() = 0;

private:

	// 提取文件内容
	virtual bool ExtractTxt() = 0;

protected:
	const char* 		m_pszFilePath;	//	文件路径
	char*				m_pszFileData;	// 文件内容
	unsigned long 	m_ulFileLen;		// 文件内容长度
	std::string		m_strText;		// 文件文本内容
	unsigned long	m_ulTextLen;		// 文件文本内容长度

	EM_FileEncode	m_emEncode;		// 文件文本编码方式

	C_BaseRule*			m_pRule;			// 文件匹配规则
	C_RegularResult* 	m_pResult;		// 文件匹配结果
};

#endif /* CONTENT_CBASEFILE_H_ */
