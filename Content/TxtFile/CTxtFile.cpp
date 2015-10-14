/*
 * CTxtFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CTxtFile.h"

/*
 * @Function Name	: C_TxtFile
 * @Parameter [in] const char* pszFilePath --- 文件路径
 * @Parameter [in] const char* pszFileData --- 文件内容
 * @Parameter [in] unsigned long ulFileLen --- 文件内容长度
 * @Parameter [in] EM_FileEncode emEncode = en_unknow --- 文件文本内容编码方式
 * @Description 	: 构造函数
 * @Return Value	:
 */
C_TxtFile::C_TxtFile(const char* pszFilePath, const char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFilePath, pszFileData, ulFileLen, emEncode){

}

/*
 * @Function Name 	: ~C_TxtFile
 * @Description 	: 析构函数
 * @Return Value	:
 */
C_TxtFile::~C_TxtFile() {

}

/*
 * @Function Name	: ExtractTxt
 * @Description		: 获取文件的文本内容
 * @Return Value	: 返回操作状态
 */
bool C_TxtFile::ExtractTxt() {

	m_strText.append(m_pszFileData, m_ulFileLen);

	m_ulTextLen = m_ulFileLen;

	return true;
}
