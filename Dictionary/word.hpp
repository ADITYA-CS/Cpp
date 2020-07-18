#ifndef DICTIONARY_WORD
#define DICTIONARY_WORD

#include <iostream>
#include <utility>
using std::cin;
using std::cout;
using std::string;

class Word {
private:
  string title_;
  string type_;
  string definition_;

public:
  Word();
  Word(string, string, string);
  Word(string, string);
  Word(const Word &);
  Word(Word &&) noexcept ;
  Word& operator=(const Word &);
  Word& operator=(Word &&) noexcept ;
  ~Word();

  void SetTitle(string);
  void SetType(string);
  void SetDefinition(string);
  [[nodiscard]] string GetTitle() const;
  [[nodiscard]] string GetType() const ;
  [[nodiscard]] string GetDefinition() const;
  friend std::ostream& operator<<(std::ostream &, const Word &);
//   friend istream & operator>>(istream &, Word &)
};

Word::Word() = default;

Word::Word(string title, string type, string definition) {
  title_ = std::move(title);
  type_ = std::move(type);
  definition_ = std::move(definition);
}

Word::Word(string title, string definition) {
  title_ = std::move(title);
  definition_ = std::move(definition);
}

Word::Word(const Word &wd) {
  title_ = wd.title_;
  type_ = wd.type_;
  definition_ = wd.definition_;
}

Word::Word(Word &&wd) noexcept {
  title_ = wd.title_;
  type_ = wd.type_;
  definition_ = wd.definition_;
}

Word& Word::operator=(const Word &wd) = default;

Word& Word::operator=(Word &&wd) noexcept {
  title_ = wd.title_;
  type_ = wd.type_;
  definition_ = wd.definition_;
  return *this;
}

Word::~Word() = default;

void Word::SetTitle(string title) {
  title_ = std::move(title);
}

void Word::SetType(string type) {
  type_ = std::move(type);
}

void Word::SetDefinition(string definition) {
  definition_ = std::move(definition);
}

string Word::GetTitle() const {
  return title_;
}

string Word::GetType() const{
  return type_;
}

string Word::GetDefinition() const {
  return definition_;
}

std::ostream& operator<<(std::ostream &out, const Word &wd) {
  out << wd.title_ << "\n";
  out<< wd.type_ << "\n";
  out<< wd.definition_ << "\n";
  return out;
}

#endif
