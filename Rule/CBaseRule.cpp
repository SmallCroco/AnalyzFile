/*
 * CBaseRule.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include <iconv.h>
#include <errno.h>
#include <iostream>
#include "CBaseRule.h"

using namespace std;

C_BaseRule::~C_BaseRule() {
}

bool C_BaseRule::ChangeTextEncode(EM_FileEncode emSrcEncode, EM_FileEncode emDestEncode,
		char* pszSrcText, size_t* pSrcLen, char* pszDestText, size_t* pDestLen) {

	const char* fromcode;
	const char* tocode;

	switch (emSrcEncode) {
	case en_ascii: fromcode = "ascii"; break;
	case en_iso_8599: fromcode = "big-5"; break;
	case en_utf_7: fromcode = "utf-7"; break;
	case en_utf_8: fromcode = "utf-8"; break;
	case en_utf_16: fromcode = "utf-16"; break;
	case en_utf_16le: fromcode = "utf-16le"; break;
	case en_utf_16be: fromcode = "utf-16be"; break;
	case en_utf_32: fromcode = "utf-32"; break;
	case en_utf_32le: fromcode = "utf-32le"; break;
	case en_utf_32be: fromcode = "utf-32be"; break;
	case en_gbk: fromcode = "gbk"; break;
	case en_gb2312: fromcode = "gb2312"; break;
	case en_gb18030: fromcode = "gb18030"; break;
	case en_big5: fromcode = "big5"; break;
	default: fromcode = NULL;
	}

	switch (emDestEncode) {
	case en_ascii: tocode = "ascii"; break;
	case en_iso_8599: tocode = "big-5"; break;
	case en_utf_7: tocode = "utf-7"; break;
	case en_utf_8: tocode = "utf-8"; break;
	case en_utf_16: tocode = "utf-16"; break;
	case en_utf_16le: tocode = "utf-16le"; break;
	case en_utf_16be: tocode = "utf-16be"; break;
	case en_utf_32: tocode = "utf-32"; break;
	case en_utf_32le: tocode = "utf-32le"; break;
	case en_utf_32be: tocode = "utf-32be"; break;
	case en_gbk: tocode = "gbk"; break;
	case en_gb2312: tocode = "gb2312"; break;
	case en_gb18030: tocode = "gb18030"; break;
	case en_big5: tocode = "big5"; break;
	default: tocode = NULL;
	}

	iconv_t hCodeConverter = iconv_open(tocode, fromcode);

	if ((iconv_t) -1 == hCodeConverter) {
		return false;
	}

	int nRet = iconv(hCodeConverter, &pszSrcText, pSrcLen, &pszDestText, pDestLen);

	if (nRet < 0) {

		switch (errno) {
		case E2BIG: cout<<"errno: E2BIG(OutBuf空间不够)"<<endl; break;
		case EILSEQ: cout<<"errno: EILSEQ(InBuf多字节序无效)"<<endl; break;
		case EINVAL: cout<<"errno: EINVAL(有残留的字节未转换)"<<endl; break;
		default: break;
		}

		iconv_close(hCodeConverter);
		return false;
	}

	return true;
}
