#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "json.hpp"
#include <algorithm>
#include <stdexcept>

class ConverterJSON
{
public:
	ConverterJSON() {
		std::ifstream file("config.json");
		if (!file.is_open())
			throw std::runtime_error("config file is missing");
		file >> _config;
		file.close();
	}

	std::vector<std::string> getTextDocuments() const;

	int getResponsesLimit() const;

	std::vector<std::string> getRequests() const;

	void putAnswers(std::vector<std::vector<std::pair<int, float>>>answers);

private:
	nlohmann::json _config;
};