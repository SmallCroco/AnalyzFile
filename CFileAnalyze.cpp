/*
 * CFileAnalyze.cpp
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#include "CFileAnalyze.h"
#include "FileStruct.h"
#include <iostream>
#include <stdio.h>

using namespace std;

/*
 * @Function Name 	: C_FileAnalyze
 * @Parameter [in]   const char*: pszFilePath --- 文件路径
 * @Description		: 通过文件路径构造对象
 * @Return Value	:
 * @Example			:
 */
C_FileAnalyze::C_FileAnalyze(const char* pszFilePath) {

	m_pszFileData = NULL;
	m_ulFileLen = 0;
	m_emFileType = en_unknow;
	m_pFile = NULL;
	m_pRule = NULL;
	m_pResult = NULL;

	if (NULL != pszFilePath) {

		FILE* fp = fopen(pszFilePath, "rb");
		if (NULL == fp) {
			break;
		}

		fseek(fp, 0L, SEEK_END);
		long len = ftell(fp);
		if (-1L == len) {
			fclose(fp);
			break;
		} else {
			m_ulFileLen = len;
			rewind(fp);
		}

		m_pszFileData = (unsigned char*)malloc(sizeof(unsigned char) * m_ulFileLen);
		if (NULL == m_pszFileData) {

			m_ulFileLen = 0;

			fclose(fp);
			break;
		}
		if (m_ulFileLen != (unsigned long)fread(m_pszFileData, sizeof(unsigned char), m_ulFileLen, fp)) {

			m_ulFileLen = 0;
			free(m_pszFileData);

			fclose(fp);
			break;
		}

		fclose(fp);
	}
}

/*
 *	@Function Name	: C_FileAnalyze
 *	@Parameter [in]	  const char*: pszFileContent --- 文件内容
 *	@Parameter [in]   unsigned long: ulFileLen --- 文件内容长度
 *	@Description		: 通过文件内容构造对象
 *	@Return Value	:
 *	@Example			:
 */
C_FileAnalyze::C_FileAnalyze(const char* pszFileContent, unsigned long ulFileLen) {

	m_pszFileData = NULL;
	m_ulFileLen = 0;
	m_emFileType = en_unknow;
	m_pFile = NULL;
	m_pRule = NULL;
	m_pResult = NULL;

	m_ulFileLen = ulFileLen;
	m_pszFileData = new unsigned char[m_ulFileLen];
	if (NULL == m_pszFileData) {
		m_ulFileLen = 0;
	}

	memcpy(m_pszFileData, pszFileContent, m_ulFileLen);
}

/*
 * @Function Name	: ~C_FileAnalyze
 * @Description		: 析构函数
 * @Return Value	:
 * @Example			:
 */
C_FileAnalyze::~C_FileAnalyze() {

	if (NULL != m_pszFileData) {
		delete m_pszFileData;
		m_pszFileData = NULL;
	}

	if (NULL != m_pRule) {
		delete m_pRule;
		m_pRule = NULL;
	}

	if (NULL != m_pFile) {
		delete m_pFile;
		m_pFile = NULL;
	}

	if (NULL != m_pResult) {
		delete m_pResult;
		m_pResult = NULL;
	}

	m_emFileType = en_unknow;
	m_ulFileLen = 0;
}

/*
 * @Function Name	: SetRule
 * @Parameter [in] const C_BaseRule: pRule -- 匹配规则
 * @Description		: 设置匹配规则
 * @Return Value	: 返回操作状态
 * 	@Example			: bool bl = this->SetRule(pRule);
 */
bool C_FileAnalyze::SetRule(const C_BaseRule* pRule) {

	m_pRule = pRule->CreateObj(void);
	if (NULL == m_pRule) {
		return false;
	} else {
		return true;
	}
}

/*
 * @Function Name	: GetRule
 * @Description		: 获取匹配规则
 * @Return Value	: 返回匹配规则常量，不能在对象外对规则进行修改
 * @Example			:
 */
const C_BaseRule* C_FileAnalyze::GetRule() {

	return m_pRule;
}

/*
 * @Function Name	: GetResult
 * @Description		: 获取匹配结果对象
 * @Return Value	: 返回结果对象
 * @Example			:
 */
const C_Result* C_FileAnalyze::GetResult() {
	return m_pResult;
}

/*
 * @Function Name	: SetFileType
 * @Parameter [in] EM_FileType: emFileType --- 文件类型
 * @Description		: 设置文件类型
 * @Return Value	:
 * @Example			:
 */
void C_FileAnalyze::SetFileType(EM_FileType emFileType) {

	this->m_emFileType = emFileType;
}

/*
 * @Function Name	: GetFileType
 * @Description		: 通过对象获取文件类型
 * @Return Value	: 文件类型
 * @Example			:
 */
const EM_FileType C_FileAnalyze::GetFileType() {

	return this->m_emFileType;
}
/*
 * @Function Name	: GetFileType
 * @Description		: 根据文件内容分析文件类型
 * @Return Value	:　返回操作状态
 * @Example			:
 */
bool C_FileAnalyze::GetType() {


	return true;
}
/*
 *	@Function Name	: Analyze
 *	@Description 	: 对文件进行分析匹配
 *	@Return Value	: 返回操作状态
 *	@Example			:
 */
bool C_FileAnalyze::Analyze() {

	// 如果规则为空，则返回
	if (NULL == m_pRule) {
		cout<<"请先初始化匹配规则"<<endl;
		return false;
	}

	// 创建结果对象，并初始化结果对象
	m_pResult = new C_Result();
	if (m_pResult == NULL) {
		cout<<"初始化结果对象失败"<<endl;
		return false;
	}

	// 如果文件类型对象为未知类型，则获取文件类型
	if (m_emFileType == en_unknow) {
		m_emFileType = this->GetFileType();
	}
	switch (m_emFileType) {
	case en_txt: m_pFile = new C_TxtFile(); break;
	case en_off: m_pFile = new C_OffFile(); break;
	case en_rar: m_pFile = new C_RarFile(); break;
	case en_zip: m_pFile = new C_ZipFile(); break;
	case en_gz: m_pFile  = new C_GzFile(); break;
	case en_pdf: m_pFile = new C_PdfFile(); break;
	case en_tar: m_pFile = new C_TarFile(); break;
	case en_7zip: m_pFile = new C_7zipFile(); break;
	default: m_pFile = NULL;
	}
	if (NULL == m_pFile) {
		cout<<"文件类型识别失败"<<endl;
		return false;
	}


	return m_pFile->Match(m_pRule, m_pResult);
}

