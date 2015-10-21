/*
 * CResult.cpp
 *
 *  Created on: 2015年9月28日
 *      Author: smallcroco
 */

#include "CRegularResult.h"

C_RegularResult::C_RegularResult() {
	// TODO Auto-generated constructor stub
	this->m_totalNum = 0;
	this->m_unitNum = 0;
	this->results.clear();
}

C_RegularResult::~C_RegularResult() {
	// TODO Auto-generated destructor stub
	for (vector<SMatchUnitNum>::iterator li = results.begin(); li != results.end(); ) {
			li->unit.clear();
			li = results.erase(li);
		}
}

