#include "RankedString.hpp"

// Custom Compare Class constructor
CustomAlphaCmp::CustomAlphaCmp(const std::string& alpha){
	for(int i=0; i<(1 << (CHAR_BIT - 1)); i++){ table[i] = i; }

	bool inputChars[26];

	int value = 'a';

	for (auto x : alpha){
		table[ static_cast<unsigned char>(x) ] = value++;

		if(x >= 'a' && x <= 'z'){
			inputChars[ static_cast<unsigned char>(x) - 97 ] = 1;
			table[ static_cast<unsigned char>(x) - 32 ] = value;
		}
		else if(x >= 'A' && x <= 'Z'){
			inputChars[ static_cast<unsigned char>(x) - 65 ] = 1;
			table[ static_cast<unsigned char>(x) + 32 ] = value;
		}
	}

	for(int i=0; i<26; i++){
		if(!inputChars[i])
			table[i] = value++;
	}
}

// Custom Compare function
int CustomAlphaCmp::operator()(const std::string& a, const std::string& b){
	auto lhs = a.begin();
	auto rhs = b.begin();

	for (; lhs != a.end() && rhs != b.end(); ++lhs,++rhs){
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

// RANKEDSTRING OPERATOR OVERLOADS

RankedString& RankedString::operator=(const RankedString& novo) {
	palavra = novo.palavra;
	repeticoes = novo.repeticoes;
	customComparator = novo.customComparator;
	return *this;
}

bool RankedString::operator==(const RankedString& outro) const {
	if(customComparator==nullptr) return palavra == outro.palavra;
	return (*customComparator)(this->palavra, outro.palavra) == 0;
}

bool RankedString::operator!=(const RankedString& outro) const {
	return palavra != outro.palavra;
}

bool RankedString::operator<(const RankedString& outro) const {
	if(customComparator==nullptr) return this->palavra < outro.palavra;
	return (*customComparator)(this->palavra, outro.palavra) == -1;
}

bool RankedString::operator>(const RankedString& outro) const {
	if(customComparator==nullptr) return this->palavra > outro.palavra;
	return (*customComparator)(this->palavra, outro.palavra) == 1;
}

bool RankedString::operator>=(const RankedString& outro) const {
	return (*this == outro || *this > outro);
}

bool RankedString::operator<=(const RankedString& outro) const {
	return (*this == outro || *this < outro);
}

std::ostream &operator<<(std::ostream& output, const RankedString& rStr){
	output << rStr.palavra << " " << rStr.repeticoes;
	return output;
}