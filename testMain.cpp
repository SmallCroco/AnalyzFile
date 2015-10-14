/*
 * testMain.cpp
 *
 *  Created on: 2015年9月28日
 *      Author: smallcroco
 */

#include <stdio.h>
#include "CFileAnalyze.h"


int main() {

	//　初始化文件
	C_FileAnalyze* an = new C_FileAnalyze("./testFile/godat-master.zip");

	// 初始化匹配规则
	C_BaseRule* rule = new C_RegularRule();
	rule->InitRules("./PatternUnit/patterns.txt", en_utf_16 | en_utf_16le | en_utf_16be | en_utf_8);
	an->SetRule(rule);


	// 设置结果
	C_BaseResult* result = new C_RegularResult();
	an->SetResult(result);

	an->Analyze();

	delete an;

	delete rule;

	return 0;
}

