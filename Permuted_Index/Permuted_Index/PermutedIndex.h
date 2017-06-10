#pragma once
#ifndef _PERMUTEDINDEX_H
#define _PERMUTEDINDEX_H
#include <iostream>
#include <cctype>
#include <iomanip>
#include <vector>
#include <map>
#include <cassert>
#include <string>
#include <algorithm>
#include <tuple>
using std::vector;		using std::cin;
using std::cout;		using std::string;
using std::getline;		using std::istream;
using std::map;			using std::make_pair;
using std::pair;		using std::ostream;
using std::endl;		using std::setw;
using std::tuple;		using std::make_tuple;
using std::get;
typedef pair<string, size_t> Sentence;
typedef vector<Sentence> Sentences;
typedef string Word;	
// <words, line>
typedef pair<vector<Word>, size_t> Words;	
//<words, line, word_order>
typedef pair<Words, int> Rotation;
typedef vector<Rotation> Rotations;
//				sentence, line, word_order
typedef tuple<string, size_t, size_t> outputForm;
class Permuted_Index;



class Permuted_Index {
	friend ostream& operator<< (ostream& os, Permuted_Index& object);
	friend ostream& operator<< (ostream& os, const outputForm& output);
private:
	size_t maxLen;
	Sentences sentences;		//original sentence
	vector<Words> vec_Words;	//split to each word
	Rotations rotations;		//rotated ver
	vector<outputForm> output;	
	void split();
	void split(const Sentence& sentence);
	void rotate();
	void rotate(const Words& words);
	void sort();
	void unrotate();
	void trimForOutput();
	bool done;
public:
	Permuted_Index() : done(false), maxLen(0) {}
	void showOriginal(ostream& os = std::cout) { for (auto i : sentences) os << i.first << endl; }
	void compute() { if (!done) { split(); rotate(); sort(); unrotate(), trimForOutput(); done = true; } }
	void input(std::istream& is = std::cin);

	void display(ostream& os = std::cout) { os << *this; }
};





ostream& operator<< (ostream& os, const outputForm& output) {
	os << get<0>(output) << "line: " << setw(4) << get<1>(output)
		<< " | word: " << setw(4) << get<2>(output);
	return os;
}
ostream& operator<< (ostream& os, Permuted_Index& object) {
	//this condition guagentee to show output without exception.
	if (!object.done)
		object.compute();

	for (auto i :object.output) 
		os << i << endl;
	return os;
}

inline void Permuted_Index::trimForOutput() {
	static string separator(" | ");

	for (Rotation rotation : rotations) {

		auto size = rotation.first.first.size();
		auto idx = rotation.second;
		auto& words = rotation.first.first;

		string retSentence;
		size_t len = 0;
		for (size_t i = 0; i < size; ++i) {
			if (i == idx) {
				len = maxLen - (len - 1);
				retSentence = string(len, ' ') + retSentence + separator;
			}
			len += words[i].size() + 1;
			retSentence += words[i] + " ";
		}

		retSentence += string(separator.size()+ (1 + maxLen) * 2 - retSentence.size(), ' ');
		output.push_back(make_tuple(retSentence, rotation.first.second, rotation.second));
	}
	rotations.clear();
}

void Permuted_Index::unrotate() {
	// chunks, line, word_order
	for(auto it = rotations.begin(); it != rotations.end(); ++it){
		auto begin = it->first.first.rbegin();
		auto middle = it->first.first.rbegin() + it->second;
		auto end = it->first.first.rend();
		std::rotate(begin, middle, end);
	}
}

inline bool comp (const Rotation& lhs, const Rotation& rhs){
	auto lbeg = lhs.first.first.begin(), rbeg = rhs.first.first.begin();
	auto lend = lhs.first.first.end(), rend = rhs.first.first.end();
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
	for (int i = 0; i < words.first.size(); ++i) {
		// pair: chunks, line, word_order
		pair<Words, int> rotated = make_pair(words, i);
		auto begin = rotated.first.first.begin();
		std::rotate(begin, begin + rotated.second, rotated.first.first.end());
		rotations.push_back(rotated);
	}
}

void Permuted_Index::rotate() {
	for (Words words : vec_Words) {
		rotate(words);
	}
	vec_Words.clear();
}

inline bool isnotspace(char c) { return !isspace(c); }

inline void Permuted_Index::split(const Sentence& sentence) {
	typedef Sentence::first_type::const_iterator iter;
	Words words;
	words.second = sentence.second;
	iter i = sentence.first.cbegin();

	while (i != sentence.first.cend()) {
		i = std::find_if(i, sentence.first.cend(), isnotspace);

		iter j = i;
		j = std::find_if(j, sentence.first.cend(), isspace);
		if (i != j) {
			words.first.push_back(string(i, j));
			i = j;
		}
	}
	vec_Words.push_back(words);
}

void Permuted_Index::split() {
	for (auto sentence : sentences) {
		split(sentence);
	}
}

void Permuted_Index::input(std::istream& is) {
	Sentence s;
	while (std::getline(is, s.first)) {
		maxLen = std::max(s.first.size(), maxLen);
		s.second = sentences.size() + 1;
		sentences.push_back(s);
	}
}
#endif // !_PERMUTEDINDEX_H