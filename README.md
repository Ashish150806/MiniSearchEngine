# Mini Search Engine — From Text to Meaning

## 📌 Overview
This project implements a Mini Search Engine using only
Data Structures and Algorithms. It indexes a large text
dataset and retrieves relevant documents using **manual TF-IDF**.

🚫 No ML, NLP, or search libraries are used.

---

## 📂 Dataset
- 20 Newsgroups (text-only)
- Source: UCI ML Repository
- Dataset is excluded from GitHub due to size

---

## ⚙️ Core Features
- Text preprocessing (tokenization, stopwords, cleaning)
- Inverted Index construction
- TF-IDF based ranking
- Performance measurement (search time)

---

## 🧠 Data Structures Used

| Purpose | Data Structure |
|------|----------------|
| Inverted Index | unordered_map<string, unordered_map<int,int>> |
| Documents | vector<Document> |
| Stopwords | set<string> |
| Ranking | vector + sort |

---

## ⏱️ Complexity Analysis
- Indexing: **O(N × W)**
- Query Processing: **O(Q × D)**
- Space: **O(V + postings)**

---

## ▶️ How to Run

### Compile
```bash
g++ src/*.cpp -o search_engine

##  Performance Analysis

- Indexing Time: ~18 seconds for 20,000 documents
- Average Query Time: ~0.01 seconds
- Memory Usage: ~50–65 MB

The inverted index allows fast query resolution at the cost of higher memory usage.
This trade-off is acceptable for search-oriented systems.

