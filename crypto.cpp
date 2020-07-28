#include <iostream>
#include <string>
#include <cstring>
#include "crypto.h"


/* Calculating "charwise Xor" on input string
Input and output strings must be the same length
Input must be zero-terminated */
std::vector<char> charwiseXor(const std::vector<char> &input, const char &c) {
    std::vector<char> result;
    for (auto it = input.begin(); it != input.end(); ++it) {
        result.push_back(*it ^ c);
    }
    return result;
}

// Assuming input is zero-terminated
std::vector<char> frequencyVector(const std::vector<char> &input) {

    std::map<char, int> freqMap;

    for (auto it=input.begin(); it != input.end(); ++it) {
        char key = tolower(*it);
        if (freqMap.count(key) == 0) {
            freqMap[key] = 1;
        }
        else {
            ++freqMap[key];
        }
    }

    std::vector<char> result;

    while (!freqMap.empty()) {
        int maxValue{0};
        char keyMaxValue;
        for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
            if (it->second > maxValue) {
                maxValue = it->second;
                keyMaxValue = it->first;
            }
        }
        result.push_back(keyMaxValue);
        freqMap.erase(keyMaxValue);
    }

    return result;
}

/* Calculates frequency scoring basing on relative frequency of letters in string
in comparision with reference frequency of space and letters in English language*/
int frequencyScoring(const charVec &inputVector) {

    // Constant for relative letters frequency in English
    const std::string referenceFrequencyString = " etaoinsrhdlucmfywgpbvkxqjz";

    int score{0};
    for (auto it=inputVector.begin(); it!=inputVector.end(); ++it) {
        int currentIndex = it - inputVector.begin();
        int lastReferenceIndex = referenceFrequencyString.length();
        char currentChar = tolower(*it);
        size_t referenceIndex = referenceFrequencyString.find(currentChar);
        if (referenceIndex != std::string::npos) {
            score += (currentIndex - referenceIndex) * (currentIndex - referenceIndex);
        }
        else {
            score += (currentIndex - lastReferenceIndex) * (currentIndex - lastReferenceIndex);
        }
    }
    return score;
}

std::vector<char> hex_string_to_char_vector(const char* hex_input) {
    std::vector<char> result;
    int i{0};
    for (; hex_input[i]; i+=2) {
        char two_chars[3];
        memcpy(two_chars, &hex_input[i], 2);
        two_chars[2] = '\0';
        result.push_back(static_cast<char>(strtol(two_chars, nullptr, 16)));
    }
    return result;
}

void print_vector(const std::vector<char> & input) {
    for (auto it = input.begin(); it != input.end(); ++it) {
        std::cout << *it;
    }
}

std::string vector_to_string(const std::vector<char> &input) {
    std::string result;
    for (auto it = input.begin(); it != input.end(); ++it) {
        result += *it;
    }
    return result;
}
