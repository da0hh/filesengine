#include <iostream>
#include "converterJSON.h"
#include "invertedindex.h"
#include "searchserver.h"
#include "json.hpp"
#include <exception>


using json = nlohmann::json;

using namespace std;

int main(){
	try 
	{
		ConverterJSON converter;

		auto files = converter.getTextDocuments();
		InvertedIndex inverter;
		inverter.updateDocumentBase(files);

		SearchServer searcher(inverter);

		auto requests = converter.getRequests();
		auto responsesLimit = converter.getResponsesLimit();

		auto res = searcher.search(requests, responsesLimit);

		vector<vector<pair<int, float>>> answer;
		for (const auto& queryRes : res)
		{
			vector<pair<int, float>> convertedRes;
			for (const auto& item : queryRes) {
				convertedRes.push_back({ (int)item.doc_id, item.rank });
			}
			answer.push_back(convertedRes);
		}

		converter.putAnswers(answer);

		cout << "Search engine finished successfully." << endl;
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
		return -1;
	}

	return 0;
}
