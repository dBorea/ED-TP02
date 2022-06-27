#ifndef RANKED_STRING_H
#define RANKED_STRING_H

#include <iostream>
#include <string>
#include <climits>


// CLASSE DE COMPARAÇÃO
class CustomAlphaCmp{
	private:
		int table[1 << (CHAR_BIT - 1)];
	public:
		CustomAlphaCmp(const std::string& alpha);
		int operator()(const std::string& a, const std::string& b);
};

// STRING RANQUEADA
class RankedString{
	private:
		std::string palavra;
		int repeticoes;
		CustomAlphaCmp *customComparator;

	public:
		RankedString() : palavra(""), repeticoes(0) , customComparator(nullptr) {}
		RankedString(std::string palavraIn) : palavra(palavraIn), repeticoes(1), customComparator(nullptr) {}
		RankedString(std::string palavraIn, CustomAlphaCmp* customCmp) : palavra(palavraIn), repeticoes(1), customComparator(customCmp) {}
		~RankedString() { customComparator = nullptr; }

		RankedString& operator=(const RankedString& novo);
		bool operator==(const RankedString& outro) const;
		bool operator!=(const RankedString& outro) const;
		bool operator<(const RankedString& outro) const;
		bool operator>(const RankedString& outro) const;
		bool operator>=(const RankedString& outro) const;
		bool operator<=(const RankedString& outro) const;
		friend std::ostream &operator<<(std::ostream& output, const RankedString& rStr);

		std::string getPalavra() { return palavra; }
		int getRepeticoes() { return repeticoes; }
		void setOrder(CustomAlphaCmp* customCmp) { customComparator = customCmp; }
		void increment() { repeticoes++; }
};

#endif