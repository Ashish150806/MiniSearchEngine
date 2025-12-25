#include "../include/search.h"
#include "../include/indexer.h"
#include "../include/tokenizer.h"

#include <cmath>
#include <algorithm>
#include <unordered_map>

SearchEngine::SearchEngine(Indexer& idx, Tokenizer& tok)
    : indexer(idx), tokenizer(tok) {}

std::vector<SearchResult> SearchEngine::search(const std::string& query) {
    std::vector<std::string> terms = tokenizer.tokenize(query);
    std::unordered_map<int, double> scores;

    int totalDocs = indexer.getTotalDocuments();

    for (const std::string& term : terms) {
        if (indexer.invertedIndex.count(term) == 0) continue;

        int docsWithTerm = indexer.invertedIndex[term].size();
        double idf = std::log10((double)totalDocs / (docsWithTerm + 1));

        for (const auto& entry : indexer.invertedIndex[term]) {
            int docID = entry.first;
            int freq  = entry.second;

            double tf = (double)freq / indexer.documents[docID].length;
            scores[docID] += tf * idf;
        }
    }

    std::vector<SearchResult> results;
    for (const auto& entry : scores) {
        results.push_back({entry.first, entry.second});
    }

    std::sort(results.begin(), results.end(),
        [](const SearchResult& a, const SearchResult& b) {
            return a.score > b.score;
        });

    return results;
}
