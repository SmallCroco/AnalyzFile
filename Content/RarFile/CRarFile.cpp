/*
 * CRarFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CRarFile.h"
#include "CFileAnalyze.h"
#include "dll.hpp"
#include <string.h>
#include <iostream>
#include <stdio.h>


using namespace std;

/*
 * @Function Name	: C_RarFile
 * @Parameter [in] const char* pszFilePath --- 文件路径
 * @Parameter [in] const char* pszFileData --- 文件内容
 * @Parameter [in] unsigned long ulFileLen --- 文件内容长度
 * @Parameter [in] EM_FileEncode emEncode = en_unknow --- 文件文本内容编码方式
 * @Description 	: 构造函数
 * @Return Value	:
 */
C_RarFile::C_RarFile(const char* pszFilePath, const unsigned char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFilePath, pszFileData, ulFileLen, emEncode){

}

/*
 * @Function Name 	: ~C_RarFile
 * @Description 	: 析构函数
 * @Return Value	:
 */
C_RarFile::~C_RarFile() {

}

/*
 * @Function Name	: ExtractTxt
 * @Description		: 获取文件的文本内容
 * @Return Value	: 返回操作状态
 */
bool C_RarFile::ExtractTxt() {

	// 打开压缩包
	RAROpenArchiveData ArchiveData;
	memset(&ArchiveData, 0, sizeof(RAROpenArchiveData));

	ArchiveData.ArcName = (char*)m_pszFilePath;
	// 打开模式：RAR_OM_LIST或RAR_OM_EXTRACT
	//		RAR_OM_LIST 只读取文件头，获取一些文件信息，而不解压文件
	//		RAR_OM_EXTRACT 为检测或者解压缩而打开压缩包
	ArchiveData.OpenMode = RAR_OM_EXTRACT;
	// 输出结果：
	//		0成功
	//		ERAR_NO_MEMORY 内存不足，无法初始化数据结构
	//		ERAR_BAD_DATA 压缩包头损坏
	//		ERAR_BAD_ARCHIVE 不是有效的Rar压缩包
	// 		ERAR_UNKNOWN_FORMAT 无法识别的压缩方式
	//		ERAR_EOPEN 压缩包打开错误
	ArchiveData.OpenResult = 0;
	//		设置存放注释缓冲区，最大不能超过64KB;设为null表示不读取注释
	ArchiveData.CmtBuf = NULL;
	//		设置缓冲区大小
	ArchiveData.CmtBufSize = 0;
	//		实际读取到的注释大小
	ArchiveData.CmtSize = 0;
	//		输出注释状态：
	//		0  注释不存在
	//		1  注释读取完毕
	// 		ERAR_NO_MEMORY 内存不足
	// 		ERAR_BAD_DATA 注释损坏
	//		ERAR_UNKNOWN_FORMAT 注释格式无效
	//		ERAR_SMALL_BUF 缓冲区过小
	ArchiveData.CmtState = 0;

	HANDLE handle = RAROpenArchive(&ArchiveData);
	if (ArchiveData.OpenResult != 0) {
		cout << "rar解压出错,文件包打开失败" << endl;
		return false;
	}

	// 设置回调函数
	RARSetCallback(handle, function, 2);

	RARHeaderData headerdata;
	int RHCode;
	while ((RHCode = RARReadHeader(handle, &headerdata)) == 0) {

		int PFCode = RARProcessFile(handle, RAR_EXTRACT, NULL, NULL);
		if (PFCode != 0) {
			cout << "Rar 解压出错" << endl;
			return false;
		}

		// 进一步分析文件
		C_FileAnalyze* file = new C_FileAnalyze(headerdata.FileName);
		file->SetRule(m_pRule);
		file->SetResult(m_pResult);

		if (file->Analyze() == false) {
			cout<<"Rar包中的："<<headerdata.FileName<<"分析失败"<<endl;
		}

		delete file;

		// 删除文件
		remove(headerdata.FileName);
	}

	if (RHCode == ERAR_BAD_DATA) {
		cout << "Rar 文件头损坏" << endl;
		return false;
	}

	RARCloseArchive(handle);

	return true;
}

int C_RarFile::function(unsigned int msg, long int UserData, long int P1, long int P2){

	switch (msg) {
	// 表示解压多个卷的压缩包
	case UCM_CHANGEVOLUME: {

		// 如果P2为RAR_VOL_ASK,则表示需要的一个卷找不到,例如几个分卷不在同一文件夹下
		// 需要的卷名称为P1指向的字符串。
		// 此时有两种解决办法，一种是把需要的卷路径(带卷名称)赋值给P1,然后返回一个非负数，解压继续
		// 另一种办法就是直接返回-1，终止解压过程
		if (P2 == RAR_VOL_ASK) {
			cout<<"\nRar 解压需要另一个压缩卷：" << (char*) P1 <<endl;
			return -1;
		}

		if (P2 == RAR_VOL_NOTIFY) {
			return 0;
		}

		return 0;
	}

	// 正常的解压过程
	// P1指向解压数据的地址
	// P2解压数据的大小
	case UCM_PROCESSDATA: {
		return 0;
	}

	// 需要密码才能解压
	// Ｐ1指向密码缓冲区地址
	// Ｐ2缓冲区大小
	case UCM_NEEDPASSWORD: {
		cout<<"Rar 解压需要密码"<<endl;
		return -1;
	}
	}

	return 1;
}

bool C_RarFile::AnalyzeFile() {

	bool bl = false;

	// 解压rar文件
	bl = ExtractTxt();

	return bl;
}
