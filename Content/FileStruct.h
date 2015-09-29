/*
 * FileStruct.h
 *
 *  Created on: 2015Äê9ÔÂ23ÈÕ
 *      Author: SmallCroco
 */

#ifndef CONTENT_FILESTRUCT_H_
#define CONTENT_FILESTRUCT_H_

typedef enum EM_FileType {
	en_txt,
	en_off,
	en_rar,
	en_pdf,
	en_zip,
	en_tar,
	en_gz,
	en_7zip,
	en_unknow
};

typedef enum EM_FileEncode {
	en_unknow = 0,
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

#endif /* CONTENT_FILESTRUCT_H_ */
