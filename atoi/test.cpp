#include <cstdio> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <vector> 
#include <algorithm> 
#include <iostream>
#include <stack>

using namespace std;

int str2int(const char* str)
{
	const int MAX_INT = 0x7fffffff; // INT 最大 = 2147483647
	const int MIN_INT = -MAX_INT - 1; // INT 最小 = - 2147483648

	unsigned int n = 0; // 无符号数,范围比int大

	if (str == NULL)
		return 0;

	//处理空格
	while (*str == ' ')
		str++;

	// 正负号
	int sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}

	while (isdigit(*str)) //是数字就处理
	{
		int c = *str - '0';
		// 最大int数处理
		if (sign > 0 && (n > MAX_INT / 10 || (n == MAX_INT / 10 && c > MAX_INT % 10))) 
		{
			n = MAX_INT;
			break;
		}
		// 最小int数处理
		else if (sign < 0 && (n >(unsigned)MIN_INT / 10 || (n == (unsigned)MIN_INT / 10 && c > (unsigned)MIN_INT % 10))){
			n = MIN_INT;
			break;
		}
		else{
			n = n * 10 + c;
			str++;
		}
	}
	return sign > 0 ? (int)n : -(int)n;
}

int main(void) 
{
	printf("自定义str2int\n");
	cout << str2int("-2147483649") << endl; // - 2147483648
	cout << str2int("-2147483658") << endl; // - 2147483648

	cout << str2int("2147483648") << endl; // 2147483647
	cout << str2int("2147483658") << endl; // 2147483647

	cout << str2int("21474836") << endl; // 
	cout << str2int("-21474836") << endl; // 

	printf("\natoi库函数\n");
	cout << atoi("+0.001") << endl; // 0
	cout << atoi("   +12") << endl; // 0
	cout << atoi("-+12") << endl; // 0

	cout << atoi("-a102a3sfd3") << endl; // 0
	cout << atoi("-102a3sfd3") << endl; // 102

	cout << atoi("2147483648") << endl; // 2147483647
	cout << atoi("2147483648") << endl; // 2147483647
	
	cout << atoi("-2147483649") << endl; // - 2147483648
	cout << atoi("-2147483658") << endl; // - 2147483648
	
	return 0;
}
