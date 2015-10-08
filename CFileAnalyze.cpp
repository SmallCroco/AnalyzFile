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

		m_pszFileData = (unsigned char*) malloc(
				sizeof(unsigned char) * m_ulFileLen);
		if (NULL == m_pszFileData) {

			m_ulFileLen = 0;

			fclose(fp);
			break;
		}
		if (m_ulFileLen
				!= (unsigned long) fread(m_pszFileData, sizeof(unsigned char),
						m_ulFileLen, fp)) {

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
C_FileAnalyze::C_FileAnalyze(const char* pszFileContent,
		unsigned long ulFileLen) {

	m_pszFileData = NULL;
	m_ulFileLen = 0;
	m_emFileType = en_unknow;
	m_pFile = NULL;
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

	// Rtf文件
	if (m_pszFileData[0] == 0x7B && m_pszFileData[1] == 0x5C
			&& m_pszFileData[2] == 0x72 && m_pszFileData[3] == 0x74
			&& m_pszFileData[4] == 0x66) {
		m_emFileType = en_rtf;
		return true;
	}

	// Html文件
	if (m_pszFileData[0] == 0x68 && m_pszFileData[1] == 0x74
			&& m_pszFileData[2] == 0x6D && m_pszFileData[3] == 0x6C
			&& m_pszFileData[4] == 0x3E) {
		m_emFileType = en_html;
		return true;
	}

	// xml文件
	if (m_pszFileData[0] == 0x3C && m_pszFileData[1] == 0x3F
			&& m_pszFileData[2] == 0x78 && m_pszFileData[3] == 0x6D
			&& m_pszFileData[4] == 0x6C) {
		m_emFileType = en_xml;
		return true;
	}

	// PDF文件
	if (m_pszFileData[0] == 0x25 && m_pszFileData[1] == 0x50
			&& m_pszFileData[2] == 0x44 && m_pszFileData[3] == 0x46
			&& m_pszFileData[4] == 0x2D && m_pszFileData[5] == 0x31
			&& m_pszFileData[6] == 0x2E) {
		m_emFileType = en_pdf;
		return true;
	}

	// Off复合二进制文件
	if (m_pszFileData[0] == 0xD0 && m_pszFileData[1] == 0xCF
			&& m_pszFileData[2] == 0x11 && m_pszFileData[3] == 0xE0) {
		m_emFileType = en_off;
		return true;
	}

	// Rar文件
	if (m_pszFileData[0] == 0x52 && m_pszFileData[1] == 0x61
			&& m_pszFileData[2] == 0x72 && m_pszFileData[3] == 0x21) {
		m_emFileType = en_rar;
		return true;
	}

	// Zip文件
	if (m_pszFileData[0] == 0x50 && m_pszFileData[1] == 0x4B
			&& m_pszFileData[2] == 0x03 && m_pszFileData[3] == 04) {
		m_emFileType = en_zip;
		return true;
	}

	// tar文件
	if (m_ulFileLen > 512) {
		tar_header* tarHeader = (tar_header*) m_pszFileData;
		if ((tarHeader->magic[0] != 'u') || (tarHeader->magic[1] != 's')
				|| (tarHeader->magic[2] != 't') || (tarHeader->magic[3] != 'a')
				|| (tarHeader->magic[4] != 'r')
				|| (tarHeader->magic[5] != ' ')) {
			// 没有tar标志,进一步判断

			// 取出校验值
			unsigned long chksum = 0;
			for (int i = 7; i >= 0; i--) {

				if (tarHeader->chksum[i] >= 0x30) {
					unsigned int s = tarHeader->chksum[i] - 0x30;
					int j = 7 - i;
					while (j > 2) {
						s *= 8;
						j--;
					}
					chksum += s;
				}

				tarHeader->chksum[i] = 0x20;

			}

			// 计算校验和
			unsigned int sum = 0;
			for (int i = 0; i < 512; i++) {
				sum += m_pszFileData[i];
			}

			// 如果相等，则是tar文件
			if (sum == chksum) {

				m_emFileType = en_tar;
				return true;

			}
		} else {
			// 是tar文件

			m_emFileType = en_tar;
			return true;
		}
	}

	// gz文件
	if (m_pszFileData[0] == 0x1F && m_pszFileData[1] == 0x8B && m_pszFileData[2] == 0x0B ) {
		m_emFileType = en_gz;
		return true;
	}

	// 7-zip文件
	if (m_pszFileData[0] == 0x37 && m_pszFileData[1] == 0x7A && m_pszFileData[2] == 0xBC &&
			m_pszFileData[3] == 0xAF && m_pszFileData[4] == 0x27 && m_pszFileData[5] == 0x1C) {
		m_emFileType = en_7zip;
		return true;
	}

	m_emFileType = en_txt;

}
/*
 *	@Function Name	: Analyze
 *	@Description 	: 对文件进行分析匹配
 *	@Return Value	: 返回操作状态
 *	@Example			:
 */
bool C_FileAnalyze::Analyze(const C_BaseRule* pRule) {

	if (NULL == pRule) {
		cout << "匹配规则不能为空" << endl;
		return false;
	}

	// 创建结果对象，并初始化结果对象
	m_pResult = new C_Result();
	if (m_pResult == NULL) {
		cout << "初始化结果对象失败" << endl;
		return false;
	}

	// 如果文件类型对象为未知类型，则获取文件类型
	if (m_emFileType == en_unknow) {
		m_emFileType = this->GetFileType();
	}
	switch (m_emFileType) {
	case en_txt:
		m_pFile = new C_TxtFile();
		break;
	case en_off:
		m_pFile = new C_OffFile();
		break;
	case en_rar:
		m_pFile = new C_RarFile();
		break;
	case en_zip:
		m_pFile = new C_ZipFile();
		break;
	case en_gz:
		m_pFile = new C_GzFile();
		break;
	case en_pdf:
		m_pFile = new C_PdfFile();
		break;
	case en_tar:
		m_pFile = new C_TarFile();
		break;
	case en_7zip:
		m_pFile = new C_7zipFile();
		break;
	case en_xml:
		m_pFile = new C_XmlFile();
		break;
	case en_rtf:
		m_pFile = new C_RtfFile();
		break;
	case en_html:
		m_pFile = new C_HtmlFile();
		break;
	default:
		m_pFile = NULL;
	}
	if (NULL == m_pFile) {
		cout << "文件类型识别失败" << endl;
		return false;
	}

	return m_pFile->Match(pRule, m_pResult);
}

