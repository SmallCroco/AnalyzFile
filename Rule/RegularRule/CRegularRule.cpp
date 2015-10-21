/*
 * CRegularRule.cpp
 *
 *  Created on: 2015��9��24��
 *      Author: SmallCroco
 */

#include "CRegularRule.h"
#include "CRegularResult.h"
#include "FileStruct.h"
#include <string.h>
#include <stdio.h>
#include <iostream>


#define MAX_PATTERNS_FILE_LINE_LENG 2500

using namespace std;

/*
 * @Function Name	: C_RegularRule
 * @Description		: 构造函数
 */
C_RegularRule::C_RegularRule() {

	this->m_gb18030Patterns.clear();

	this->m_utf8Patterns.clear();

	this->m_utf16Patterns.clear();

	this->m_utf16lePatterns.clear();

	this->m_utf16bePatterns.clear();

	this->m_utf32Patterns.clear();

	this->m_utf32lePatterns.clear();

	this->m_utf32bePatterns.clear();

}

C_RegularRule::C_RegularRule(C_RegularRule& rule) {
	for (vector<C_PatternUnit_UTF8*>::iterator li = rule.m_utf8Patterns.begin();
			li != rule.m_utf8Patterns.end(); ++li) {
		C_PatternUnit_UTF8* unit = new C_PatternUnit_UTF8(**li);
		this->m_utf8Patterns.push_back(unit);
	}

	for (vector<C_PatternUnit_UTF16*>::iterator li = rule.m_utf16Patterns.begin();
			li != rule.m_utf16Patterns.end(); ++li) {
		C_PatternUnit_UTF16* unit = new C_PatternUnit_UTF16(**li);
		this->m_utf16Patterns.push_back(unit);
	}
	for (vector<C_PatternUnit_UTF16*>::iterator li = rule.m_utf16lePatterns.begin();
			li != rule.m_utf16lePatterns.end(); ++li) {
		C_PatternUnit_UTF16* unit = new C_PatternUnit_UTF16(**li);
		this->m_utf16lePatterns.push_back(unit);
	}
	for (vector<C_PatternUnit_UTF16*>::iterator li = rule.m_utf16bePatterns.begin();
			li != rule.m_utf16bePatterns.end(); ++li) {
		C_PatternUnit_UTF16* unit = new C_PatternUnit_UTF16(**li);
		this->m_utf16bePatterns.push_back(unit);
	}
	for (vector<C_PatternUnit_UTF32*>::iterator li = rule.m_utf32Patterns.begin();
			li != rule.m_utf32Patterns.end(); ++li) {
		C_PatternUnit_UTF32* unit = new C_PatternUnit_UTF32(**li);
		this->m_utf32Patterns.push_back(unit);
	}
	for (vector<C_PatternUnit_UTF32*>::iterator li = rule.m_utf32lePatterns.begin();
			li != rule.m_utf32lePatterns.end(); ++li) {
		C_PatternUnit_UTF32* unit = new C_PatternUnit_UTF32(**li);
		this->m_utf32lePatterns.push_back(unit);
	}
	for (vector<C_PatternUnit_UTF32*>::iterator li = rule.m_utf32Patterns.begin();
			li != rule.m_utf32Patterns.end(); ++li) {
		C_PatternUnit_UTF32* unit = new C_PatternUnit_UTF32(**li);
		this->m_utf32bePatterns.push_back(unit);
	}
	for (vector<C_PatternUnit_GB18030*>::iterator li = rule.m_gb18030Patterns.begin();
			li != rule.m_gb18030Patterns.end(); ++li) {
		C_PatternUnit_GB18030* unit = new C_PatternUnit_GB18030(**li);
		this->m_gb18030Patterns.push_back(unit);
	}
}
/*
 * @Function Name	: ~C_RegularRule
 * @Description		: 析构函数
 * @Example			:
 */
