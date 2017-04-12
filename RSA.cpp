#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <tuple>
#include <bitset>
#include <ctime>

using namespace std;

//****************************string to number******************//
unsigned long long combine(string s)
{
	unsigned long long result = 0;
	for (int i = 0; i < s.length(); i++)
	{
		result = result * 10 + s[i] - '0';
	}
	return result;
}

class BigInt
{
	public:
		//**************************Constructors************************//
		BigInt()
		{
			long_bigInt.push_back(0);
			sign = 0;
		}

		BigInt(vector<unsigned long long> v)
		{
			long_bigInt = v;
			sign = 0;
		}

		BigInt(string s)
		{
			if (s[0] == '-')
			{
				sign = 1;
			}
			else
			{
				sign = 0;
			}

			unsigned long long element = 0;
			int count = 0;
			if (s.length() <= 9 && s[0] != '-')
			{
				element = combine(s);
				if (s[s.length() - 1] == '0')
				{
					element = element * 10;
				}
				long_bigInt.push_back(element);
			}

			else if(s.length() <= 9 && s[0] == '-')
			{
				element = combine(s.substr(1, s.length() - 1));
				if (s[s.length() - 1] == '0')
				{
					element = element * 10;
				}
				long_bigInt.push_back(element);
			}

			else if (s.length() > 9 && s[0] != '-')
			{
				for (int i = s.length() - 1; i >= 0; i--)
				{
					count++;
					if (count == 9)
					{
						element = combine(s.substr(i, 9));
						if (element < 100000000 && i != 0 && s[i] != '0')
						{
							element = element * 10;
							long_bigInt.push_back(element);
							count = 0;
							element = 0;
						}
						else
						{
							long_bigInt.push_back(element);
							count = 0;
							element = 0;
						}
					}
					else if (i == 0)
					{
						element = combine(s.substr(i, count));
						long_bigInt.push_back(element);
					}
				}
			}
			else
			{
				for (int i = s.length() - 1; i >= 1; i--)
				{
					count++;
					if (count == 9)
					{
						element = combine(s.substr(i, 9));
						if (element < 100000000 && i != 0 && s[i] != '0')
						{
							element = element * 10;
							long_bigInt.push_back(element);
							count = 0;
							element = 0;
						}
						else
						{
							long_bigInt.push_back(element);
							count = 0;
							element = 0;
						}
					}
					else if (i == 1)
					{
						element = combine(s.substr(i, count));
						long_bigInt.push_back(element);
					}
				}
			}
		}

		BigInt(int d)
		{
			long_bigInt.push_back(d);
			sign = 0;
		}

