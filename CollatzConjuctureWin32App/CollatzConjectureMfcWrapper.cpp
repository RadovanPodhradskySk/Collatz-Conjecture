#include <stdlib.h>
#include <TCHAR.H>
#include "CollatzConjectureMfcWrapper.h"
#include "LargeIntegerCalculations.h"
#include "CollatzConjectureMath.h"


static cCCMath scMath;

bool CCW_CalcSequence(std::string* pstrInitValue)
{
	//_tcstoui64(pstrInitValue->c_str(), NULL, 10);
	BigInt biInitValue = Integer(pstrInitValue->c_str());
	
	return scMath.CalcSequence(biInitValue, true);
}

// get sequence result
void CCW_GetSequence(std::string* pstrSequence)
{
	scMath.GetSequence(pstrSequence);
}

// get calculation statistics
void CCW_GetOddCount(std::string* pstrOddCount)
{
	BigInt biValue = scMath.GetOddCount();
	Sprint(pstrOddCount, biValue);
}

void CCW_GetEvenCount(std::string* pstrEvenCount)
{
	BigInt biValue = scMath.GetEvenCount();
	Sprint(pstrEvenCount, biValue);
}

void CCW_GetLargest(std::string* pstrLargest)
{
	BigInt biValue = scMath.GetLargest();
	Sprint(pstrLargest, biValue);
}

void CCW_CancelCalculation()
{
	if (scMath.IsCalcRun()){ scMath.SetCalcCancel(); }
}

bool CCW_IsCalcRun()
{
	return scMath.IsCalcRun();
}

bool CCW_IsCalcCancel()
{
	return scMath.GetCalcCancel();
}