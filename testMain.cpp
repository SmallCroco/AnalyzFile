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
	C_FileAnalyze* an = new C_FileAnalyze("");

	// 初始化匹配规则
	C_BaseRule* rule = new C_RegularRule();
	rule->InitRules("", 0);

	an->Analyze(rule);

	delete an;

	delete rule;

	return 0;
}

