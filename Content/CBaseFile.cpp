/*
 * CBaseFile.cpp
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#include "CBaseFile.h"

/*
 * @Function Name	: C_BaseFile
 * @Parameter [in] const char* pszFilePath --- 文件路径
 * @Parameter [in] const char* pszFileData --- 文件内容
 * @Parameter [in] unsigned long ulFileLen --- 文件内容长度
 * @Parameter [in] EM_FileEncode emEncode = en_unknow　--- 文件的文本内容编码方式
 * @Description		: 构造函数
 * @Return Value	:
 */
C_BaseFile::C_BaseFile(const char* pszFilePath, const char* pszFileData,
		unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow):m_pszFilePath(pszFilePath) {

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

	m_emEncode = en_unknow;

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
 * @Description		: 获取文件的文本编码方式
 * @Return Value	: 返回文件的文本编码方式
 * @Example			:
 */
EM_FileEncode C_BaseFile::GetEncode() {
	return m_emEncode;
}

/*
 * @Function Name	: GetFileEncode
 * @Description		: 分析获取文件的文本内容
 * @Return Value	: 返回操作状态
 * @Example			:
 */
bool C_BaseFile::GetFileEncode() {
	if (m_emEncode != en_unknow) {
		return true;
	}

	if (m_strText.length() > 0) {
		uchardet_t ud = uchardet_new();
		if (uchardet_handle_data(ud, m_strText.c_str(), m_ulTextLen) != 0) {
			printf("分析编码失败!\n");
			m_emEncode = en_unknow;

			return false;
		}

		uchardet_data_end(ud);

		// 获取文件内容编码方式
		const char * charset = uchardet_get_charset(ud);
		if (strcmp(charset, "UTF-7") == 0) {
			m_emEncode = en_utf_7;
			uchardet_delete(ud);
			return true;
		}
		if (strcmp(charset, "UTF-8") == 0) {
			m_emEncode = en_utf_8;
			uchardet_delete(ud);
			return true;
		}
		if (strcmp(charset, "GB2312") == 0) {
			m_emEncode = en_gb2312;
			uchardet_delete(ud);
			return true;
		}
		if (strcmp(charset, "BIG5") == 0) {
			m_emEncode = en_big5;
			uchardet_delete(ud);
			return true;
		}
		if (strcmp(charset, "UTF-16") == 0) {

			if ((unsigned char)m_strText[0] == 0xFE && (unsigned char)m_strText[1] == 0xFF) {
				m_emEncode = en_utf_16be;
			} else {
				if ((unsigned char)m_strText[0] == 0xFF && (unsigned char)m_strText[1] == 0xFE) {
					m_emEncode = en_utf_16le;
				} else {
					m_emEncode = en_utf_16;
				}
			}
			uchardet_delete(ud);
			return true;
		}
		if (strcmp(charset, "UTF-32") == 0) {

			if ((unsigned char)m_strText[0] == 0x00 &&
					(unsigned char)m_strText[1] == 0x00 &&
					(unsigned char)m_strText[2] == 0xFE &&
					(unsigned char)m_strText[3] == 0xFF) {
				m_emEncode = en_utf_32be;
			} else {
				if ((unsigned char)m_strText[0] == 0xFF &&
						(unsigned char)m_strText[1] == 0xFE &&
						(unsigned char)m_strText[2] == 0x00 &&
						(unsigned char)m_strText[3] == 0x00) {
					m_emEncode = en_utf_32le;
				} else {
					m_emEncode = en_utf_32;
				}
			}
			uchardet_delete(ud);
			return true;
		}
		if (strcmp(charset, "US-ASCII") == 0) {
			m_emEncode = en_ascii;
			uchardet_delete(ud);
			return true;
		}
		if (strcmp(charset, "gb18030") == 0) {
			m_emEncode = en_gb18030;
			uchardet_delete(ud);
			return true;
		}
		if (*charset == 0) {
			m_emEncode = en_unknow;
			uchardet_delete(ud);
			return true;
		}

		m_emEncode = en_unknow;
		uchardet_delete(ud);
		return true;

	} else {
		return false;
	}
}

/*
 * @Function Name	: SetResult
 * @Parameter [in] C_BaseResult* pResult --- 匹配结果
 * @Description		: 设置匹配结果
 * @Return Value	: void
 */
void C_BaseFile::SetResult(C_BaseResult* pResult) {

	m_pResult = pResult;
}

/*
 * @Function Name	: SetRule
 * @Description		: 设置匹配规则
 * @Return Value	: void
 */
void C_BaseFile::SetRule(const C_BaseRule* pRule) {

	m_pRule = pRule->CreateObj();
}
