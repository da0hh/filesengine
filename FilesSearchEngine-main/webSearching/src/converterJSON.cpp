#include "converterJSON.h"
#include <sstream>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

string appVersion = "0.1";

std::vector<std::string> ConverterJSON::getTextDocuments() const
{
	if (!_config.contains("config"))
		throw runtime_error("config file is empty");

	if (_config["config"]["version"] != appVersion)
		throw runtime_error("config.json has incorret file version");

	vector<string> contents;

	for (const auto& path : _config["files"])
	{
		ifstream doc(path.get<string>());

		if (doc.is_open())
		{
			string content((istreambuf_iterator<char>(doc)), istreambuf_iterator<char>());
			contents.push_back(content);
		}
		else
			cerr << "File not found: " << path << endl;
	}

	return contents;
}

int ConverterJSON::getResponsesLimit() const
{
	return _config["config"].value("max_responses", 5);
}

vector<string> ConverterJSON::getRequests() const
{
	ifstream file("../jsonFiles/requests.json");
	if (!file.is_open())
		throw runtime_error("requests file is missing");

	json doc;
	file >> doc;

	vector<string> contents;

	if (doc["requests"].size() > 1000)
		throw runtime_error("Requests sum is higher than available");
	
	for (const auto &request : doc["requests"])
	{
		string requestText = request.get<string>();

		stringstream ss(requestText);
		string word;
		int wordCount = 0;
		while (ss >> word) wordCount++;

		if (wordCount > 10 || wordCount < 1)
			throw runtime_error("Request has invalid count of words");

		contents.push_back(requestText);
	}	

	return contents;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>>answers)
{
	json fullDict;
	
	for (auto i = 0; i < answers.size(); i++) {
		stringstream ss;
		ss << "request" << setw(3) << setfill('0') << (i + 1);
		string requestName = ss.str();

		json requestData;

		if (answers[i].empty())
			requestData["result"] = "false";
		else {
			requestData["result"] = "true";

			if (answers[i].size() == 1) 
			{
				requestData["docid"] = answers[i][0].first;
				requestData["rank"] = answers[i][0].second;
			}
			else if(answers[i].size() > 1)
			{
				for (const auto& res : answers[i]) {
					json relevance;
					relevance["docid"] = res.first;
					relevance["rank"] = res.second;
					requestData["relevance"].push_back(relevance);
				}
			}
		}

		fullDict["answers"][requestName] = requestData;

	}

	ofstream outFile("../jsonFiles/answers.json");
	if (outFile.is_open()) {
		outFile << fullDict.dump(4);
		outFile.close();
	}
	else {
		cerr << "Error: Could not write to answers.json" << endl;
	}
}