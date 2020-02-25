#pragma once

#include<string>
#include <vector>
#include <map>
#include <iostream>

class Convertion
{
public:
	Convertion(const std::string& inputText):_inputText(inputText), _result("") {

	}

    std::string Exec();
	
private:

    static const int ERROR = -1;

    enum MultiNumbers {
        hundred = 100,
        thousand = 1000,
        million = 1000000
    };

	static const std::map<std::string, int> _mNumbers;
	static std::map<std::string, int> createMapNumbers() {
        std::map<std::string, int> mapOfNumbers{
        {"one" , 1 },
        { "two" , 2 },
        {"three" , 3 },
        {"four" , 4 },
        {"five" , 5 },
        {"six" , 6 },
        {"seven" , 7 },
        {"eight" , 8 },
        {"nine" , 9 },
        {"ten" , 10 },
        {"eleven" , 11 },
        {"twelve" , 12 },
        {"thirteen" , 13 },
        {"fourteen" , 14 },
        {"fifteen" , 15 },
        {"sixteen" , 16 },
        {"seventeen" , 17 },
        {"eighteen" , 18 },
        {"nineteen" , 19 },
        {"twenty" , 20 },
        {"thirty" , 30 },
        {"forty" , 40 },
        {"fifty" , 50 },
        {"sixty" , 60 },
        {"seventy" , 70 },
        {"eighty" , 80 },
        {"ninety" , 90 },
        {"hundred" , 100 },
        {"thousand" , 1000 },
        {"million" , 1000000 }
        };
        return mapOfNumbers;
	}

	const std::string _inputText;
	std::vector<std::string> _vTokens;
    std::string _result;

    void Init();
	int SplitInput();
	int Convert();
    std::vector<std::string> CreateWordVector(const std::vector<std::string>::iterator it_ini) const;  
    std::vector<std::string>::iterator FindNumberEdge(const std::vector<std::string>::iterator it_ini) const;
    std::vector<int> ConvertEachWordToNum(std::vector<std::string>& vTokens);
    int CalculateNumber(std::vector<int>& vNumberTokens);
    std::string LinkVector(std::vector<std::string>& vResult);
};