C_RegularRule::~C_RegularRule() {
	for (vector<C_PatternUnit_UTF8*>::iterator li = m_utf8Patterns.begin();
			li != m_utf8Patterns.end(); ++li) {
		delete *li;
	}

	for (vector<C_PatternUnit_UTF16*>::iterator li = m_utf16Patterns.begin();
			li != m_utf16Patterns.end(); ++li) {
		delete *li;
	}

	for (vector<C_PatternUnit_UTF16*>::iterator li = m_utf16lePatterns.begin();
			li != m_utf16lePatterns.end(); ++li) {
		delete *li;
	}

	for (vector<C_PatternUnit_UTF16*>::iterator li = m_utf16bePatterns.begin();
			li != m_utf16bePatterns.end(); ++li) {
		delete *li;
	}

	for (vector<C_PatternUnit_UTF32*>::iterator li = m_utf32Patterns.begin();
			li != m_utf32Patterns.end(); ++li) {
		delete *li;
	}

	for (vector<C_PatternUnit_UTF32*>::iterator li = m_utf32lePatterns.begin();
			li != m_utf32lePatterns.end(); ++li) {
		delete *li;
	}

	for (vector<C_PatternUnit_UTF32*>::iterator li = m_utf32bePatterns.begin();
			li != m_utf32bePatterns.end(); ++li) {
		delete *li;
	}

	for (vector<C_PatternUnit_GB18030*>::iterator li = m_gb18030Patterns.begin();
			li != m_gb18030Patterns.end(); ++li) {
		delete *li;
	}
}

/*
 * @Function Name	: InitRules
 * @Parameter [in] const char* : pszFilePath --- 规则文件路径
 * @Parameter [in] int : encode --- 文件编码
 * @Description		: 初始化文件匹配规则
 * @Return Value	:
 * 		成功返回0
 * 		失败返回负整数
 * @Example			:
 */
int C_RegularRule::InitRules(const char* pszFilePath, int encode) {
	FILE* fp;

	int lineNo = 0;
	char *dealNow, *strEnd, *ptemp;
	char str_line[MAX_PATTERNS_FILE_LINE_LENG];
	if ((m_utf8Patterns.size() != 0) && (encode & en_utf_8) != 0) {
		cout << "UTF-8正则表达式已经初始化" << endl;
		return -2;
	}
	if ((m_utf16Patterns.size() != 0) && (encode & en_utf_16) != 0) {
		cout << "UTF-16正则表达式已经初始化" << endl;
		return -2;
	}
	if ((m_utf16lePatterns.size() != 0) && (encode & en_utf_16le) != 0) {
		cout << "UTF-16LE小端正则表达式已经初始化" << endl;
		return -2;
	}
	if ((m_utf16bePatterns.size() != 0) && (encode & en_utf_16be) != 0) {
		cout << "UTF-16BE大端正则表达式已经初始化" << endl;
		return -2;
	}
	if ((m_utf32Patterns.size() != 0) && (encode & en_utf_32) != 0) {
		cout << "UTF-32正则表达式已经初始化" << endl;
		return -2;
	}
	if ((m_utf32lePatterns.size() != 0) && (encode & en_utf_32le) != 0) {
		cout << "UTF-32LE小端正则表达式已经初始化" << endl;
		return -2;
	}
	if ((m_utf32bePatterns.size() != 0) && (encode & en_utf_32be) != 0) {
		cout << "UTF-32BE大端正则表达式已经初始化" << endl;
		return -2;
	}
	if ((m_gb18030Patterns.size() != 0) && (encode & en_gb18030) != 0) {
		cout << "GB18030正则表达式已经初始化" << endl;
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
			bl = ChangeTextEncode(en_utf_8, en_utf_16le, pin_utf16le,	(size_t*) &inLen_utf16le, pout_utf16le, (size_t*)&outLen_utf16le);
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

C_BaseRule* C_RegularRule::CreateObj() {

	return new C_RegularRule(*this);
}

void C_RegularRule::asciiMatch(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_GB18030*>::iterator li =
			m_gb18030Patterns.begin(); li != m_gb18030Patterns.end();
			++li) {

		for (int offset = 0; offset < bufLen;) {
			rc = pcre_exec((pcre *) (*li)->getPcre(),
					(const pcre_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR) pszFileText, bufLen, offset,
					PCRE_NOTEMPTY, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0];
			amatch.matchLen = ovector[1] - ovector[0];
			int flag = 0;
			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];

		}
	}

}


