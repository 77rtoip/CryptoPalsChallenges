#include <iostream>
#include <map>
#include <cmath>

using std::cout, std::string;

typedef std::map<char, double> dmap_t;
typedef std::map<char, int> imap_t;

uint8_t toBin(uint8_t);
uint8_t toChar(uint8_t);
void charwiseXor(uint8_t*, uint8_t*, uint8_t);
dmap_t englishFrequencyMap();
dmap_t calculateFrequencies(uint8_t*);
double frequencyScoring(dmap_t);

int main()
{
    string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    int inputBytesCount = input.length()/2;
    uint8_t* inputChars = new uint8_t[inputBytesCount + 1];

    int i{0};
    for (; input[i]; i+=2) {
        inputChars[i/2] = (toBin(input[i]) << 4) + toBin(input[i+1]);
    }

    inputChars[i/2] = 0;
    cout << inputChars << '\n';

    uint8_t* output = new uint8_t[i/2 + 1];

    for (uint8_t c{32}; c < 127; ++c) {
        charwiseXor(inputChars, output, c);
        cout << c << ": " << output << '\n';
        dmap_t freq = calculateFrequencies(output);
        double score = frequencyScoring(freq);
        cout << "Score: " << score << '\n';
    }

    delete[] inputChars;
    delete[] output;

    return 0;
}

// Convert character to uint8_t (unsigned char) hex value
// Works properly only for valid hex characters as input
uint8_t toBin(uint8_t c) {
    return (c-'0')*(c<='9')+(toupper(c)-'A'+10)*(c>'9');
}

// Convert uint8_t hex value to unsigned char - for print
// No valid input checking
uint8_t toChar(uint8_t h) {
    return (h+'0')*(h<=9)+(h+'a'-10)*(h>9);
}

// Output string MUST be the same length as input,
// otherwise the result will be meaningless
void charwiseXor(uint8_t* input, uint8_t* output, uint8_t c) {
    int i{0};
    for (; input[i]; ++i) {
        output[i] = input[i] ^ c;
    }
    output[i] = 0;
}


// Creating frequency map for English language
dmap_t englishFrequencyMap() {
    dmap_t m;
    const double freqMap[] {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,\
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758,\
    0.978, 2.360, 0.150, 1.974, 0.074};
    char c{'a'};
    for (; c<='z'; ++c) {
        m[c] = freqMap[c-'a'];
    }
    return m;
}


dmap_t calculateFrequencies(uint8_t* input) { // input must be zero-terminated
    imap_t countMap;
    int i{0};
    for (; input[i]; ++i) {
        char key = tolower(input[i]);
        if (countMap.count(key) == 0) {
            countMap[key] = 1;
        }
        else {
            ++countMap[key];
        }
    }
    int inputLength = i;

    dmap_t outputMap;
    for (std::map<char, int>::iterator it=countMap.begin(); it!=countMap.end(); ++it) {
        outputMap[it->first] = double(double(it->second)/inputLength);
    }
    return outputMap;
}

double frequencyScoring(dmap_t inputFreq) {
    dmap_t referenceFrequencies = englishFrequencyMap();
    double score = 0.0;
    for (std::map<char, double>::iterator it=inputFreq.begin(); it!=inputFreq.end(); ++it) {
        double a = inputFreq[it->first];
        if (referenceFrequencies.count(it->first) >= 1) {
            double b = referenceFrequencies[it->first];
            score += (a-b)*(a-b);
        }
        else {
            score += a*a;
        }
    }
    return sqrt(score);
}
