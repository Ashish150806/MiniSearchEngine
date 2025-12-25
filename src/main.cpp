#include <iostream>
#include <filesystem>
#include <chrono>
#include <algorithm>

#include "../include/tokenizer.h"
#include "../include/indexer.h"
#include "../include/search.h"

using namespace std;
namespace fs = filesystem;

int main() {
    Tokenizer tokenizer;
    tokenizer.loadStopwords("data/stopwords.txt");

    Indexer indexer;
    string dataPath = "data/20_newsgroups";

    cout << "Indexing documents from: " << dataPath << endl;

    auto start = chrono::high_resolution_clock::now();
    int docID = 0;

    for (const auto& entry : fs::recursive_directory_iterator(dataPath)) {
        if (entry.is_regular_file()) {
            indexer.addDocument(entry.path().string(), docID, tokenizer);
            docID++;
            if (docID % 100 == 0) cout << "." << flush;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "\nIndexed " << indexer.getTotalDocuments()
         << " documents in " << elapsed.count() << " seconds\n";

    SearchEngine engine(indexer, tokenizer);
    string query;

    while (true) {
        cout << "\nEnter search query (or 'exit'): ";
        getline(cin, query);
        if (query == "exit") break;

        auto qs = chrono::high_resolution_clock::now();
        vector<SearchResult> results = engine.search(query);
        auto qe = chrono::high_resolution_clock::now();

        chrono::duration<double> searchTime = qe - qs;
        cout << "Found " << results.size()
             << " results in " << searchTime.count() << " seconds\n";

        for (int i = 0; i < min(5, (int)results.size()); i++) {
            int id = results[i].docId;
            cout << "[" << i + 1 << "] Score: " << results[i].score
                 << " | File: " << indexer.documents[id].filename << endl;

            string snippet = indexer.documents[id].text.substr(0, 100);
            replace(snippet.begin(), snippet.end(), '\n', ' ');
            cout << "    Snippet: " << snippet << "...\n";
        }
    }
    return 0;
}
