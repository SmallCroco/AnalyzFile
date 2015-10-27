/*
 * testMain.cpp
 *
 *  Created on: 2015年9月28日
 *      Author: smallcroco
 */

#include <stdio.h>
#include "CFileAnalyze.h"
#include "CBaseResult.h"
#include "CRegularResult.h"
#include "CBaseRule.h"
#include "CRegularRule.h"


// 根据文件路径来分析文件
int main11() {

	//　初始化文件
	C_FileAnalyze* an = new C_FileAnalyze("./testFile/192.168.10.180_21878_1439434310-04PTDW.docx");

	// 初始化匹配规则
	C_BaseRule* rule = new C_RegularRule();
	int init = rule->InitRules("./PatternUnit/patterns.txt", en_utf_16 | en_utf_16le | en_utf_16be | en_utf_8);
	if (init == -3) {
		printf("正则表达式文件格式错误\n");
		return 0;
	}
	if (init == -2) {
		printf("正则表达式已经初始化\n");
		return 0;
	}
	if (init == -1) {
		printf("文件不存在\n");
		return 0;
	}

	init = rule->InitRules("./PatternUnit/patterns_gb18030.txt", en_gb18030);
	if (init == -3) {
		printf("正则表达式文件格式错误\n");
		return 0;
	}
	if (init == -2) {
		printf("正则表达式已经初始化\n");
		return 0;
	}
	if (init == -1) {
		printf("文件不存在\n");
		return 0;
	}
	an->SetRule(rule);
	delete rule;


	// 设置结果
	C_RegularResult* res = new C_RegularResult();
	an->SetResult(res);

	an->Analyze();

	printf("There are %d unit num\n", res->m_unitNum);
	printf("There are %d resultes\n", res->m_totalNum);
	printf("\n\n");

	for (vector<SMatchUnitNum>::iterator li = res->results.begin(); li != res->results.end(); li++) {
		printf("Unit Num %d There are %d resultes\n", li->ID, li->num);
		for (vector<SMatchUnit>::iterator unit = li->unit.begin(); unit != li->unit.end(); unit++) {
			printf("%.*s\n", unit->matchLen, unit->matchPosition);
		}
	}

	delete an;
	delete res;

	return 0;
}


//　根据文件内容来分析文件
int main() {

	FILE *fp = fopen("./testFile/192.168.10.180_21878_1439434310-04PTDW.docx", "rb");
	if (NULL == fp) {
		return false;
	}

	// 获取文件长度
	fseek(fp, 0L, SEEK_END);
	long m_lFileLength = ftell(fp);
	if (m_lFileLength == -1L) {
		fclose(fp);
		return false;
	}
	rewind(fp);

	// 分配内存
	char* m_pFileData = (char*) malloc(sizeof(char)*m_lFileLength);
	if (m_pFileData == NULL) {
		fclose(fp);
		return false;
	}

	// 读取文件
	if (m_lFileLength != (long)fread(m_pFileData, sizeof(char), m_lFileLength, fp)) {
		fclose(fp);
		free(m_pFileData);
		return false;
	}

	fclose(fp);

	//　初始化文件
	C_FileAnalyze* an = new C_FileAnalyze(m_pFileData, m_lFileLength);
	free(m_pFileData);

	// 初始化匹配规则
	C_BaseRule* rule = new C_RegularRule();
	int init = rule->InitRules("./PatternUnit/patterns.txt", en_utf_16 | en_utf_16le | en_utf_16be | en_utf_8);
	if (init == -3) {
		printf("正则表达式文件格式错误\n");
		return 0;
	}
	if (init == -2) {
		printf("正则表达式已经初始化\n");
		return 0;
	}
	if (init == -1) {
		printf("文件不存在\n");
		return 0;
	}

	init = rule->InitRules("./PatternUnit/patterns_gb18030.txt", en_gb18030);
	if (init == -3) {
		printf("正则表达式文件格式错误\n");
		return 0;
	}
	if (init == -2) {
		printf("正则表达式已经初始化\n");
		return 0;
	}
	if (init == -1) {
		printf("文件不存在\n");
		return 0;
	}
	an->SetRule(rule);
	delete rule;

	// 设置结果
	C_RegularResult* res = new C_RegularResult();
	an->SetResult(res);

	an->Analyze();

	printf("There are %d unit num\n", res->m_unitNum);
	printf("There are %d resultes\n", res->m_totalNum);
	printf("\n\n");

	for (vector<SMatchUnitNum>::iterator li = res->results.begin(); li != res->results.end(); li++) {
		printf("Unit Num %d There are %d resultes\n", li->ID, li->num);
		for (vector<SMatchUnit>::iterator unit = li->unit.begin(); unit != li->unit.end(); unit++) {
			printf("%.*s\n", unit->matchLen, unit->matchPosition);
		}
	}

	delete an;
	delete res;

	return 0;
}

