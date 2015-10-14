/*
 * CHtmlFile.cpp
 *
 *  Created on: 2015年10月8日
 *      Author: smallcroco
 */

#include "CHtmlFile.h"
#include "plain_text_extractor.h"
#include "metadata.h"
#include "uchardet.h"

using namespace doctotext;

/*
 * @Function Name	: C_HtmlFile
 * @Parameter [in] const char* pszFilePath --- 文件路径
 * @Parameter [in] const char* pszFileData --- 文件内容
 * @Parameter [in] unsigned long ulFileLen --- 文件内容长度
 * @Parameter [in] EM_FileEncode emEncode = en_unknow --- 文件文本内容编码方式
 * @Description 	: 构造函数
 * @Return Value	:
 */
C_HtmlFile::C_HtmlFile(const char* pszFilePath, const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFilePath, pszFileData, ulFileLen, emEncode){

}

/*
 * @Function Name 	: ~C_HtmlFile
 * @Description 	: 析构函数
 * @Return Value	:
 */
C_HtmlFile::~C_HtmlFile() {
	// TODO Auto-generated destructor stub
}

/*
 * @Function Name	: ExtractTxt
 * @Description		: 获取文件的文本内容
 * @Return Value	: 返回操作状态
 */
bool C_HtmlFile::ExtractTxt() {

	PlainTextExtractor extractor;
	extractor.setVerboseLogging(true);

	if (!extractor.processFile(m_pszFileData, m_ulFileLen, m_strText)) {
		return false;
	}

	return true;
}

