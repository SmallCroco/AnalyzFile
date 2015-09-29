/*
 * CRegularRule.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CRegularRule.h"
#include <iostream>

#define MAX_PATTERNS_FILE_LINE_LENG 2500

using namespace std;

C_RegularRule::C_RegularRule() {

}

C_RegularRule::~C_RegularRule() {

}

int C_RegularRule::InitRules(const char* pszFilePath, int encode) {
	FILE* fp;

	int lineNo = 0;
	char *dealNow, *strEnd, *ptemp;
	char str_line[MAX_PATTERNS_FILE_LINE_LENG];
	if ((m_utf8Patterns.size() != 0) && (encode & en_utf_8) != 0) {
		cout << "UTF-8��������ʽ�Ѿ���ʼ��" << endl;
		return -2;
	}
	if ((m_utf16Patterns.size() != 0) && (encode & en_utf_16) != 0) {
		cout << "UTF-16��������ʽ�Ѿ���ʼ��" << endl;
		return -2;
	}
	if ((m_utf16lePatterns.size() != 0) && (encode & en_utf_16le) != 0) {
		cout << "UTF-16LE��������ʽ�Ѿ���ʼ��" << endl;
		return -2;
	}
	if ((m_utf16bePatterns.size() != 0) && (encode & en_utf_16be) != 0) {
		cout << "UTF-16BE��������ʽ�Ѿ���ʼ��" << endl;
		return -2;
	}
	if ((m_utf32Patterns.size() != 0) && (encode & en_utf_32) != 0) {
		cout << "UTF-32��������ʽ�Ѿ���ʼ��" << endl;
		return -2;
	}
	if ((m_utf32lePatterns.size() != 0) && (encode & en_utf_32le) != 0) {
		cout << "UTF-32LE��������ʽ�Ѿ���ʼ��" << endl;
		return -2;
	}
	if ((m_utf32bePatterns.size() != 0) && (encode & en_utf_32be) != 0) {
		cout << "UTF-32BE��������ʽ�Ѿ���ʼ��" << endl;
		return -2;
	}
	if ((m_gb18030Patterns.size() != 0) && (encode & en_gb18030) != 0) {
		cout << "GB18030��������ʽ�Ѿ���ʼ��" << endl;
		return -2;
	}

	fp = fopen(pszFilePath, "rb");
	if (!fp) {
		cout << "Error:open pattern file error" << endl;
		return -1;
	}

	while (fgets(str_line, sizeof(str_line), fp)) {
		lineNo++;

		strEnd = &str_line[strlen(str_line) - 1];
		if (str_line[0] == '#') {
			continue;
		}

		if (lineNo == 1) {
			if ((unsigned int) str_line[0] == 0xFFFFFFEF
					&& (unsigned int) str_line[1] == 0xFFFFFFBB
					&& (unsigned int) str_line[2] == 0xFFFFFFBF) {
				str_line[0] = ' ';
				str_line[1] = ' ';
				str_line[2] = ' ';
			}
		}

		if ((*strEnd != '\n')
				&& (strlen(str_line) == MAX_PATTERNS_FILE_LINE_LENG - 1)) {
			fprintf(stderr, "Error: strategy is too long in line %d : %s\n",
					lineNo, str_line);
			return -3;
		}

		if (*strEnd == '\n') {
			*strEnd = '\0';
		}

		if (strEnd[-1] == '\r') {
			strEnd[-1] = '\0';
			strEnd--;
		}

		dealNow = str_line;
		while ((*dealNow == ' ') || (*dealNow == '\t')) {
			dealNow++;
		}

		if (strlen(dealNow) == 0) {
			continue;
		}

		int pid = 0;

		if (1 != sscanf(str_line, "%d", &(pid))) {
			fprintf(stderr, "Error: have no pattern id in line %d : %s\n",
					lineNo, str_line);
			return -3;
		}

		while (*dealNow != '\t' && dealNow != strEnd) {
			dealNow++;
		}

		if (dealNow == strEnd) {
			fprintf(stderr, "Error: format error in line %d : %s\n", lineNo,
					str_line);
			return -3;
		}

		ptemp = ++dealNow;
		while ((*ptemp != '\t') && (ptemp != strEnd)) {
			ptemp++;
		}

		if (ptemp == strEnd) {
			fprintf(stderr, "Error: format error in line %d : %s\n", lineNo,
					str_line);
			return -3;
		}

		*ptemp = '\0';
		char* pName = strdup(dealNow);
		char* pContent = strdup(ptemp + 1);
		int nContentLen = strlen(ptemp + 1);
		bool bl = false;

		if ((encode & en_utf_8) != 0) {
			C_PatternUnit_UTF8* punit_utf8 = new C_PatternUnit_UTF8();
			punit_utf8->m_nPid = pid;
			punit_utf8->m_pName = strdup(pName);
			punit_utf8->m_pContent = strdup(pContent);
			punit_utf8->m_nContentLen = nContentLen;

			if (punit_utf8->PcreCompile() != 0) {
				fprintf(stderr, "Error: format error in line %d : %s\n", lineNo,
						str_line);
				delete punit_utf8;
			} else {
				m_utf8Patterns.push_back(punit_utf8);
			}
		}

		if ((encode & en_utf_16) != 0) {
			C_PatternUnit_UTF16* punit_utf16 = new C_PatternUnit_UTF16();
			punit_utf16->m_nPid = pid;
			punit_utf16->m_pName = strdup(pName);

			char* pin_utf16 = pContent;
			size_t inLen_utf16 = nContentLen;
			punit_utf16->m_pContent = (char*) malloc(
					sizeof(char) * 2 * MAX_PATTERNS_FILE_LINE_LENG);
			size_t outLen_utf16 = 2 * MAX_PATTERNS_FILE_LINE_LENG;
			memset(punit_utf16->m_pContent, 0, 2 * MAX_PATTERNS_FILE_LINE_LENG);
			bl = ChangeTextEncode(en_utf_8, en_utf_16, pin_utf16,
					(size_t*) &inLen_utf16, punit_utf16->m_pContent,
					(size_t*) &outLen_utf16);

			if (false == bl) {
				delete punit_utf16;
			} else {
				punit_utf16->m_nContentLen = 2 * MAX_PATTERNS_FILE_LINE_LENG
						- outLen_utf16;
				if (punit_utf16->PcreCompile() != 0) {
					delete punit_utf16;
				} else {
					m_utf16Patterns.push_back(punit_utf16);
				}
			}
		}

		if ((encode & en_utf_16le) != 0) {
			C_PatternUnit_UTF16* punit_utf16le = new C_PatternUnit_UTF16();
			punit_utf16le->m_nPid = pid;
			punit_utf16le->m_pName = strdup(pName);

			char* pin_utf16le = pContent;
			size_t inLen_utf16le = nContentLen;
			punit_utf16le->m_pContent = (char*) malloc(
					sizeof(char) * 2 * MAX_PATTERNS_FILE_LINE_LENG);

			size_t outLen_utf16le = 2 * MAX_PATTERNS_FILE_LINE_LENG;
			memset(punit_utf16le->m_pContent, 0,
					2 * MAX_PATTERNS_FILE_LINE_LENG);

			char* pout_utf16le = punit_utf16le->m_pContent;
			bl = ChangeTextEncode(en_utf_8, en_utf_16le, pin_utf16le,
					(size_t*) &inLen_utf16le, pout_utf16le,
					(size_t*) &outLen_utf16le);
			if (false == bl) {
				delete punit_utf16le;
			} else {
				punit_utf16le->m_nContentLen = 2 * MAX_PATTERNS_FILE_LINE_LENG
						- outLen_utf16le;
				if (punit_utf16le->PcreCompile() != 0) {
					delete punit_utf16le;
				} else {
					m_utf16lePatterns.push_back(punit_utf16le);
				}
			}
		}

		if ((encode & en_utf_16be) != 0) {
			C_PatternUnit_UTF16* punit_utf16be = new C_PatternUnit_UTF16();
			punit_utf16be->m_nPid = pid;
			punit_utf16be->m_pName = strdup(pName);

			char* pin_utf16be = pContent;
			size_t inLen_utf16be = nContentLen;
			punit_utf16be->m_pContent = (char*) malloc(
					sizeof(char) * 2 * MAX_PATTERNS_FILE_LINE_LENG);

			size_t outLen_utf16be = 2 * MAX_PATTERNS_FILE_LINE_LENG;
			memset(punit_utf16be->m_pContent, 0,
					2 * MAX_PATTERNS_FILE_LINE_LENG);

			char* pout_utf16be = punit_utf16be->m_pContent;
			bl = ChangeTextEncode(en_utf_8, en_utf_16be, pin_utf16be,
					(size_t*) &inLen_utf16be, pout_utf16be,
					(size_t*) &outLen_utf16be);
			if (false == bl) {
				delete punit_utf16be;
			} else {
				punit_utf16be->m_nContentLen = 2 * MAX_PATTERNS_FILE_LINE_LENG
						- outLen_utf16be;
				if (punit_utf16be->PcreCompile() != 0) {
					delete punit_utf16be;
				} else {
					m_utf16bePatterns.push_back(punit_utf16be);
				}
			}
		}

		if ((encode & en_utf_32) != 0) {
			C_PatternUnit_UTF32* punit_utf32 = new C_PatternUnit_UTF32();
			punit_utf32->m_nPid = pid;
			punit_utf32->m_pName = strdup(pName);

			char* pin_utf32 = pContent;
			size_t inLen_utf32 = nContentLen;
			punit_utf32->m_pContent = (char*) malloc(
					sizeof(char) * 4 * MAX_PATTERNS_FILE_LINE_LENG);

			size_t outLen_utf32 = 4 * MAX_PATTERNS_FILE_LINE_LENG;
			memset(punit_utf32->m_pContent, 0, 4 * MAX_PATTERNS_FILE_LINE_LENG);

			char* pout_utf32 = punit_utf32->m_pContent;
			bl = ChangeTextEncode(en_utf_8, en_utf_32, pin_utf32,
					(size_t*) &inLen_utf32, pout_utf32,
					(size_t*) &outLen_utf32);
			if (false == bl) {
				delete punit_utf32;
			} else {
				punit_utf32->m_nContentLen = 4 * MAX_PATTERNS_FILE_LINE_LENG
						- outLen_utf32;
				if (punit_utf32->PcreCompile() != 0) {
					delete punit_utf32;
				} else {
					m_utf32Patterns.push_back(punit_utf32);
				}
			}
		}

		if ((encode & en_utf_32le) != 0) {
			C_PatternUnit_UTF32* punit_utf32le = new C_PatternUnit_UTF32();
			punit_utf32le->m_nPid = pid;
			punit_utf32le->m_pName = strdup(pName);

			char* pin_utf32le = pContent;
			size_t inLen_utf32le = nContentLen;
			punit_utf32le->m_pContent = (char*) malloc(
					sizeof(char) * 4 * MAX_PATTERNS_FILE_LINE_LENG);

			size_t outLen_utf32le = 4 * MAX_PATTERNS_FILE_LINE_LENG;
			memset(punit_utf32le->m_pContent, 0, 4 * MAX_PATTERNS_FILE_LINE_LENG);

			char* pout_utf32le = punit_utf32le->m_pContent;
			bl = ChangeTextEncode(en_utf_8, en_utf_32le, pin_utf32le,
					(size_t*) &inLen_utf32le, pout_utf32le,
					(size_t*) &outLen_utf32le);
			if (false == bl) {
				delete punit_utf32le;
			} else {
				punit_utf32le->m_nContentLen = 4 * MAX_PATTERNS_FILE_LINE_LENG
						- outLen_utf32le;
				if (punit_utf32le->PcreCompile() != 0) {
					delete punit_utf32le;
				} else {
					m_utf32lePatterns.push_back(punit_utf32le);
				}
			}
		}

		if ((encode & en_utf_32be) != 0) {
			C_PatternUnit_UTF32* punit_utf32be = new C_PatternUnit_UTF32();
			punit_utf32be->m_nPid = pid;
			punit_utf32be->m_pName = strdup(pName);

			char* pin_utf32be = pContent;
			size_t inLen_utf32be = nContentLen;
			punit_utf32be->m_pContent = (char*) malloc(
					sizeof(char) * 4 * MAX_PATTERNS_FILE_LINE_LENG);

			size_t outLen_utf32be = 4 * MAX_PATTERNS_FILE_LINE_LENG;
			memset(punit_utf32be->m_pContent, 0,
					4 * MAX_PATTERNS_FILE_LINE_LENG);

			char* pout_utf32be = punit_utf32be->m_pContent;
			bl = ChangeTextEncode(en_utf_8, en_utf_32be, pin_utf32be,
					(size_t*) &inLen_utf32be, pout_utf32be,
					(size_t*) &outLen_utf32be);
			if (false == bl) {
				delete punit_utf32be;
			} else {
				punit_utf32be->m_nContentLen = 4 * MAX_PATTERNS_FILE_LINE_LENG
						- outLen_utf32be;
				if (punit_utf32be->PcreCompile() != 0) {
					delete punit_utf32be;
				} else {
					m_utf32bePatterns.push_back(punit_utf32be);
				}
			}
		}

		if ((encode & en_gb18030) != 0) {
			C_PatternUnit_GB18030* punit_gb18030 = new C_PatternUnit_GB18030();
			punit_gb18030->m_nPid = pid;
			punit_gb18030->m_pName = strdup(pName);

			char* pin_gb18030 = pContent;
			size_t inLen_gb18030 = nContentLen;
			punit_gb18030->m_pContent = (char*)malloc(sizeof(char) * 2 * MAX_PATTERNS_FILE_LINE_LENG);
			size_t outLen_gb18030 = 2 * MAX_PATTERNS_FILE_LINE_LENG;
			memset(punit_gb18030->m_pContent, 0, 2 * MAX_PATTERNS_FILE_LINE_LENG);
			bl = ChangeTextEncode(en_utf_8, en_gb18030, pin_gb18030, (size_t*)&inLen_gb18030, punit_gb18030->m_pContent, (size_t*)&outLen_gb18030);
			if (false == bl) {
				delete punit_gb18030;
			} else {
				punit_gb18030->m_nContentLen = 2 * MAX_PATTERNS_FILE_LINE_LENG - outLen_gb18030;
				if (punit_gb18030->PcreCompile() != 0) {
					delete punit_gb18030;
				} else {
					m_gb18030Patterns.push_back(punit_gb18030);
				}
			}
		}

		if (NULL != pName) {
			free(pName);
			pName = NULL;
		}

		if (NULL != pContent) {
			free(pContent);
			pContent = NULL;
		}
	}

	return 0;
}

