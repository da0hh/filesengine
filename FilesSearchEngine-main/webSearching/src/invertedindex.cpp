#include "invertedindex.h"

using namespace std;

void InvertedIndex::indexDocument(size_t doc_id, const string& content)
{
	map<string, int> word_count;
	stringstream ss(content);
	string word;
	while (ss >> word)
	{
		word_count[word]++;
	}

	lock_guard<mutex> lock(mutex_index);
	for (auto const& [word, count] : word_count) {
		Entry entry;
		entry.doc_id = doc_id;
		entry.count = static_cast<size_t>(count);

			freq_dictionary[word].push_back(entry);
	}
}

void InvertedIndex::updateDocumentBase(std::vector<std::string>input_docs)
{	
	map<string, int> local_map;
	docs = input_docs;
	freq_dictionary.clear();
	vector<thread> threads;

	for (size_t i = 0; i < input_docs.size(); i++)
	{
		threads.push_back(thread(&InvertedIndex::indexDocument, this, i, input_docs[i]));
	}

	for (auto& t : threads) {
		if (t.joinable())
			t.join();
	}

	for (auto& [word, entries] : freq_dictionary) {
		std::sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) {
			return a.doc_id < b.doc_id;
			});
	}
}

vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
	auto it = freq_dictionary.find(word);
	if (it != freq_dictionary.end())
		return it->second;
	return {};
}
