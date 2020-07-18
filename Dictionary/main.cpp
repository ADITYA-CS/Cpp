
#include <iostream>
#include "trie.hpp"

int main() {
  int n = 3;
  Word temp;
  string tmp;
  Trie trie;
  for (int i = 0; i < n; i++) {
    getline(cin, tmp);
    temp.SetTitle(tmp);
    getline(cin, tmp);
    temp.SetType(tmp);
    getline(cin, tmp);
    temp.SetDefinition(tmp);
    trie.Insert(temp);
  }

  for (int i = 0; i < n; i++) {
    getline(cin, tmp);
    temp = trie.Search(tmp);
    cout << temp;
  }

}