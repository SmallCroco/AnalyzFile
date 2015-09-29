/*
 * testMain.cpp
 *
 *  Created on: 2015年9月28日
 *      Author: smallcroco
 */

#include <stdio.h>
#include "CFileAnalyze.h"



int main() {

	C_RegularRule* rule = new C_RegularRule();

	//　初始化文件
	C_FileAnalyze* an = new C_FileAnalyze("");

	// 设置匹配规则
	an->SetRule(rule);
	delete an;

	return 0;
}

