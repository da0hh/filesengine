#include "searchserver.h"

using namespace std;

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& queries_input, 
	int max_responses)
{
	vector<vector<RelativeIndex>> result;
	for (const auto& query : queries_input) {
		stringstream ss(query);
		string word;
		set<string> unique_words;
		while (ss >> word)
			unique_words.emplace(word);
		
		vector<string> sorted_words(unique_words.begin(), unique_words.end());

		sort(sorted_words.begin(), sorted_words.end(), [this](const string& a, const string& b) {
			return _index.GetWordCount(a).size() < _index.GetWordCount(b).size();
			});

		map<size_t, size_t> doc_scores;

		for (const auto& word : sorted_words) {
			auto entries = _index.GetWordCount(word);

			for (const auto& entry : entries) {
				doc_scores[entry.doc_id] += entry.count;
			}
		}

		size_t max_abs_relevance = 0;
		for (const auto& [doc_id, score] : doc_scores) {
			if (score > max_abs_relevance) max_abs_relevance = score;
		}

		vector<RelativeIndex> query_results;
		if (max_abs_relevance > 0) {
			for (auto const& [doc_id, score] : doc_scores) {
				float rank = static_cast<float>(score) / max_abs_relevance;
				query_results.push_back({ doc_id, rank });
			}
		}

		sort(query_results.begin(), query_results.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
			if (std::abs(a.rank - b.rank) > 0.000001f) {
				return a.rank > b.rank; 
			}
			return a.doc_id < b.doc_id;
			});

		if (query_results.size() > max_responses) {
			query_results.resize(max_responses);
		}

		result.push_back(query_results);
	}

	return result;
}