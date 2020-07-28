#include <iostream>
#include <limits>
#include "crypto.h"

int main()
{
    const char* hex_input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    std::vector<char> char_input = hex_string_to_char_vector(hex_input);
    std::cout << "Encoded string: " << vector_to_string(char_input) << '\n';
    std::vector<char> optimalOutput;
    char optimalLetter;
    int minScore{std::numeric_limits<int>::max()};

    for (char c{0}; c < 127; ++c) {

        std::vector<char> output = charwiseXor(char_input, c);
        charVec freq = frequencyVector(output);
        int score = frequencyScoring(freq);
        if (score < minScore) {
            minScore = score;
            optimalOutput = output;
            optimalLetter = c;
        }

    }

    std::cout << "Decoded string: " << vector_to_string(optimalOutput) << '\n';
    std::cout << "Cipher letter: " << optimalLetter << '\n';
    std::cout << "Score: " << minScore << '\n';

    return 0;
}
