#ifndef CRYPTO_H_INCLUDED
#define CRYPTO_H_INCLUDED

#include <map>
#include <vector>

typedef std::map<char, int> imap_t;
typedef std::vector<char> charVec;

char toBin(const char &);
char toChar(const char &);
std::vector<char> charwiseXor(const std::vector<char> &, const char &);
std::vector<char> frequencyVector(const std::vector<char> &);
int frequencyScoring(const charVec &);
std::vector<char> hex_string_to_char_vector(const char*);
void print_vector(const std::vector<char> &);
std::string vector_to_string(const std::vector<char> &);

#endif // CRYPTO_H_INCLUDED
