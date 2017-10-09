#pragma once
#ifndef _PERMUTEDINDEX_H
#define _PERMUTEDINDEX_H
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <locale>
#include <map>
#include <string>
#include <tuple>
#include <vector>
using std::vector;		using std::cin;
using std::cout;		using std::string;
using std::getline;		using std::istream;
using std::map;			using std::make_pair;
using std::pair;		using std::ostream;
using std::endl;		using std::setw;
using std::tuple;		using std::make_tuple;
using std::get;			using std::tie;
using std::lexicographical_compare;



using Word = string;
using Words = vector<Word>;
//					<words, line, word_order>
using Data = tuple<Words, size_t, size_t>;
using Sentence = pair<string, size_t>;
using Sentences = vector<Sentence>;
using Words = vector<Word>;
typedef vector<Data> Rotations;
//			sentence, line, word_order
typedef tuple<string, size_t, size_t> outputForm;

class Permuted_Index;



class Permuted_Index {
	friend ostream& operator<< (ostream& os, Permuted_Index& object);
	friend ostream& operator<< (ostream& os, const outputForm& output);
private:
	size_t maxLen;
	Sentences sentences;		//original sentence
	vector<Data> dataVector;	//split to each word
	Rotations rotations;		//rotated ver
	vector<outputForm> output;	
	void split();
	void split(const Sentence& sentence);
	void rotate();
	void rotate(Data&);
	void sort();
	void unrotate();
	void trimForOutput();
	bool done;
	void compute() { if (!done) { split(); rotate(); sort(); unrotate(), trimForOutput(); done = true; } }
public:
	Permuted_Index() : done(false), maxLen(0) {}
	void showOriginal(ostream& os = std::cout) { for (auto i : sentences) os << i.first << endl; }
	void setData(std::istream& is = std::cin);

	void result(ostream& os = std::cout) { os << *this; }
};


ostream& operator<< (ostream& os, const outputForm& output) {
	const auto& [sentence, lineNO, wordOrder] = output;

	os << sentence << "line: " << setw(4) << lineNO
		<< " | word: " << setw(4) << wordOrder;
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

	for (Data& rotation : rotations) {

		auto& [words, lineNO, wordOrder] = rotation;
		Word::size_type size = words.size();

		string retSentence;
		size_t len = 0;
		for (size_t i = 0; i < size; ++i) {
			if (i == wordOrder) {
				len = maxLen - (len - 1);
				retSentence = string(len, ' ') + retSentence + separator;
			}
			len += words[i].size() + 1;
			retSentence += words[i] + " ";
		}

		retSentence += string(separator.size()+ (1 + maxLen) * 2 - retSentence.size(), ' ');

		//lineNO와 wordOrder에 +1을 하는것은 시작점을 1로 하기 위함이다.
		output.push_back({ retSentence, lineNO + 1, wordOrder + 1 });
	}
	rotations.clear();
}

void Permuted_Index::unrotate() {
	for(Data& rotation : rotations){
		auto&[words, ignore, wordOrder] = rotation;

		auto begin = words.rbegin();
		auto middle = words.rbegin() + wordOrder;
		auto end = words.rend();
		std::rotate(begin, middle, end);
	}
}

void Permuted_Index::sort() {
	auto IgnoreCase = [&](const Data& lhs, const Data& rhs) -> bool
	{
		const vector<Word>& lwords = get<0>(lhs),
			rwords = get<0>(rhs);
		//each iterator represents the word.
		auto lit = lwords.cbegin(), rit = rwords.cbegin();
		for (; lit != lwords.cend() && rit != rwords.cend(); ++lit, ++rit)
		{
			if (*lit == *rit)
				continue;

			return lexicographical_compare(lit->cbegin(), lit->cend(),
				rit->cbegin(), rit->cend(), 
				[](char l, char r) {return tolower(l) < tolower(r); });
		}

		if (lit == lwords.cend())
			return true;
		else
			return false;
	};

	std::sort(rotations.begin(), rotations.end(), IgnoreCase);
}

inline void Permuted_Index::rotate(Data& data) {
	auto&[words, lineNO, ignore] = data;
	for (size_t wordOrder = 0; wordOrder < words.size(); ++wordOrder) {
		// pair: chunks, line, word_order
		std::rotate(words.begin(), words.begin() + wordOrder, words.end());
		rotations.push_back({ words,lineNO,wordOrder });
	}
}

void Permuted_Index::rotate() {
	for (Data& words : dataVector) {
		rotate(words);
	}
	dataVector.clear();
}


inline void Permuted_Index::split(const Sentence& sentence) {

	auto isnotspace = [](char c) -> bool {return !isspace(c); };

	using cIter = Sentence::first_type::const_iterator;

	Words words;
	size_t lineNO = sentence.second, numberOfWords;

	cIter i = sentence.first.cbegin();

	while (i != sentence.first.cend()) {
		i = std::find_if(i, sentence.first.cend(), isnotspace);

		cIter j = i;
		j = std::find_if(j, sentence.first.cend(), isspace);
		if (i != j) {
			words.push_back(string(i, j));
			i = j;
		}
	}
	dataVector.push_back({ words, lineNO, numberOfWords });
}

void Permuted_Index::split() {
	for (auto sentence : sentences) {
		split(sentence);
	}
}

void Permuted_Index::setData(std::istream& is) {
	done = false;
	Sentence s;
	while (std::getline(is, s.first)) {
		maxLen = std::max(s.first.size(), maxLen);
		s.second = sentences.size();
		sentences.push_back(s);
	}
}
#endif // !_PERMUTEDINDEX_H