/*
 * CResult.h
 *
 *  Created on: 2015年9月28日
 *      Author: smallcroco
 */

#ifndef RESULT_CRESULT_H_
#define RESULT_CRESULT_H_

#include <vector>
#include "CBaseResult.h"

using std::vector;

/*
 * 每一种匹配的结果
 */
struct SMatchUnit {
	int ID;		// 种类编号
	int matchLen;	// 内容长度
	const char* matchPosition;	// 内容
};

/*
 * 每一种匹配的数量
 */
struct SMatchUnitNum {
	int ID;	 // 种类编号
	int num;	// 种类数量
	vector<SMatchUnit> unit;	// 匹配的每一个结果
};


class C_RegularResult: public C_BaseResult {
public:
	C_RegularResult();
	~C_RegularResult();

public:
	int m_unitNum;
	int m_totalNum;
	vector<SMatchUnitNum> results;
};

#endif /* RESULT_CRESULT_H_ */
