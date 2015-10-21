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

int main() {

	//　初始化文件
	C_FileAnalyze* an = new C_FileAnalyze("./testFile/5");

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

