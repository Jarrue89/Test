#include "Convertion.h"

#include <sstream>


const std::map<std::string, int> Convertion::_mNumbers = Convertion::createMapNumbers();

std::string Convertion::Exec() {
   
    Init();

    if (Convert() == ERROR)
        return std::string();

    return _result;
}

int Convertion::SplitInput() {

    if (_inputText.empty())
        return ERROR;

    if (!_vTokens.empty())
        _vTokens.clear();

    std::string copyInputText (_inputText);
    std::istringstream iss(copyInputText);
    std::string token;

    while (std::getline(iss, token, ' ')) {
        if (!token.empty()) {
            _vTokens.push_back(token);
        }
    }

    return 0;
}

int Convertion::Convert() {

    //1. Split and fill "_vTokens"
    if (SplitInput() == ERROR)
        return ERROR;

    //2. Fills vResult
        //2.1 If it is not a number the item is added directly
        //2.2. If it is a number the item is added after calculating
            //2.2.1 Get the whole number
            //2.2.2 Convert each number to int
            //2.2.3 Calculate the number

    std::vector<std::string> vResult;
    std::vector<std::string>::iterator it = _vTokens.begin();
    while (it != _vTokens.end()) {
        std::string token = *it;
        
        //2.1
        if (_mNumbers.find(token) == _mNumbers.end())
            vResult.push_back(token);
        //2.2
        else {
            //2.2.1
            std::vector<std::string> vTokens = CreateWordVector(it);
            //2.2.2
            _vNumberTokens.clear();
            _vNumberTokens = ConvertEachWordToNum(vTokens);
            if (_vNumberTokens.empty()) {
                it++;
                continue;
            }
            //2.2.3
            double convertion = CalculateNumber();
            vResult.push_back(std::to_string(convertion));

            it = it + vTokens.size() - 1;
        }

        it++;
    }
    //3. Link the result in order to have it in a line
    _result = LinkVector(vResult);

    return 0;
}

std::vector<int> Convertion::ConvertEachWordToNum(std::vector<std::string>& vTokens){

    if (vTokens.empty())
        return std::vector<int>();

    std::vector<int> vNumberTokens;
    for (auto& i : vTokens) {
        std::map<std::string, int>::const_iterator it = _mNumbers.find(i);
        if (it != _mNumbers.end())
            vNumberTokens.push_back(it->second);
        else
            return std::vector<int>();
    }

    return vNumberTokens;
}

double Convertion::CalculateNumber() {

    double result = Calculate(_vNumberTokens.begin(), _vNumberTokens.end() - 1);

    return result;
}


void Convertion::Init() {
    _vTokens.clear();
    _vNumberTokens.clear();
    _result = "";
}

std::vector<std::string>::iterator Convertion::FindNumberEdge(const std::vector<std::string>::iterator it_ini) const {
    std::vector<std::string>::iterator it = it_ini + 1;
    std::vector<std::string>::iterator it_end;

    while (it != _vTokens.end()) {
        std::string token = *it;
        if (_mNumbers.find(token) == _mNumbers.end()) 
            return it;

        it++;
    }

    return it;
}

std::vector<std::string> Convertion::CreateWordVector(const std::vector<std::string>::iterator it_ini)const  {
    std::vector<std::string>::iterator it = it_ini;
    std::vector<std::string> vTokens;

    std::vector<std::string>::iterator it_end = FindNumberEdge(it);
    while (it != it_end) {
        vTokens.push_back(*it);
        it++;
    }

    return vTokens;
}


std::string Convertion::LinkVector(std::vector<std::string>& vResult) {

    std::string result;
    std::stringstream ss;

    for (auto& i : vResult) 
        ss << i << " ";

    return ss.str();
}

double Convertion::Calculate(std::vector<int>::iterator it_ini, std::vector<int>::iterator it_end) {

    double result = 0;

    result = CalculateParts(it_ini, it_end, MultiNumbers::million);
    if (result)
        return result;

    result = CalculateParts(it_ini, it_end, MultiNumbers::thousand);
    if (result)
        return result;

    result = CalculateParts(it_ini, it_end, MultiNumbers::hundred);
    if (result)
        return result;

    result = CalculateUnits(it_ini, it_end);
    if (result)
        return result;

    return 0;
}


double Convertion::CalculateParts(std::vector<int>::iterator it_ini, std::vector<int>::iterator it_end, MultiNumbers multiNumber) {

    // Searching the multinumber. If does not exit return 0.
    std::vector<int>::iterator it;   
    for (it = it_ini; it <= it_end; it++) {
        if (*it == multiNumber)
            break;

        if (it == it_end)
            return 0;
    }


    double result = 0;
    double calculate = Calculate(it_ini, it - 1) * multiNumber;

    if (it + 1 == _vNumberTokens.end())
        result = calculate;
    else
        result = calculate + Calculate(it + 1, it_end);


    return result;
}

double Convertion::CalculateUnits(std::vector<int>::iterator it_ini, std::vector<int>::iterator it_end) {

    double result = 0;

    if (it_ini == it_end)
        return *it_ini;

    std::vector<int>::iterator it;
    for (it = it_ini; it <= it_end; it++) {
        result += *it;
        if (it == it_end)
            break;
    }

    return result;

}








