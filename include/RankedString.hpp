#ifndef RANKED_STRING_H
#define RANKED_STRING_H

#include <iostream>
#include <string>
#include <climits>

class CustomAlphaCmp{
	private:
		int table[1 << CHAR_BIT];
	public:
		CustomAlphaCmp(const std::string& alpha){
			for(int i=0; i<(1 << CHAR_BIT); i++){ table[i] = INT_MAX; }

			int value = 0;
			for (auto x : alpha)
				table[ static_cast<unsigned char>(x) ] = ++value;
		}

		int operator()(const std::string& a, const std::string& b){
			auto lhs = a.begin();
			auto rhs = b.begin();

			for (; lhs != a.end() && rhs != b.end(); ++lhs,++rhs){
				if(*rhs == (char)"-") rhs++;
				if(*lhs == (char)"-") lhs++;
				int lhs_val = table[static_cast<unsigned char>(*lhs)];
				int rhs_val = table[static_cast<unsigned char>(*rhs)];

					if (lhs_val < rhs_val)
						return -1;
					else if (lhs_val > rhs_val)
						return 1;
			}

			if(lhs == a.end())
				if(rhs == b.end())
					return 0;
				else return -1;
			return 1;
		}
};

class RankedString{
	private:
		std::string palavra;
		int repeticoes;
		CustomAlphaCmp *customComparator;

	public:
		RankedString() : palavra(""), repeticoes(0) , customComparator(nullptr) {}
		RankedString(std::string palavraIn, CustomAlphaCmp& customCmp) : palavra(palavraIn), repeticoes(1), customComparator(&customCmp) {}
		~RankedString() { customComparator = nullptr; }

		int retornaCaractere() const;
		RankedString& operator=(const RankedString& novo) {
			palavra = novo.palavra;
			repeticoes = novo.repeticoes;
			customComparator = novo.customComparator;
		}
		bool operator==(const RankedString& outro) const {
			return palavra == outro.palavra;
		}
		bool operator!=(const RankedString& outro) const {
			return palavra != outro.palavra;
		}
		bool operator<(const RankedString& outro) const {
			return (*customComparator)(this->palavra, outro.palavra) == -1;
		}
		bool operator>(const RankedString& outro) const {
			return (*customComparator)(this->palavra, outro.palavra) == 1;
		}

};

#endif