		BigInt(unsigned long long n)
		{
			long_bigInt.push_back(n);
			sign = 0;
		}
		//***************************Print Number***********************//
		void printBigInt()
		{
			string s = "";
			int x = 0;
			for (int i = long_bigInt.size() - 1; i >= 0 ;i--)
			{
				if (long_bigInt[i] >= 100000000 || (long_bigInt[i] < 100000000 && i == long_bigInt.size() - 1))
				{
					s+= to_string(long_bigInt[i]);
				}
				else if (long_bigInt[i] < 100000000 && i != long_bigInt.size() - 1)
				{
					int foo = 9 - to_string(long_bigInt[i]).length();
					s+= string(foo ,'0') + to_string(long_bigInt[i]);
				}
			}
			
			if (sign)
			{
				cout << '-' << s << endl;
			}
			else
			{
				cout << s << endl;
			}
		}
		//****************************Is it zero ? ***********************//
		bool isZero(BigInt a)
		{
			BigInt zero(vector<unsigned long long>(a.long_bigInt.size(), 0));
			if (isEqual(a, zero))
			{
				return true;
			}
			else return false;
		}
		//****************************Greater than**********************//
		bool isGreater(BigInt a, BigInt b)
		{
			vector<unsigned long long> temp1 = a.long_bigInt;
			vector<unsigned long long> temp2 = b.long_bigInt;
			if (temp1.size() > temp2.size())
			{
				return true;
			}
			else if (temp1.size() == temp2.size())
			{
				for (int i = temp1.size() - 1; i >= 0; i--)
				{
					if (temp1[i] > temp2[i])
					{
						return true;
						break;
					}
					else if (temp1[i] < temp2[i])
					{
						return false;
						break;
					}
				}
				return false;
			}
			else
			{
				return false;
			}
		}
		//*****************************is Equal*************************//
		bool isEqual(BigInt a, BigInt b)
		{
			vector<unsigned long long> temp1 = a.long_bigInt;
			vector<unsigned long long> temp2 = b.long_bigInt;
			if (temp1.size() > temp2.size())
			{
				return false;
			}
			else if (temp1.size() == temp2.size())
			{
				for (int i = 0; i < temp1.size(); i++)
				{
					if (temp1[i] > temp2[i])
					{
						return false;
					}

					else if (temp1[i] < temp2[i])
					{
						return false;
					}

					return true;
				}
			}
		else
		{
			return false;
		}
	}
		//****************************Addding two Big Integers**********//
		BigInt Add(BigInt a, BigInt b)
		{
			vector<unsigned long long> sum;
			unsigned long long r = 0;
			BigInt temp1(a.long_bigInt);
			BigInt temp2(b.long_bigInt);

			if (!a.sign && !b.sign)
			{
				if (isGreater(b, a))
				{
					return Add(b, a);
				}

				for (int i = 0; i < temp2.long_bigInt.size(); i ++)
				{
					unsigned long long x = temp1.long_bigInt[i] + temp2.long_bigInt[i] + r;
					sum.push_back(x % 1000000000);
					r = x / 1000000000;
					if ((temp1.long_bigInt.size() == temp2.long_bigInt.size()) && (i == temp2.long_bigInt.size() - 1))
					{
						sum.push_back(r);
					}
				}
				for (int i = temp2.long_bigInt.size(); i < temp1.long_bigInt.size(); i++)
				{
					int x = temp1.long_bigInt[i] + r;
					sum.push_back(x % 1000000000);
					r = x / 1000000000;
					if (i == temp1.long_bigInt.size() - 1)
					{
						sum.push_back(r);
					}
				}

				while (sum.back() == 0 && sum.size() > 1)
				{
					sum.pop_back();
				}
				BigInt c = BigInt(sum);
				c.sign = 0;
				return c;
			}

			else if (a.sign && b.sign )
			{
				temp1.sign = 0; temp2.sign = 0;
				BigInt Result = Add(temp1, temp2);
				Result.sign = 1;
				return Result;
			}

			else if (a.sign)
			{
				temp1.sign = 0;
				if (isGreater(temp2, temp1))
				{
					BigInt Result = Sub(temp2, temp1);
					Result.sign = 0;
					return Result;
				}
				else
				{
					BigInt Result = Sub(temp1, temp2);
					Result.sign = 1;
					return Result;
				}
			}

			else if (b.sign == 1)
			{
				temp2.sign == 0;
				if (isGreater(temp2, temp1))
				{
					BigInt Result = Sub(temp2, temp1);
					Result.sign = 1;
					return Result;
				}
				else
				{
					BigInt Result = Sub(temp1, temp2);
					Result.sign = 0;
					return Result;
				}
			}
		}
		//****************************Subtracting two Big Integers******//	
		BigInt Sub(BigInt a, BigInt b)
		{
			long long r = 0;
			vector<unsigned long long> result;
			BigInt temp1(a.long_bigInt);
			BigInt temp2(b.long_bigInt);

			if (!a.sign && !b.sign)
			{
				if (isGreater(b, a))
				{
					BigInt Result = Sub(b, a);
					Result.sign = 1;
					return Result;
				}

				for (int i = 0; i < temp2.long_bigInt.size(); i++)
				{
					temp1.long_bigInt[i] = temp1.long_bigInt[i] + r;
					if (temp1.long_bigInt[i] < temp2.long_bigInt[i])
					{
						result.push_back((temp1.long_bigInt[i] + 1000000000) - temp2.long_bigInt[i]);
						r = -1;
					}
					else
					{
						result.push_back(temp1.long_bigInt[i] - temp2.long_bigInt[i]);
						r = 0;
					}
				}

				for (int i = temp2.long_bigInt.size(); i < temp1.long_bigInt.size(); i++)
				{
					if (temp1.long_bigInt[i] == 0 && r == -1)
					{
						result.push_back(999999999);
					}
					else
					{
						result.push_back(temp1.long_bigInt[i] + r);
						r = 0;
					}
				}

				while (result.back() == 0 && result.size() > 1)
				{
					result.pop_back();
				}
				BigInt Result(result);
				Result.sign = 0;
				return Result;
			}

			else if (a.sign && b.sign )
			{
				temp1.sign = 0;
				temp2.sign = 0;
				if (isGreater(temp2, temp1))
				{
					BigInt Result = Sub(temp2, temp1);
					Result.sign = 0;
					return Result;
				}
				else
				{
					BigInt Result = Sub(temp1, temp2);
					Result.sign = 1;
					return Result;
				}
			}

			else if (a.sign)
			{
				temp1.sign = 0;
				BigInt Result = Add(temp1, b);
				Result.sign = 1;
				return Result;
			}

			else
			{
				temp2.sign = 0;
				BigInt Result = Add(a, temp2);
				Result.sign = 0;
				return Result;
			}

		}
		//****************************Multiplication**********//
		BigInt Mul(BigInt a, BigInt b)
		{
			BigInt temp1 = a;
			BigInt temp2 = b;

			if (isZero(a) || isZero(b))
			{
				BigInt result("0");
				return result;
			}
			else if (!a.sign && !b.sign)
			{
				unsigned long long element;
				unsigned long long carry = 0;
				BigInt Result, temp_result;
				if (b.long_bigInt.size() > a.long_bigInt.size())
				{
					return Mul(b, a);
				}
				vector<unsigned long long> temp;
				for (int i = 0; i < b.long_bigInt.size(); i++)
				{
					for (int j = 0; j < a.long_bigInt.size(); j++)
					{
						element = temp1.long_bigInt[j] * temp2.long_bigInt[i] + carry;
						carry = element / 1000000000;
						temp.push_back(element % 1000000000);
						if (j == a.long_bigInt.size() - 1 && carry != 0)
						{
							temp.push_back(carry);
							carry = 0;
						}
					}
					temp_result = BigInt (temp);
					temp_result.sign = 0;
					Result = Add(Result, temp_result);
					temp.clear();
					for (int k = 0; k <= i; k++)
					{
						temp.push_back(0);
					}
				}
				while (Result.long_bigInt.back() == 0 && Result.long_bigInt.size() > 1)
				{
					Result.long_bigInt.pop_back();
				}
				Result.sign = 0;
				return Result;
			}
		
			else if (temp1.sign && temp2.sign)
			{
				temp1.sign = 0;
				temp2.sign = 0;
				return Mul(temp1, temp2);
			}
		
			else if (temp1.sign)
			{
				temp1.sign = 0;
				BigInt result = Mul(temp1, b);
				result.sign = 1;
				return result;
			}
		
			else
			{
				temp2.sign = 0;
				BigInt result = Mul(a, temp2);
				result.sign = 1;
				return result;
			}
				
		}
		//****************************Divide by number******************//
		BigInt divNumber(BigInt a, unsigned long long n)
		{
			unsigned long long remainder = 0;
			for (int i = a.long_bigInt.size() - 1; i >= 0; i--)
			{
				unsigned long long element = a.long_bigInt[i] + remainder * 1000000000;
				a.long_bigInt[i] = element / n;
				remainder = element % n;
			}
			while (a.long_bigInt.back() == 0 && a.long_bigInt.size() > 1)
			{
				a.long_bigInt.pop_back();
			}
			return a;
		}
		//****************************Division of two Big Integers******//
		tuple <BigInt, BigInt> Div(BigInt dividend, BigInt divisor)
		{
				unsigned long long n = 1000000000 / (divisor.long_bigInt.back() + 1);
				BigInt temp1 = temp1.Mul(dividend, n);
				BigInt temp2 = temp2.Mul(divisor, n);
				BigInt quotient, remainder;
				quotient.sign = 0;
				remainder.sign = 0;
				unsigned long long foo1, foo2;
				quotient.long_bigInt.resize(temp1.long_bigInt.size());
				for (int i = temp1.long_bigInt.size() - 1; i >= 0; i--)
				{
					remainder = Mul(remainder, BigInt(1000000000));
					remainder = Add(remainder, temp1.long_bigInt[i]);
					if (remainder.long_bigInt.size() <= temp2.long_bigInt.size())
					{
						foo1 = 0;
					}
					else
					{
						foo1 = remainder.long_bigInt[temp2.long_bigInt.size()];
					}
					if (remainder.long_bigInt.size() <= temp2.long_bigInt.size() - 1 )
					{
						foo2 = 0;
					}
					else
					{
						foo2 = remainder.long_bigInt[temp2.long_bigInt.size() - 1];
					}
					unsigned long long foo3 = (foo1 * 1000000000 + foo2) / temp2.long_bigInt.back();
					remainder = Sub(remainder, Mul(temp2, BigInt(foo3)));
					while (remainder.sign == 1)
					{
						remainder = Add(remainder, temp2);
						foo3 --;
					}
					quotient.long_bigInt[i] = foo3;
				}
				while (quotient.long_bigInt.back() == 0 && quotient.long_bigInt.size() > 1)
				{
					quotient.long_bigInt.pop_back();
				}
				while (remainder.long_bigInt.back() == 0 && remainder.long_bigInt.size() > 1)
				{
					remainder.long_bigInt.back();
				}
				remainder = divNumber(remainder, n);
				return make_tuple(quotient, remainder);				
		}
		//****************************Multiplicative Inverse Mod********//
		BigInt inverse_mod(BigInt e, BigInt phi)
			{
				BigInt one("1");
				BigInt zero("0");
				BigInt A[3];
				BigInt B[3];
				BigInt temp[3];
				BigInt Q, quotient, remainder;
				A[0] = one;
				A[1] = zero;
				A[2] = phi;
				B[0] = zero;
				B[1] = one;
				B[2] = e;
				while (!isEqual(B[2], one))
				{
					tie(quotient, remainder) = Div(A[2], B[2]);
					Q = quotient;
					temp[0] = Sub(A[0], Mul(Q, B[0]));
					temp[1] = Sub(A[1], Mul(Q, B[1]));
					//temp[2] = Sub(A[2], Mul(Q, B[2]));
					temp[2] = remainder;
					//A[0] = B[0];
					A[1] = B[1];
					A[2] = B[2];
					B[0] = temp[0];
					B[1] = temp[1];
					B[2] = temp[2];
				}
		
				while (B[1].sign)
				{
					B[1] = Add(phi, B[1]);
				}
		
				while (isGreater(B[1], phi))
				{
					B[1] = Sub(B[1], phi); 
				}
		
				return B[1];
			}
		//****************************Power Mod of Big Integer**********//
		BigInt modExponent(BigInt base, BigInt exponent, BigInt mod)
			{
				BigInt result("1");
				BigInt one("1");
				BigInt two("2");
				BigInt exp_q, exp_r, result_q, result_r, base_q, base_r;
				while (!isZero(exponent))
				{
					tie(exp_q, exp_r) = exponent.Div(exponent, two);
					if (isEqual(exp_r, one))
					{
						tie(result_q, result_r) = result.Div(Mul(result, base), mod);
						result = result_r;
					}
					exponent = exp_q;
					tie(base_q, base_r) = base.Div(Mul(base, base), mod);
					base = base_r;
				}
				return result;
			}
		//**************************** Is it Prime?********************//
		bool isPrime(BigInt n)
			{
				BigInt temp = n;
				BigInt zero("0");
				BigInt one("1");
				BigInt two("2");
				BigInt three("3");
				BigInt a, q, r, power2, pow_2, n_1, count;
				BigInt test_numbers[2] = {two, three};
				
				if (isEqual(temp, two) || isEqual(temp, one))
				{
					return true;
				}
				//getting k & q
				temp = temp.Sub(temp, one);
				while (1)
				{
					tie(q, r) = q.Div(temp, two);
					if (isEqual(r, one))
					{
						break;
					}
					pow_2 = pow_2.Add(pow_2, one);
					temp = q;
				}
				//start testing
				for(int i = 0; i < 2; i++)
				{
					bool prime = false;
					a = test_numbers[i];
					power2 = one;
					n_1 = Sub(n, one);
					if (isEqual(modExponent(a, temp, n), one))
					{
						prime = true;
					}
					else if (isEqual(modExponent(a, temp, n), n_1))
					{
						prime = true;
					}
					else
					{
						for (int j = 1; j <= pow_2.long_bigInt[0]; j++)
						{
							power2 = power2.Mul(power2, two);
							BigInt power = power.Mul(power2, temp);
							if (isEqual(modExponent(a, power, n), n_1))
							{
								prime = true;
							}
						}
					}
					if(!prime)
					{
						return prime;
					}
				}
			}
				
