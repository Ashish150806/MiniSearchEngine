#include "../include/indexer.h"
#include <fstream>
#include <sstream>

using namespace std;

static string readFile(const string& path) {
    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Indexer::addDocument(const string& filepath, int docId, Tokenizer& tokenizer) {
    string content = readFile(filepath);
    vector<string> tokens = tokenizer.tokenize(content);

    Document doc;
    doc.id = docId;
    doc.text = content;
    doc.length = tokens.size();
    doc.filename = filepath;

    documents.push_back(doc);

    for (const string& word : tokens) {
        invertedIndex[word][docId]++;
    }
}

int Indexer::getTotalDocuments() const {
    return documents.size();
}
