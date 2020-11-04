#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <time.h> // for rand
#include <stdlib.h> // for rand
#include <cstdint> // for numeric_limits
#include <ctype.h> // for isdigit
#include "tokenparser.cpp"

using vecNum = std::vector<uint64_t>;
using vecStr = std::vector<std::string>;
using FuncGetDigit = std::function<void (uint64_t x)>;
using FuncGetStr = std::function<void (const std::string &x)>;
using FuncTest = std::function<size_t (void/*const std::string &s, const vecNum &vn, const vecStr &vs*/)>;

std::string genString(size_t tokens, size_t lvl, vecNum &vn, vecStr &vs)
{
	std::string l = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-=+#$^&0123456789";
	std::string sep = " \t\n\r\v";
	size_t nl = l.length();
	size_t ns = sep.length();
	//size_t ms = 10; // maximum seps
	std::string res = "";
	size_t t;
	size_t tt = 0;

	for(size_t i = 0; i < tokens; i++)
	{
		t = std::rand() % lvl + tt;
		for(size_t j = 0;j < t; j++)
			res += sep[std::rand() % ns];

		t = (std::rand() % lvl) & 1;
		if (t)
		{
			bool isDigit = true;
			std::string cur = "";
			t = std::rand() % (lvl * lvl) + 1;
			for(size_t j = 0; j < t; j++)
			{
				auto c = l[std::rand() % nl]; 
				cur += c;
				if (!isdigit(c))
					isDigit = false;
			}
			if(isDigit)
				cur += l[std::rand() % (nl - 10)];
			vs.push_back(cur);
			res += cur;
		}
		else
		{
			uint64_t x = std::rand() % std::numeric_limits<uint64_t>::max();
			vn.push_back(x);
			res += std::to_string(x);
		}

		t = std::rand() % lvl;
		if (t)
			tt = 0;
		else
			tt = 1;
		for(size_t j = 0;j < t; j++)
			res += sep[std::rand() % ns];

	}
	return res;

}

size_t testCanCreate()
{
	TokenParser	t;
	FuncGetStr emptyStrFunc = [](const std::string &s) -> void {};
	FuncGetDigit emptyDigitFunc = [](uint64_t x) -> void {};

	t.SetStartCallback(emptyStrFunc);
	t.SetDigitTokenCallback(emptyDigitFunc);
	t.SetStringTokenCallback(emptyStrFunc);
	t.SetFinishCallback(emptyStrFunc);
	t.Parse("123 abc");
	return (0);
}

size_t testWithPrintCallback()
{
	TokenParser	t;
	FuncGetStr printStrFunc = [](const std::string &s) -> void {std::cout << s << ' ';};
	FuncGetDigit printDigitFunc = [](uint64_t x) -> void {std::cout << x << ' ';};
	std::string s = "TokenParser print this 3 times;";	

	t.SetStartCallback(printStrFunc);
	t.SetDigitTokenCallback(printDigitFunc);
	t.SetStringTokenCallback(printStrFunc);
	t.SetFinishCallback(printStrFunc);
	t.Parse(s);
	return (0);	
}

size_t testCheckCorrectWork1()
{
	TokenParser	t;
	vecNum vn = {};
	vecStr vs = {};
	vecNum vne = {};
	vecStr vse = {};	
	FuncGetStr emptyStrFunc = [](const std::string &s) -> void {};
	FuncGetStr getStrFunc = [&vs](const std::string &s) -> void {vs.push_back(s);};
	FuncGetDigit getDigitFunc = [&vn](uint64_t x) -> void {vn.push_back(x);};
	std::string s = genString(5, 2, vne, vse);	
	/*std::cout << "< <" << s << "> >" << std::endl;	
	for(auto c:vne)
		std::cout << c << ';';
	for(auto c:vse)
		std::cout << c << ';';
	std::cout << std::endl;*/

	t.SetStartCallback(emptyStrFunc);
	t.SetDigitTokenCallback(getDigitFunc);
	t.SetStringTokenCallback(getStrFunc);
	t.SetFinishCallback(emptyStrFunc);
	t.Parse(s);

	if(vne.size() != vn.size() || vse.size() != vs.size())
		return 1;
	//std::cout << "<<" << s << ">>";
	/*for(auto c:vn)
		std::cout << c << ';';
	for(auto c:vs)
		std::cout << c << ';';*/
	size_t len = vn.size();
	for(size_t i = 0; i < len; i++)
		if (vn[i] != vne[i])
			return 1;
	len = vs.size();
	for(size_t i = 0; i < len; i++)
		if (vs[i] != vse[i])
			return 1;		
	return 0;	
}

size_t testCheckCorrectWork2()
{
	TokenParser	t;
	vecNum vn = {};
	vecStr vs = {};
	vecNum vne = {};
	vecStr vse = {};	
	FuncGetStr emptyStrFunc = [](const std::string &s) -> void {};
	FuncGetStr getStrFunc = [&vs](const std::string &s) -> void {vs.push_back(s);};
	FuncGetDigit getDigitFunc = [&vn](uint64_t x) -> void {vn.push_back(x);};
	std::string s = genString(100, 10, vne, vse);	
	/*std::cout << "< <" << s << "> >" << std::endl;	
	for(auto c:vne)
		std::cout << c << ';';
	for(auto c:vse)
		std::cout << c << ';';
	std::cout << std::endl;*/

	t.SetStartCallback(emptyStrFunc);
	t.SetDigitTokenCallback(getDigitFunc);
	t.SetStringTokenCallback(getStrFunc);
	t.SetFinishCallback(emptyStrFunc);
	t.Parse(s);

	if(vne.size() != vn.size() || vse.size() != vs.size())
		return 1;
	//std::cout << "<<" << s << ">>";
	/*for(auto c:vn)
		std::cout << c << ';';
	for(auto c:vs)
		std::cout << c << ';';*/
	size_t len = vn.size();
	for(size_t i = 0; i < len; i++)
		if (vn[i] != vne[i])
			return 1;
	len = vs.size();
	for(size_t i = 0; i < len; i++)
		if (vs[i] != vse[i])
			return 1;		
	return 0;	
}

void printErrorState(size_t e)
{
	if(e)
		std::cout << "TEST IS FAILED." <<std::endl;
	else
		std::cout << "TEST IS OK." << std::endl;
}


struct stest 
{
	FuncTest func;
	std::string name;
} tests [] =
{
	{testCanCreate, "TokenParser is created and is got callbacks: "},
	{testWithPrintCallback, ""},
	{testCheckCorrectWork1, "Check is working correct with 5 tokens: "},
	{testCheckCorrectWork2, "Check is working correct with 100 tokens: "},
};

int		main()
{
	size_t errs = 0;
	size_t curr = 0;
	std::srand(std::time(nullptr));

	std::cout << "============================ Starting tests ============================" << std::endl;
	std::cout << std::endl;

	for(auto t:tests)
	{
		curr = t.func();
		errs += curr;
		std::cout << t.name;
		printErrorState(curr);
	}
 
	std::cout << "========================== Finished with "<< errs <<" errors =========================" << std::endl;

	return 0;
}
