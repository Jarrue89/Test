#pragma once

#include<string>


class ConvertProcess
{
public:

	int execute(void);

private:

	std::string _sInput;

	void Init();
	const std::string InputProcess() const;
	std::string Convert(const std::string& line);
	void ShowResult(std::string& result) const;


};

