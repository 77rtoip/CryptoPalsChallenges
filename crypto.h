#ifndef CRYPTO_H_INCLUDED
#define CRYPTO_H_INCLUDED

#include <map>
#include <vector>

std::vector<char> charwiseXor(const std::vector<char> &, const char &);
std::vector<char> frequencyVector(const std::vector<char> &);
int frequencyScoring(const std::vector<char> &);
std::vector<char> hex_string_to_char_vector(const char*);
std::string to_string(const std::vector<char> &);

#endif // CRYPTO_H_INCLUDED
