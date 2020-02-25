#include "ConvertProcess.h"

#include "Convertion.h"

int ConvertProcess::execute() {

	while(true){
		Init();
		const std::string line = InputProcess();
		std::string result = Convert(line);
		ShowResult(result);
	}

	return 0;
}

const std::string ConvertProcess::InputProcess() const {

    std::string line;
    std::cout << "Please type the number in words you want to convert from 0 to 999.999.999:\n";
	std::getline(std::cin, line);

	return line;

}

void ConvertProcess::Init() {
	_sInput = "";
}

std::string ConvertProcess::Convert(const std::string& line) {

	Convertion convertion(line);
	std::string result = convertion.Exec();

	return result;
}

void ConvertProcess::ShowResult(std::string& result) const {
		std::cout << result << std::endl;
}

