#pragma once
#ifndef _PERMUTEDINDEX_H
#define _PERMUTEDINDEX_H
#include <iostream>
#include <cctype>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using std::vector;		using std::cin;
using std::cout;		using std::string;
using std::getline;		using std::istream;
using std::map;			using std::make_pair;
using std::pair;		using std::ostream;
using std::endl;
typedef string Sentence;
typedef vector<Sentence> Sentences;
typedef string Word;
typedef vector<Word> Words;
typedef pair<Words, int> Rotation;
typedef vector<Rotation> Rotations;
class Permuted_Index;
ostream& operator<< (ostream& os, const Words& rhs) {
	for (auto i : rhs) 
		os << i << ' ';
	return os;
}
size_t maxLen;
ostream& operator<< (ostream& os, const Rotation& rot) {
	auto& words = rot.first;
	int len = 0;
	string ret;
	for (size_t i = 0; i < words.size(); ++i) {
		if (i == rot.second) {
			len = maxLen - (len-1);
			ret = string(len, ' ') + ret + string(4, ' ');
		}
		len += words[i].size() + 1;
		ret += words[i] + " ";
	}
	os << ret;
	return os;
}

class Permuted_Index {
	friend ostream& operator<< (ostream& os, const Rotation& rot);
private:
	Sentences sentences;
	vector<Words> vec_Words;
	Rotations rotations;
	void split(const Sentence& sentence);
	void rotate(const Words& words);
public:
	Permuted_Index() {}
	void input(std::istream& is = std::cin);
	void split();
	void rotate();
	void sort();
	void unrotate();

	void display(ostream& os = std::cout) {
		for (auto rotation : rotations) {
			os << rotation << endl;
		}
	}
};
void Permuted_Index::unrotate() {
	for(auto it = rotations.begin(); it != rotations.end(); ++it){
		auto begin = it->first.rbegin();
		auto middle = it->first.rbegin() + it->second;
		auto end = it->first.rend();
		std::rotate(begin, middle, end);
	}
}
inline bool comp (const Rotation& lhs, const Rotation& rhs){
	auto lbeg = lhs.first.begin(), rbeg = rhs.first.begin();
	auto lend = lhs.first.end(), rend = rhs.first.end();
	//i, j ดย string_iterator
	for (auto i = lbeg, j = rbeg; i != lend && j != rend; ++i, ++j) {
		auto lch_beg = i->begin(), rch_beg = j->begin();
		auto lch_end = i->end(), rch_end = j->end();
		for (auto a = lch_beg, b = rch_beg; a != lch_end && b != rch_end; ++a, ++b) {
			int cmp = tolower(*b) - tolower(*a);
			if (cmp > 0)
				return true;
			else if (cmp == 0)
				continue;
			else
				return false;
		}
	}
	return false;

}
void Permuted_Index::sort() {
	std::sort(rotations.begin(), rotations.end(), comp);
}
inline void Permuted_Index::rotate(const Words& words) {
	for (int i = 0; i < words.size(); ++i) {
		pair<Words, int> rotated = make_pair(words, i);
		auto begin = rotated.first.begin();
		std::rotate(begin, begin + rotated.second, rotated.first.end());
		rotations.push_back(rotated);
	}
}
void Permuted_Index::rotate() {
	for (auto words : vec_Words) {
		rotate(words);
	}
	vec_Words.clear();
}
inline bool isnotspace(char c) { return !isspace(c); }
inline void Permuted_Index::split(const Sentence& sentence) {
	typedef Sentence::const_iterator iter;
	Words words;
	iter i = sentence.cbegin();

	while (i != sentence.cend()) {
		i = std::find_if(i, sentence.cend(), isnotspace);

		iter j = i;
		j = std::find_if(j, sentence.cend(), isspace);
		if (i != j) {
			words.push_back(string(i, j));
			i = j;
		}
	}
	vec_Words.push_back(words);
}
void Permuted_Index::split() {
	for (auto sentence : sentences) {
		split(sentence);
	}
	sentences.clear();
}
void Permuted_Index::input(std::istream& is) {
	std::string s;
	while (std::getline(is, s)) {
		maxLen = std::max(s.size(), maxLen);
		sentences.push_back(s);
	}
}
#endif // !_PERMUTEDINDEX_H