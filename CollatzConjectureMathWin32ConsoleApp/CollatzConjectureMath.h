// For multithread/multiprocess usage add synchronization using Lock/Unlock

// typedef unsigned long long int u2lint;
#include <string>
#include <iostream>
#include <sstream>

#include "LargeIntegerCalculations.h"

typedef BigInt u2lint;

class cCCMath
{
	BigInt m_iOddCount;
	BigInt m_iEvenCount;
	BigInt m_u2lLargest;
	std::string m_strSeqeunce;

	static const std::string m_strSeqSep;
	static const std::string m_strSeqStart;
	static const std::string m_strSeqEnd;

public:
	inline BigInt GetOddCount() { return m_iOddCount; }
	inline BigInt GetEvenCount() { return m_iEvenCount; }
	inline BigInt GetLargest() { return m_u2lLargest; }


	cCCMath();

	void cCCMath::UpdateLargest(BigInt u2lNum)
	{
		if (u2lNum > m_u2lLargest)
		{
			m_u2lLargest = u2lNum;
		}
	}

	//inline void 
	inline int cCCMath::Reset(){ m_iOddCount = m_iEvenCount = Integer(0); m_u2lLargest = Integer(0); }

	u2lint cCCMath::CalcOdd(u2lint u2lNum);
	u2lint cCCMath::CalcEven(u2lint u2lNum);

	//bool CalcSequence(u2lint u2lInputNumber, bool bOutputAsString, ...);
	void cCCMath::GetSequence(std::ostringstream* pstrstmSequence);
	void cCCMath::GetSequence(std::string* pstrSequence);
	bool cCCMath::CalcSequence(BigInt u2lInputNumber, bool bOutputAsString, ...);
};