void C_RegularRule::iso8599Match(const char* pszFileText, int bufLen,  C_RegularResult* result) {

}

void C_RegularRule::utf7Match(const char* pszFileText, int bufLen, C_RegularResult* result) {

}

void C_RegularRule::utf8Match(const char* pszFileText, int bufLen, C_RegularResult* result) {

}

void C_RegularRule::utf16Match(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_UTF16*>::iterator li = m_utf16Patterns.begin();
			li != m_utf16Patterns.end(); ++li) {

		for (int offset = 0; offset < bufLen/2;) {
			rc = pcre16_exec((pcre16 *) (*li)->getPcre(),
					(const pcre16_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR16) pszFileText, bufLen/2, offset,
					PCRE_NOTEMPTY | PCRE_NO_UTF16_CHECK, ovector, 12);
			if (rc < 0) {
				break;
			}


			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0] * 2;
			amatch.matchLen = (ovector[1] - ovector[0])*2;
			int flag = 0;
			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}
			offset = ovector[1];
		}
	}
}

void C_RegularRule::utf16leMatch(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_UTF16*>::iterator li =
			m_utf16lePatterns.begin(); li != m_utf16lePatterns.end();
			++li) {

		for (int offset = 0; offset < bufLen / 2;) {
			rc = pcre16_exec((const pcre16*) (*li)->getPcre(),
					(const pcre16_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR16) pszFileText, (bufLen/2), offset,
					PCRE_NOTEMPTY | PCRE_NO_UTF16_CHECK, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0] * 2;
			amatch.matchLen = (ovector[1] - ovector[0]) * 2;
			int flag = 0;
			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}
			offset = ovector[1];

		}
	}
}

void C_RegularRule::utf16beMatch(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_UTF16*>::iterator li =
			m_utf16bePatterns.begin(); li != m_utf16bePatterns.end();
			++li) {

		for (int offset = 0; offset < bufLen/2;) {
			rc = pcre16_exec((pcre16 *) (*li)->getPcre(),
					(const pcre16_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR16) pszFileText, bufLen/2, offset,
					PCRE_NOTEMPTY | PCRE_NO_UTF16_CHECK, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0] * 2;
			amatch.matchLen = (ovector[1] - ovector[0]) * 2;

			int flag = 0;
			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];
		}
	}
}

void C_RegularRule::utf32Match(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_UTF32*>::iterator li = m_utf32Patterns.begin();
			li != m_utf32Patterns.end(); ++li) {

		for (int offset = 0; offset < bufLen/4;) {
			rc = pcre32_exec((pcre32 *) (*li)->getPcre(),
					(const pcre32_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR32) pszFileText, bufLen/4, offset,
					PCRE_NOTEMPTY | PCRE_NO_UTF32_CHECK, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0] * 4;
			amatch.matchLen = (ovector[1] - ovector[0]) * 4;
			int flag = 0;

			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];
		}
	}
}

void C_RegularRule::utf32leMatch(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_UTF32*>::iterator li =
			m_utf32lePatterns.begin(); li != m_utf32lePatterns.end();
			++li) {

		for (int offset = 0; offset < bufLen/4;) {
			rc = pcre32_exec((pcre32 *) (*li)->getPcre(),
					(const pcre32_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR32) pszFileText, bufLen/4, offset,
					PCRE_NOTEMPTY | PCRE_NO_UTF32_CHECK, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0] * 4;
			amatch.matchLen = (ovector[1] - ovector[0]) * 4;
			int flag = 0;
			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];

		}
	}
}

