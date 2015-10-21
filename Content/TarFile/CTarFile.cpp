/*
 * CTarFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CTarFile.h"
#include "CFileAnalyze.h"

/*
 * @Function Name	: C_TarFile
 * @Parameter [in] const char* pszFilePath --- 文件路径
 * @Parameter [in] const char* pszFileData --- 文件内容
 * @Parameter [in] unsigned long ulFileLen --- 文件内容长度
 * @Parameter [in] EM_FileEncode emEncode = en_unknow --- 文件文本内容编码方式
 * @Description 	: 构造函数
 * @Return Value	:
 */
C_TarFile::C_TarFile(const char* pszFilePath, const unsigned char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFilePath, pszFileData, ulFileLen, emEncode){

}

/*
 * @Function Name 	: ~C_TarFile
 * @Description 	: 析构函数
 * @Return Value	:
 */
C_TarFile::~C_TarFile() {
	// TODO Auto-generated destructor stub
}

/*
 * @Function Name	: ExtractTxt
 * @Description		: 获取文件的文本内容
 * @Return Value	: 返回操作状态
 */
bool C_TarFile::ExtractTxt() {

	char* p = m_pszFileData;

	while ((p != NULL) && (m_ulFileLen > 0)) {

		// 获取tar文件头结构
		tar_header* tarHeader = (tar_header*)p;
		p = p + 512;

		// 获取文件大小
		unsigned int fSize = 0;
		for (int i=10; i>=0; i--) {
			unsigned int size = tarHeader->size[i];
			int j = 11 - i;
			while(j>1) {
				size = size * 8;
				j--;
			}
			fSize += size;
		}

		// 获取文件内容
		if (fSize > 0) {
			char* pszFileData = p;
			unsigned long ulFileLen = fSize;

			C_FileAnalyze* file = new C_FileAnalyze(pszFileData, ulFileLen);
			file->SetRule(m_pRule);
			file->SetResult(m_pResult);

			if (file->Analyze() == false) {
				std::cout<<tarHeader->name<<"分析失败"<<std::endl;
			}

			p = p + fSize;
		}
	}

	return true;
}

bool C_TarFile::AnalyzeFile() {

	bool bl = false;

	// 获取解包文件
	bl = ExtractTxt();

	return bl;
}
