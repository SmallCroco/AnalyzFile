/*
 * FileStruct.h
 *
 *  Created on: 2015��9��23��
 *      Author: SmallCroco
 */

#ifndef CONTENT_FILESTRUCT_H_
#define CONTENT_FILESTRUCT_H_

enum EM_FileType {
	en_txt,
	en_off,
	en_rar,
	en_pdf,
	en_zip,
	en_tar,
	en_gz,
	en_7zip,
	en_xml,
	en_rtf,
	en_html,
	en_unknow
};

enum EM_FileEncode {
	en_unknowEncode = 0,
	en_ascii = 1,
	en_iso_8599 = 2,
	en_utf_7 = 4,
	en_utf_8 = 8,
	en_utf_16 = 16,
	en_utf_16le = 32,
	en_utf_16be = 64,
	en_utf_32 = 128,
	en_utf_32le = 256,
	en_utf_32be = 512,
	en_gbk = 1024,
	en_gb2312 = 2048,
	en_gb18030 = 4096,
	en_big5 = 8192
};

struct tar_header {
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
	char padding[12];
};

#endif /* CONTENT_FILESTRUCT_H_ */
