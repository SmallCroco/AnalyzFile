/*
 * CBaseFile.cpp
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#include "CBaseFile.h"
#include "uchardet.h"
#include <iostream>
#include <string.h>

/*
 * @Function Name	: C_BaseFile
 * @Parameter [in] const char* pszFilePath --- 文件路径
 * @Parameter [in] const char* pszFileData --- 文件内容
 * @Parameter [in] unsigned long ulFileLen --- 文件内容长度
 * @Parameter [in] EM_FileEncode emEncode = en_unknow　--- 文件的文本内容编码方式
 * @Description		: 构造函数
 * @Return Value	:
 */
C_BaseFile::C_BaseFile(const char* pszFilePath, const unsigned char* pszFileData,
		unsigned long ulFileLen, EM_FileEncode emEncode):m_pszFilePath(pszFilePath) {

	if (NULL != pszFileData) {
		m_pszFileData = new char[ulFileLen];
		if (NULL != m_pszFileData) {
			memset(m_pszFileData, 0, ulFileLen*sizeof(char));
			memcpy(m_pszFileData, pszFileData, ulFileLen*sizeof(char));
			m_ulFileLen = ulFileLen;
		} else {
			m_pszFileData = NULL;
			m_ulFileLen = 0;
		}
	} else {
		m_pszFileData = NULL;
		m_ulFileLen = 0;
	}

	m_strText = "";
	m_ulTextLen = 0;
	m_emEncode = emEncode;

	m_pRule = NULL;
	m_pResult = NULL;
}

/*
 * @Function Name	: ~C_BaseFile
 * @Description		: 析构函数
 * @Return Value	:
 */
C_BaseFile::~C_BaseFile() {
	if (NULL != m_pszFileData) {
		delete m_pszFileData;
		m_pszFileData = NULL;
	}

	m_ulFileLen = 0;
	m_strText = "";
	m_ulTextLen = 0;

	m_emEncode = en_unknowEncode;

	if (NULL != m_pRule) {
		delete m_pRule;
		m_pRule = NULL;
	}

}

/*
 * @Function Name	: GetFileData
 * @Description		: 获取文件的内容
 * @Return Value	: 返回文件的内容
 */
const char* C_BaseFile::GetFileData() {
	return (const char*)m_pszFileData;
}

/*
 * @Function Name	: GetFileLen
 * @Description		: 获取文件的内容长度
 * @Return Value	: 返回文件的内容长度
 */
unsigned long C_BaseFile::GetFileLen() {

	return m_ulFileLen;
}

/*
 * @Function Name	: GetFileTxt
 * @Description		: 获取文件的文本内容
 * @Return Value	: 返回文件的文本内容
 * @Example			:
 */
string C_BaseFile::GetFileTxt() {
	return m_strText;
}

/*
 * @Function Name	: GetFileTxtLen
 * @Description		: 获取文件的文本内容长度
 * @Return Value	: 返回文件的文本内容长度
 * @Example			:
 */
unsigned long C_BaseFile::GetFileTxtLen() {
	return m_ulTextLen;
}

/*
 * @Function Name	: GetEncode
 * @Description		: 获取文件的文本编码方式printf(
 * @Return Value	: 返回文件的文本编码方式
 * @Example			:
 */
EM_FileEncode C_BaseFile::GetEncode() {
	return m_emEncode;
}

/*
 * @Function Name	: SetResult
 * @Parameter [in] C_BaseResult* pResult --- 匹配结果
 * @Description		: 设置匹配结果
 * @Return Value	: void
 */
void C_BaseFile::SetResult(C_RegularResult* pResult) {

	m_pResult = pResult;
}

/*
 * @Function Name	: SetRule
 * @Description		: 设置匹配规则
 * @Return Value	: void
 */
void C_BaseFile::SetRule(C_BaseRule* pRule) {

	m_pRule = pRule->CreateObj();
}
