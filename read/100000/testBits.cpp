//----------LIBRARY----------
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>
#include <bitset>

using std::stringstream;
using std::max_element;
using std::min_element;
using std::accumulate;
using std::ifstream;
using std::getline;
using std::vector;
using std::string;
using std::bitset;
using std::pair;
using std::cout;

//----------HASH GENERATOR----------
string generateHash(string &str) {
    unsigned int hash[8] = {0};     // 8 elements - 64 symbols - 256 bits

    for(char c : str) {
        for(int i = 0; i < 8; i ++) {
            hash[i] += c * (i + 1); // multiplying the character's ASCII value with (i + 1) / hashing
        }
    }

    //----------CONVERSION TO HEX----------
    stringstream hashStream;
    hashStream << std::hex << std::setfill('0');
    for(int i = 0; i < 8; i ++) {
        hashStream << std::setw(8) << hash[i];
    }

    return hashStream.str();
}

double evaluateDifference(string &leftHash, string &rightHash) {
    int totalBits = leftHash.length() * 8;  // number of bits in the hash
    int differenceCount = 0;

    for (size_t i = 0; i < leftHash.length(); ++ i) {
        bitset<8> bits1(leftHash[i]);
        bitset<8> bits2(rightHash[i]);

        differenceCount += (bits1 ^ bits2).count();
    }

    double percentageDifference = (static_cast<double>(differenceCount) / totalBits) * 100.0;

    return percentageDifference;
}

int main() {
    vector<double> differences;
    string         line;

    ifstream inputFile("symbols.txt");
    while(getline(inputFile, line)) {
        size_t space = line.find(' ');

        if(space != string::npos) {
            string leftHash = line.substr(0, space),
                   rightHash = line.substr(space + 1);
            leftHash = generateHash(leftHash);
            rightHash = generateHash(rightHash);

            double percentageDifference = evaluateDifference(leftHash, rightHash);

            differences.push_back(percentageDifference);
        }
    }
    inputFile.close();

    //----------MIN, AVG, MAX CALCULATION----------
    double minDifference = *min_element(differences.begin(), differences.end());
    double maxDifference = *max_element(differences.begin(), differences.end());
    double avgDifference = accumulate(differences.begin(), differences.end(), 0.0) / differences.size();

    cout << "Bit-wise difference\n";
    cout << "Minimum Difference: " << minDifference << "%\n";
    cout << "Average Difference: " << avgDifference << "%\n";
    cout << "Maximum Difference: " << maxDifference << "%\n";

    return 0;
}