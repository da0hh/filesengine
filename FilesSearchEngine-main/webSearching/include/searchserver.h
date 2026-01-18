#pragma once
#include "invertedindex.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cmath>

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : _index(idx) {};

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input, int max_responses);

private:
    InvertedIndex& _index;
};