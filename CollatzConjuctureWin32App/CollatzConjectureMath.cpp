// #include "stdafx.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
//#include <debugapi.h>     
               
#include "LargeIntegerCalculations.h"
#include "CollatzConjectureMath.h"
#include "TraceWrapper.h"

const std::string cCCMath::m_strSeqSep = ", ";
const std::string cCCMath::m_strSeqStart = "( ";
const std::string cCCMath::m_strSeqEnd = " )";

cCCMath::cCCMath()
{
	m_iOddCount = Integer(0);
	m_iEvenCount = Integer(0);

	m_u2lLargest = Integer(0);
	m_strSeqeunce = "";
	m_bCalcRun = false;
	m_bCalcCancel = false;
}

void cCCMath::GetSequence(std::string* pstrSequence)
{
	(pstrSequence)->append(m_strSeqeunce);
}

void cCCMath::GetSequence(std::ostringstream* pstrstmSequence)
{
	*pstrstmSequence << m_strSeqeunce;
}

// // calculate next Collatz conjecture value from previous odd value with update odd operation count and the largest sequence value
u2lint cCCMath::CalcOdd(u2lint u2lNum)
{
	// cout << num << " is odd, so multiply by 3 and add 1" << endl;
	u2lNum = 3 * u2lNum + 1;

	if (u2lNum > 1)
	{
		m_iOddCount+=1;
		UpdateLargest(u2lNum);
	}

	return u2lNum;
}

// calculate next Collatz conjecture value from previous even value with update odd operation count and the largest sequence value
u2lint cCCMath::CalcEven(u2lint u2lNum)
{
	// cout << num << " is even, so divide by 2" << endl;
	u2lNum /= 2;
	m_iEvenCount+=1;

	return u2lNum;
}

// LARGE INTEGER CALCULATION
bool cCCMath::CalcSequence(BigInt u2lInputNumber, bool bOutputAsString = false, ...)
{
	BigInt u2lSeq = u2lInputNumber;
	bool bRetVal = false;
	std::string strSeqVal = "";

	if (u2lInputNumber > 1)
	{
		bRetVal = true;

		ResetStats(); 
		CleanSquenceOutput();

		// format begining of seuence string and store init largest
		if (bOutputAsString)
		{
			m_strSeqeunce += m_strSeqStart;
			Sprint(&strSeqVal, u2lInputNumber);

			m_strSeqeunce.append(strSeqVal);
			m_strSeqeunce += m_strSeqSep;
			m_u2lLargest = u2lInputNumber;
		}

		m_bCalcRun = true;
		m_bCalcCancel = false;
		TRACE("cCCMath::CalcSequence() calculation loop enter\n");

		do{
			// calculate next sequence value 
			u2lSeq = (u2lSeq % 2 == 0) ? CalcEven(u2lSeq) : CalcOdd(u2lSeq);

			// add it to string stream with separator
			if (bOutputAsString)
			{
				strSeqVal.clear();
				Sprint(&strSeqVal, u2lSeq); 
				m_strSeqeunce.append(strSeqVal);

				// print separator
				m_strSeqeunce.append((u2lSeq > 1) ? m_strSeqSep : m_strSeqEnd);

				// threading sleep 1ms
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		} while (u2lSeq > 1 && m_bCalcCancel == false);

		TRACE("cCCMath::CalcSequence() calculation loop finish\n");
		if (m_bCalcCancel)
		{
			TRACE("cCCMath::CalcSequence() calculation loop canceled\n");
			m_bCalcCancel = false;
			bRetVal = false;
		}
		m_bCalcRun = false;
	}

	return bRetVal;
}



