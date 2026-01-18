#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <thread>
#include <mutex>

struct Entry
{
	size_t doc_id, count;
	bool operator == (const Entry& other) const {
		return(doc_id == other.doc_id &&
			count == other.count);
	}
};

class InvertedIndex
{
public:
	InvertedIndex() = default;

	void updateDocumentBase(std::vector<std::string>input_docs);
std::vector<Entry> GetWordCount(const std::string& word);
private:
	std::vector<std::string> docs;
	std::map<std::string, std::vector<Entry>> freq_dictionary;

	void indexDocument(size_t doc_id, const std::string& content);
	std::mutex mutex_index;
};