void C_RegularRule::utf32beMatch(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_UTF32*>::iterator li =
			m_utf32bePatterns.begin(); li != m_utf32bePatterns.end();
			++li) {

		for (int offset = 0; offset < bufLen/4;) {
			rc = pcre32_exec((pcre32 *) (*li)->getPcre(),
					(const pcre32_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR32) pszFileText, bufLen/4, offset,
					PCRE_NOTEMPTY | PCRE_NO_UTF32_CHECK, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0] * 4;
			amatch.matchLen = (ovector[1] - ovector[0]) * 4;
			int flag = 0;
			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];
		}
	}
}

void C_RegularRule::gbkMatch(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_GB18030*>::iterator li =	m_gb18030Patterns.begin(); li != m_gb18030Patterns.end();
			++li) {

		for (int offset = 0; offset < bufLen;) {
			rc = pcre_exec((pcre *) (*li)->getPcre(),
					(const pcre_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR) pszFileText, bufLen, offset,
					PCRE_NOTEMPTY, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0];
			amatch.matchLen = ovector[1] - ovector[0];
			int flag = 0;
			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];

		}
	}

}

void C_RegularRule::gb2312Match(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_GB18030*>::iterator li =
			m_gb18030Patterns.begin(); li != m_gb18030Patterns.end();
			++li) {

		for (int offset = 0; offset < bufLen;) {
			rc = pcre_exec((pcre *) (*li)->getPcre(),
					(const pcre_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR) pszFileText, bufLen, offset,
					PCRE_NOTEMPTY, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0];
			amatch.matchLen = ovector[1] - ovector[0];
			int flag = 0;
			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];

		}
	}

}

void C_RegularRule::gb18030Match(const char* pszFileText, int bufLen, C_RegularResult* res) {

	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_GB18030*>::iterator li =
			m_gb18030Patterns.begin(); li != m_gb18030Patterns.end();
			++li) {

		for (int offset = 0; offset < bufLen;) {
			rc = pcre_exec((pcre *) (*li)->getPcre(),
					(const pcre_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR) pszFileText, bufLen, offset,
					PCRE_NOTEMPTY, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0];
			amatch.matchLen = ovector[1] - ovector[0];
			int flag = 0;

			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];
		}
	}
}

void C_RegularRule::big5Match(const char* pszFileText, int bufLen, C_RegularResult* res) {


	int rc = 0;
	int ovector[12];

	for (vector<C_PatternUnit_GB18030*>::iterator li =
			m_gb18030Patterns.begin(); li != m_gb18030Patterns.end();
			++li) {

		for (int offset = 0; offset < bufLen;) {
			rc = pcre_exec((pcre *) (*li)->getPcre(),
					(const pcre_extra *) (*li)->getPcreExtra(),
					(PCRE_SPTR) pszFileText, bufLen, offset,
					PCRE_NOTEMPTY, ovector, 12);

			if (rc < 0) {
				break;
			}

			SMatchUnit amatch;
			amatch.ID = (*li)->m_nPid;
			amatch.matchPosition = pszFileText + ovector[0];
			amatch.matchLen = ovector[1] - ovector[0];
			int flag = 0;

			// 遍历种类编号,查找是否已经存在种类编号
			for (unsigned int i = 0; i < res->results.size(); i++) {
				if (amatch.ID == res->results[i].ID) {
					res->m_totalNum += 1;
					res->results[i].num += 1;
					res->results[i].unit.push_back(amatch);

					flag = 1;

					break;
				}
			}

			// 如果不存在
			if (flag == 0) {
				res->m_unitNum += 1;
				res->m_totalNum += 1;

				SMatchUnitNum unitNum;
				unitNum.ID = amatch.ID;
				unitNum.num = 1;
				unitNum.unit.push_back(amatch);

				res->results.push_back(unitNum);
			}

			offset = ovector[1];
		}
	}
}
