#ifndef _COLLATZCONJECTUREMFCWRAPPER_H_
#define _COLLATZCONJECTUREMFCWRAPPER_H_

#include <sstream>

// Collatz Conjecture Mfc Wrapper Interface

// produce Collatz Conjecture sequence
bool CCW_CalcSequence(std::string* pstrInitValue);


// get sequence result
void CCW_GetSequence(std::string* pstrSequence);


// get calculation statistics
void CCW_GetOddCount(std::string* pstrOddCount);
void CCW_GetEvenCount(std::string* pstrEvenCount);
void CCW_GetLargest(std::string* pstrLargest);
void CCW_CancelCalculation();
bool CCW_IsCalcRun();
bool CCW_IsCalcCancel();

#endif // _COLLATZCONJECTUREMFCWRAPPER_H_