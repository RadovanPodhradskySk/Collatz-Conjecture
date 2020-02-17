#include "CollatzConjectureMath.h"
#include "LargeIntegerCalculations.h"

#include <conio.h>
#include <sstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////

int main()
{
	u2lint InputNumber, u2lSeq;
	cCCMath cMath;
	ostringstream strstmSeq;

	// int n;

	cout << "Enter an integer: ";
	// cin >> n;
	cin >> InputNumber;

	u2lSeq = InputNumber;

	// don't start cycle in case of 1 as input
	// if
	// (n % 2 == 0) ? cout << n << " is even." : cout << n << " is odd.";
	cout << "\n Collatz Conjecture is: ";
	cMath.CalcSequence(InputNumber, true);
	cMath.GetSequence(&strstmSeq);

	cout << strstmSeq.str();
	
	cout << "\nNumber of 3x+1 operations:\t" << cMath.GetOddCount();
	cout << "\nNumber of 2k operations:\t" << cMath.GetEvenCount();
	cout << "\nSquence the largest number:\t" << cMath.GetLargest();

	std::string sInitA = "999999";
	std::string sInitB = "111111";


	BigInt C;  // cin >> B;

	BigInt B = Integer("999999999999999999999999999999");
	BigInt A = Integer("111111111111111111111111111111");
	cout << "\nB is " << B;
	cout << "\nA is " << A;

	//LargeInt liValA(sInitA);
	//LargeInt liValB(sInitB);

	//LargeInt liResult;

	//liResult = liValA;

	//liResult += liValB;

 	//cout << "LargeInteger result is: " << liResult;
	C = B - A;
	cout << "Result B - A is: " << C;

	std::string sResult;
	Sprint(&sResult, C);
	cout << "Result B - A from string is: " << sResult;

	B = Integer("333333333333333333333333333333");
	C = 3 * B;
	cout << "\nB is " << B;
	cout << "Result 3*B is: " << C;
	cout << "Result B%2 is: " << B % 2 ;

	B = Integer("888888888888888888888888888888");
	C = B/2;
	cout << "\nB is " << B;
	cout << "Result B/2 is: " << C;
	cout << "Result B%2 is: " << B % 2;

	cout << "\nPress any key to exit";
	_getch();

	return 0;
}