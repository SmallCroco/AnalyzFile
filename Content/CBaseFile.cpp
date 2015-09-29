/*
 * CBaseFile.cpp
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#include "CBaseFile.h"

C_BaseFile::C_BaseFile(const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode = en_unknow) {
	m_pszFileData = NULL;
	m_ulFileLen = 0;
	m_strText = "";
	m_ulTextLen = 0;
	m_emEncode = en_unknow;
}

C_BaseFile::~C_BaseFile() {

}

const char* C_BaseFile::GetFileData() {

	return (const char*)m_pszFileData;
}

unsigned long C_BaseFile::GetFileLen() {

	return m_ulFileLen;
}

string C_BaseFile::GetFileTxt() {

	return m_strText;
}

unsigned long C_BaseFile::GetFileTxtLen() {

	return m_ulTextLen;
}

EM_FileEncode C_BaseFile::GetEncode() {

	return m_emEncode;
}

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

void C_BaseFile::Match(const C_BaseRule* pRule, C_Result* pResult) {

	if (NULL == pRule) {
		return ;
	}

	if (NULL == pResult) {
		return;
	}


}
