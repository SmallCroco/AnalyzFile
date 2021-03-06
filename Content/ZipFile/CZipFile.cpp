/*
 * CZipFile.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CZipFile.h"
#include "unzip.h"
#include "CFileAnalyze.h"
#include <sys/stat.h>
#include <iostream>

using namespace std;

C_ZipFile::C_ZipFile(const char* pszFilePath, const unsigned char* pszFileData, unsigned long ulFileLen, EM_FileEncode emEncode):
	C_BaseFile(pszFilePath, pszFileData, ulFileLen, emEncode){

}

C_ZipFile::~C_ZipFile() {

}

/*
 * @Function Name	: ExtractTxt
 * @Description 	: 提取文本
 * @Return Value	: 返回操作状态
 */
bool C_ZipFile::ExtractTxt() {

	bool flag = false;

	flag = UnZipFile();

	return flag;

}

bool C_ZipFile::UnZipFile(const char* pszPassword) {
	// 打开ｚｉｐ包
	unzFile uf = unzOpen(m_pszFilePath);
	if (NULL == uf) {
		cout<<"zip 包打开失败"<<endl;
		return false;
	}

	int err = UNZ_OK;

	// zip包中的文件信息
	unz_global_info64 gi;
	err = unzGetGlobalInfo64(uf, &gi);
	if (err != UNZ_OK) {
		cout<<"error: "<<err<<" with zipfile in unzGetGlobalInfo"<<endl;
		return false;
	}

	// 循环解压zip包中的每一个文件
	for (unsigned int i = 0; i < gi.number_entry; i++) {
		unz_file_info64 file_info;	// 文件信息
		char filename_inzip[256];		// zip包中的文件名

		// 获取当前文件信息
		err = unzGetCurrentFileInfo64(uf, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);
		if (err != UNZ_OK) {
			cout<<"error "<<err<<" with zipfilein unzGetCurrentFileInfo64"<<endl;

			//　关闭文件句柄
			err = unzCloseCurrentFile(uf);
			if (err != UNZ_OK) {
				cout<<"error "<<err<<" with zipfile in unzCloseCurrentFile"<<endl;
			}
			return false;
		}

		char* filename_withoutpath;	// zip包中的文件名不带路径
		filename_withoutpath = filename_inzip;
		char* p = filename_inzip;
		while ((*p) != '\0') {
			if (((*p) == '/') || ((*p) == '\\')) {
				filename_withoutpath = p + 1;
			}

			p++;
		}

		// 判断是文件夹还是文件,文件夹不处理
		if ((*filename_withoutpath) != '\0') {
			// 打开当前文件
			err = unzOpenCurrentFilePassword(uf, pszPassword);
			if (err != UNZ_OK) {
				cout<<"error: "<<err<<" with zipfile in unzOpenCurrentFilePassword,zip包文件是一个加密包"<<endl;

				// 关闭文件句柄
				err = unzCloseCurrentFile(uf);
				if (err != UNZ_OK) {
					cout<<"error "<<err<<" with zipfile in unzCloseCurrentFile"<<endl;
				}
				return false;
			}

			// 创建新文件
			FILE* fout = fopen64(filename_withoutpath, "wb");
			if ((fout == NULL)) {
				cout<<"创建zip包中的"<<filename_withoutpath<<"失败"<<endl;
				break;
			}

			// 写入文件内容
			if (fout != NULL) {
				uInt size_buf = 8192;
				void* buf = (void*) malloc(size_buf);

				do {
					// 读取当前文件内容
					err = unzReadCurrentFile(uf, buf, size_buf);
					if (err < 0) {
						cout<<"error "<<err<<" with zipfile in unzReadCurrentFile"<<endl;
						break;
					}

					if (err > 0) {
						if (fwrite(buf, err, 1, fout) != 1) {
							cout<<"error in writing extracted file"<<endl;
							err = UNZ_ERRNO;
							break;
						}
					}
				}while(err > 0);

				if (fout) {
					fclose(fout);
				}

				free(buf);
			}

			// err 等于零表示文件正常写入并结尾
			if (err == 0) {
				// 进一步分析文件
				C_FileAnalyze* file = new C_FileAnalyze(filename_withoutpath);
				file->SetRule(m_pRule);
				file->SetResult(m_pResult);

				if (file->Analyze() == false) {
					cout<<filename_withoutpath<<"分析失败"<<endl;
				}

				delete file;
			}

			// 删除文件
			remove(filename_withoutpath);
		}

		// 指向下一个文件
		if ((i+1) < gi.number_entry) {
			err = unzGoToNextFile(uf);
			if (err != UNZ_OK) {
				cout<<"error "<<err<<" with zipfile in unzGoToNextFile"<<endl;
				break;
			}
		}

	}

	if (err == UNZ_OK) {
		err = unzCloseCurrentFile(uf);
		if (err != UNZ_OK) {
			cout<<"error "<<err<<" with zipfile in unzCloseCurrentFile"<<endl;
		}
	} else {
		unzCloseCurrentFile(uf);
	}

	return true;
}

bool C_ZipFile::AnalyzeFile() {

	// 获取解压文件
	return this->ExtractTxt();
}
