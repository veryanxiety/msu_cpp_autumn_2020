#include <functional>
#include <cstddef>
#include <string>
#include <ctype.h> // for isspace

class TokenParser
{
	using FuncGetDigit = std::function<void (uint64_t x)>;
	using FuncGetStr = std::function<void (const std::string &x)>;

	private:
		FuncGetStr StartCallback;
		FuncGetDigit DigitTokenCallback;
		FuncGetStr StringTokenCallback;
		FuncGetStr FinishCallback;
	public:
		TokenParser()
		{
			FuncGetStr emptyStrFunc = [](const std::string &s) -> void {};
			FuncGetDigit emptyDigitFunc = [](uint64_t x) -> void {};
			
			StartCallback = emptyStrFunc;
			DigitTokenCallback = emptyDigitFunc;
			StringTokenCallback = emptyStrFunc;
			FinishCallback = emptyStrFunc;
		}

		~TokenParser()
		{
		}

		void SetStartCallback(FuncGetStr f)
		{
			StartCallback = f;
		}

		void SetDigitTokenCallback(FuncGetDigit f)
		{
			DigitTokenCallback = f;
		}

		void SetStringTokenCallback(FuncGetStr f)
		{
			StringTokenCallback = f;
		}

		void SetFinishCallback(FuncGetStr f)
		{
			FinishCallback = f;
		}

		void Parse(const std::string &s)
		{
			bool isDigit = true;
			bool isToken = false;
			std::string strToken = "";
			uint64_t digitToken = 0;

			StartCallback(s);

			for(auto c:s)
			{
				if(!isspace(c))
				{
					if(isToken)
					{
						strToken += c;
						if(!isdigit(c))
							isDigit = false;
						else if (isDigit)
							digitToken = digitToken * 10 + (c - '0');
					}
					else
					{
						isToken = true;
						strToken += c;
						if(!isdigit(c))
							isDigit = false;
						else
							digitToken = c - '0';
					}
				}
				else
				{
					if(isToken)
					{
						if(isDigit)
							DigitTokenCallback(digitToken);
						else
							StringTokenCallback(strToken);
						isDigit = true;
						isToken = false;
						strToken = "";
						digitToken = 0;
					}
					else
						continue;
				}
			}

			if(isToken)
			{
				if(isDigit)
					DigitTokenCallback(digitToken);
				else
					StringTokenCallback(strToken);
			}

			FinishCallback(s);
		}
};
