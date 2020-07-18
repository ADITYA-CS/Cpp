#ifndef DICTIONARY_TRIE
#define DICTIONARY_TRIE

#include <iostream>
#include <vector>
#include <unordered_map>
#include "word.hpp"

#define NUMBER_OF_LETTER_IN_WORD 27

using std::vector;
using std::unordered_map;

struct Node{
    bool word_end;
    vector<Node *> child;
    Word word;
    Node();
    explicit Node(bool, Word);
    ~Node();
};

class Trie {
 private:
  unordered_map<char, int> indexing_;
  Node *root_;
 public:
  Trie();
  void Insert(Word&);
  Word Search(string) noexcept ;
};

/**
 *  Node method definition
 */
Node::Node() {
  word_end = false;
  child.resize(NUMBER_OF_LETTER_IN_WORD, nullptr);
}

Node::Node(bool b, Word wd) {
  word_end = b;
  child.resize(NUMBER_OF_LETTER_IN_WORD, nullptr);
  word = std::move(wd);
}

Node::~Node() = default;

/**
 *  Trie method definition
 */
Trie::Trie() {
  for (int i = 0; i < 26; i++) {
    indexing_['a' + i] = i;
  }
  indexing_[' '] = 26;
  root_ =  new Node();
}

void Trie::Insert(Word& wd) {
  string el = wd.GetTitle();
  int len = el.size();
  auto ptr = root_;

  for (int i = 0, index; i < len; i++) {
    index = indexing_[el[i]];
    if (ptr->child[index] == nullptr) {
      ptr->child[index] = new Node();
    }
    ptr = ptr->child[index];
  }
  if(ptr->word_end)
    return;
  ptr->word_end = true;
  ptr->word = std::move(wd);
}

Word Trie::Search(string key) noexcept {
  int len = key.size();
  auto ptr = root_;

  for (int i = 0, index; i < len; i++) {
    index = indexing_[key[i]];
    if (ptr->child[index] == nullptr) {
      return Word();
    }
    ptr = ptr->child[index];
  }
  if(ptr->word_end)
    return ptr->word;
  return Word();
}
#endif
