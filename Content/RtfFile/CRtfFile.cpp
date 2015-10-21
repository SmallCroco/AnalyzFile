/*
 * CRtfFile.cpp
 *
 *  Created on: 2015年10月8日
 *      Author: smallcroco
 */

#include "CRtfFile.h"
#include "plain_text_extractor.h"
#include "metadata.h"
#include "uchardet.h"
#include <string.h>

using namespace doctotext;

/*
 * @Function Name	: C_RtfFile
 * @Parameter [in] const char* pszFilePath --- 文件路径
 * @Parameter [in] const char* pszFileData --- 文件内容
 * @Parameter [in] unsigned long ulFileLen --- 文件内容长度
 * @Parameter [in] EM_FileEncode emEncode = en_unknow --- 文件文本内容编码方式
 * @Description 	: 构造函数
 * @Return Value	:
 */
C_RtfFile::C_RtfFile(const char* pszFilePath, const unsigned char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFilePath, pszFileData, ulFileLen, emEncode){

}

/*
 * @Function Name 	: ~C_RtfFile
 * @Description 	: 析构函数
 * @Return Value	:
 */
C_RtfFile::~C_RtfFile() {

}

/*
 * @Function Name	: ExtractTxt
 * @Description		: 获取文件的文本内容
 * @Return Value	: 返回操作状态
 */
bool C_RtfFile::ExtractTxt() {

	PlainTextExtractor extractor;
	extractor.setVerboseLogging(true);

	if (!extractor.processFile(m_pszFileData, m_ulFileLen, m_strText)) {
		return false;
	}

	return true;
}

/*
 * @Function Name	: GetFileEncode
 * @Description		: 分析获取文件的文本内容
 * @Return Value	: 返回操作状态
 * @Example			:
 */
bool C_RtfFile::GetFileEncode() {
	if (m_emEncode != en_unknowEncode) {
		return true;
	}

	if (m_strText.length() > 0) {
		uchardet_t ud = uchardet_new();
		if (uchardet_handle_data(ud, m_strText.c_str(), m_ulTextLen) != 0) {
			std::cout<<"分析编码失败!"<<std::endl;
			m_emEncode = en_unknowEncode;

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
			m_emEncode = en_unknowEncode;
			uchardet_delete(ud);
			return true;
		}

		m_emEncode = en_unknowEncode;
		uchardet_delete(ud);
		return true;

	} else {
		std::cout<<"文本内容为空"<<std::endl;
		return false;
	}
}

bool C_RtfFile::AnalyzeFile() {

	// 获取文本
	if (ExtractTxt()) {

		// 获取文本编码方式
		if (GetFileEncode()) {

			switch(m_emEncode) {
			case en_ascii: m_pRule->asciiMatch(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_iso_8599: m_pRule->iso8599Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_utf_7: m_pRule->utf7Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_utf_8: m_pRule->utf8Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_utf_16: m_pRule->utf16Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_utf_16le: m_pRule->utf16Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_utf_16be: m_pRule->utf16Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_utf_32: m_pRule->utf32Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_utf_32le: m_pRule->utf32Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_utf_32be: m_pRule->utf32Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_gbk: m_pRule->gb18030Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_gb2312: m_pRule->gb18030Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_gb18030: m_pRule->gb18030Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_big5: m_pRule->big5Match(m_strText.c_str(), m_ulTextLen, m_pResult); break;
			case en_unknowEncode: return false;
			}

			return true;
		}
	}

	return false;
}
