#ifndef RANKED_STRING_H
#define RANKED_STRING_H

#include <iostream>
#include <string>
#include <climits>

class CustomAlphaCmp{
	private:
		int table[1 << (CHAR_BIT - 1)];
	public:
		CustomAlphaCmp(const std::string& alpha){
			for(int i=0; i<(1 << (CHAR_BIT - 1)); i++){ table[i] = i; }

			int value = 'a';

			for (auto x : alpha){
				table[ static_cast<unsigned char>(x) ] = ++value;

				if(x >= 'a' && x <= 'z')
					table[ static_cast<unsigned char>(x) - 32 ] = value;
				else if(x >= 'A' && x <= 'Z')
					table[ static_cast<unsigned char>(x) + 32 ] = value;
			}
		}

		int operator()(const std::string& a, const std::string& b){
			auto lhs = a.begin();
			auto rhs = b.begin();

			for (; lhs != a.end() && rhs != b.end(); ++lhs,++rhs){
				// if(*rhs == '-') rhs++;
				// if(*lhs == '-') lhs++;
				int lhs_val = table[static_cast<unsigned char>(*lhs)];
				int rhs_val = table[static_cast<unsigned char>(*rhs)];

					if (lhs_val < rhs_val)
						return -1;
					else if (lhs_val > rhs_val)
						return 1;
			}

			if(lhs == a.end()){
				if(rhs == b.end()){
					return 0;
				}
				else return -1;
			}
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
		RankedString(std::string palavraIn) : palavra(palavraIn), repeticoes(1), customComparator(nullptr) {}
		RankedString(std::string palavraIn, CustomAlphaCmp* customCmp) : palavra(palavraIn), repeticoes(1), customComparator(customCmp) {}
		~RankedString() { customComparator = nullptr; }

		RankedString& operator=(const RankedString& novo) {
			palavra = novo.palavra;
			repeticoes = novo.repeticoes;
			customComparator = novo.customComparator;
			return *this;
		}
		bool operator==(const RankedString& outro) const {
			if(customComparator==nullptr) return palavra == outro.palavra;
			return (*customComparator)(this->palavra, outro.palavra) == 0;
		}
		bool operator!=(const RankedString& outro) const {
			return palavra != outro.palavra;
		}
		bool operator<(const RankedString& outro) const {
			if(customComparator==nullptr) return this->palavra < outro.palavra;
			return (*customComparator)(this->palavra, outro.palavra) == -1;
		}
		bool operator>(const RankedString& outro) const {
			if(customComparator==nullptr) return this->palavra > outro.palavra;
			return (*customComparator)(this->palavra, outro.palavra) == 1;
		}
		bool operator>=(const RankedString& outro) const {
			return (*this == outro || *this > outro);
		}
		bool operator<=(const RankedString& outro) const {
			return (*this == outro || *this < outro);
		}
		friend std::ostream &operator<<(std::ostream& output, const RankedString& rStr){
			output << rStr.palavra << " " << rStr.repeticoes;
			return output;
		}

		std::string getPalavra() { return palavra; }
		int getRepeticoes() { return repeticoes; }
		void setOrder(CustomAlphaCmp* customCmp) { customComparator = customCmp; }
		void increment() { repeticoes++; }
};

#endif