	private:
		vector<unsigned long long> long_bigInt;
		int sign;
};


using namespace std;
int main()
{
	string inputText1, inputText2, p, q, e;
	getline(cin, inputText1);
	p = inputText1.substr(2, inputText1.length() - 2);
	getline(cin, inputText1);
	q = inputText1.substr(2, inputText1.length() - 2);
	getline(cin, inputText1);
	e = inputText1.substr(2, inputText1.length() - 2);
	BigInt P(p);
	BigInt Q(q);
	BigInt E(e);
	BigInt one("1");
	BigInt P_1 = P_1.Sub(P, one);
	BigInt Q_1 = Q_1.Sub(Q, one);
	BigInt N = N.Mul(P, Q);
	BigInt Phi = Phi.Mul(P_1, Q_1);
	BigInt D;

l:	getline(cin, inputText2);

	if (inputText2 == "IsPPrime")
	{
		if (P.isPrime(P))
		{
			cout << "Yes" << endl;
			goto l;
		}
		else
		{
			cout << "No" << endl;
			goto l;
		}
	}

	else if (inputText2 == "IsQPrime")
	{
		if (Q.isPrime(Q))
		{
			cout << "Yes" << endl;
			goto l;
		}
		else
		{
			cout << "No" << endl;
			goto l;
		}
	}

	else if (inputText2 == "PrintN")
	{	
		N.printBigInt();
		goto l;
	}

	else if (inputText2 == "PrintPhi")
	{
		Phi.printBigInt();
		goto l;
	}

	else if (inputText2 == "PrintD")
	{
		D.inverse_mod(E, Phi).printBigInt();
		goto l;
	}

	else if (inputText2.substr(0, 9) == "EncryptPu")
	{
		string msg = inputText2.substr(15, inputText2.length() - 16);
		BigInt Msg(msg);
		Msg.modExponent(Msg, E, N).printBigInt();
		goto l;
	}
	else if(inputText2.substr(0, 9) == "EncryptPr")
	{
		string msg = inputText2.substr(16, inputText2.length() - 17);
		BigInt Msg(msg);
		Msg.modExponent(Msg, E, N).printBigInt();
		goto l;
	}
	else
	{
		exit(0);
	}
	
	return 0;
}