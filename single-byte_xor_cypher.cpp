#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <limits>

using std::cin, std::cout, std::string;

// Types definitions
typedef std::map<char, int> imap_t;
typedef std::vector<char> charVec;

// Functions declarations
char toBin(const char &);
char toChar(const char &);
void charwiseXor(const char*, char*, const char &);
charVec frequencyVector(const char*, const int &);
int frequencyScoring(const charVec &);

int main()
{
    const string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    int inputCharsCount = input.length()/2;
    char* inputChars = new char[inputCharsCount + 1];

    int i{0};
    for (; input[i]; i+=2) {
        inputChars[i/2] = (toBin(input[i]) << 4) + toBin(input[i+1]);
    }

    inputChars[i/2] = 0;
    cout << inputChars << '\n';

    char* output = new char[i/2 + 1];

    string optimalOutput;
    char optimalLetter;
    int minScore{std::numeric_limits<int>::max()};

    for (char c{32}; c < 127; ++c) {
        charwiseXor(inputChars, output, c);
        // cout << c << ": " << output << '\n';
        charVec freq = frequencyVector(output, inputCharsCount);
        int score = frequencyScoring(freq);
        if (score < minScore) {
            minScore = score;
            optimalOutput = string(output);
            optimalLetter = c;
        }
        // cout << "Score: " << score << '\n';
    }

    cout << "Decoded string: " << optimalOutput << '\n';
    cout << "Cipher letter: " << optimalLetter << '\n';
    cout << "Score: " << minScore << '\n';

    delete[] inputChars;
    delete[] output;

    return 0;
}

// Converts binary value to hex digit
// Does not check if input is valid hex character
char toBin(const char &c) {
    return (c-'0')*(c<='9')+(toupper(c)-'A'+10)*(c>'9');
}

// Converts char hex value to its binary value
// Does not check if input is valid
char toChar(const char &h) {
    return (h+'0')*(h<=9)+(h+'a'-10)*(h>9);
}

/* Calculating "charwise Xor" on input string
Input and output strings must be the same length
Input must be zero-terminated */
void charwiseXor(const char* input, char* output, const char &c) {
    int i{0};
    for (; input[i]; ++i) {
        output[i] = input[i] ^ c;
    }
    output[i] = 0;
}

// Assuming input is zero-terminated
charVec frequencyVector(const char* input, const int &inputLength) {

    imap_t freqMap;

    for (int i{0}; i < inputLength; ++i) {
        char key = tolower(input[i]);
        if (freqMap.count(key) == 0) {
            freqMap[key] = 1;
        }
        else {
            ++freqMap[key];
        }
    }

    charVec result;

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
    const string referenceFrequencyString = " etaoinsrhdlucmfywgpbvkxqjz";

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
