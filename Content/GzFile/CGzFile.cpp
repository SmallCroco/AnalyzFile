/*
 * CGzFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CFileAnalyze.h"
#include "CGzFile.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define ZLIB_COPY_BUFFER_SIZE (1024*2)

/*
 * @Function Name	: C_HtmlFile
 * @Parameter [in] const char* pszFilePath --- 文件路径
 * @Parameter [in] const char* pszFileData --- 文件内容
 * @Parameter [in] unsigned long ulFileLen --- 文件内容长度
 * @Parameter [in] EM_FileEncode emEncode = en_unknow --- 文件文本内容编码方式
 * @Description 	: 构造函数
 * @Return Value	:
 */
C_GzFile::C_GzFile(const char* pszFilePath, const unsigned char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFilePath, pszFileData, ulFileLen, emEncode){

}

/*
 * @Function Name 	: ~C_HtmlFile
 * @Description 	: 析构函数
 * @Return Value	:
 */
C_GzFile::~C_GzFile() {
	// TODO Auto-generated destructor stub
}

/*
 * @Function Name	: ExtractTxt
 * @Description		: 获取文件的文本内容
 * @Return Value	: 返回操作状态
 */
bool C_GzFile::ExtractTxt() {

	Bytef* pOutputData = NULL;
	unsigned long nOutputLen = 0;

	bool bl = ungzip((Bytef*)m_pszFileData, m_ulFileLen, &pOutputData, &nOutputLen);
	if (bl == true) {

			FILE *f = fopen("./test.tar", "wb");
			if (NULL == f) {
				std::cout<<"创建.gz包中的文件时，创建失败"<<std::endl;
				return false;
			}

			if (fwrite(pOutputData, sizeof(Bytef), nOutputLen, f) != nOutputLen) {

				fclose(f);
				// 删除文件
				remove("./test.tar");
				return false;
			} else {
				fclose(f);

				// 进一步分析文件
				C_FileAnalyze* file = new C_FileAnalyze("./test.tar");
				file->SetRule(m_pRule);
				file->SetResult(m_pResult);

				if (file->Analyze() == false) {
					std::cout<<".gz包中的：文件分析失败"<<std::endl;
					delete file;
					// 删除文件
					remove("./test.tar");

					return false;
				}

				// 删除文件
				remove("./test.tar");
				return true;
			}
		} else {
			std::cout<<"解压.gz包时出错"<<std::endl;
			return false;
		}
}

bool C_GzFile::ungzip(Bytef* pInputbuf, unsigned long inputlen, Bytef** pOutputbuf, unsigned long* pOutputlen) {

	int ret = 0;	// 返回结果

	unsigned long have = 0;	// 每次实际解压的长度
	unsigned long offset = 0; // 每次解压完后的总长度

	unsigned long maxoutbufsize = 0;	// 每一次分配内存后的大小
	uLong comprLen = inputlen;			// 解压前的总长度
	uLong uncomprLen = ZLIB_COPY_BUFFER_SIZE;	//　每次需要解压的长度

	// m_copybuf用于每一次解压结果的存放
	Bytef m_copybuf[ZLIB_COPY_BUFFER_SIZE];
	memset(m_copybuf, 0 , sizeof(Bytef)*ZLIB_COPY_BUFFER_SIZE);
	strcpy((char*)m_copybuf, "garbage");

	// m_pOutputbuf 用于存放最后的解压结果
	Bytef* m_pOutputbuf = new Bytef[ZLIB_COPY_BUFFER_SIZE];
	memset(m_pOutputbuf, 0, sizeof(Byte)*ZLIB_COPY_BUFFER_SIZE);
	(*pOutputbuf) = m_pOutputbuf;

	z_stream d_stream;

	d_stream.zalloc = Z_NULL;
	d_stream.zfree = Z_NULL;
	d_stream.opaque = Z_NULL;
	d_stream.next_in = pInputbuf;
	d_stream.avail_in = comprLen;

	ret = inflateInit2(&d_stream, 47);
	if (ret != Z_OK) {
		return false;
	}

	do {
		d_stream.next_out = m_copybuf;	// 指定每次解压的内容存放位置
		d_stream.avail_out = uncomprLen;	// 指定每次需要解压的长度
		ret = inflate(&d_stream, Z_NO_FLUSH);
		if (ret == Z_STREAM_END) {
			break;
		}

		switch (ret) {
		case Z_NEED_DICT: {
			return false;
		}

		case Z_DATA_ERROR: {
			inflateEnd(&d_stream);
			return false;
		}

		case Z_MEM_ERROR: {
			inflateEnd(&d_stream);
			return false;
		}
		}

		// 这里得到每次实际解压的长度
		have = uncomprLen - d_stream.avail_out;

		// 每次解压完后的总长度
		unsigned long length = offset + have;
		// 只要每一次解压的实际长度have大于零，则每一次解压后的总长度就会大于上一次解压后的长度
		if (length > maxoutbufsize) {
			maxoutbufsize = length + ZLIB_COPY_BUFFER_SIZE;
			// 重新分配内存空间
			m_pOutputbuf = (Bytef*)realloc(m_pOutputbuf, sizeof(Bytef)*maxoutbufsize);
			if (m_pOutputbuf == NULL) {
				m_pOutputbuf = (*pOutputbuf);
				return false;
			} else {
				(*pOutputbuf) = m_pOutputbuf;
			}
		}

		memcpy((char*)(m_pOutputbuf+offset), m_copybuf, have);
		offset += have;

		memset(m_copybuf, 0 , sizeof(Bytef)*ZLIB_COPY_BUFFER_SIZE);

	} while(d_stream.avail_out == 0);

	inflateEnd(&d_stream);
	*pOutputlen = offset;

	return true;
}

bool C_GzFile::AnalyzeFile() {

	// 解压Gz文件
	bool bl = ExtractTxt();

	return bl;
}
