#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

struct FileType {
    std::string pronom;
    std::string fullName;
    std::string version;
};

// Custom comparison function
bool compareFileType(const FileType& a, const FileType& b) {
    std::string s1 = a.pronom;
    std::string s2 = b.pronom;
    // If size of numeric strings are same the put the lowest value first
    if (s1.size() == s2.size()) {
        return s1 < s2;
    }
        // If size is not same put the numeric string with fewer number of digits first
    else {
        return s1.size() < s2.size();
    }
}

int main(int argc, char** argv) {
    if(argc < 2){
        std::cerr << "Error: No argument for input filename" << std::endl;
        return 1;
    }
    std::string inputFilename = argv[1];
    std::string outputFilename = argc > 2 ? argv[2] : "output.txt";

    //Open inputFile
    std::fstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: File '" << inputFilename << "' not found" << std::endl;
        return 1;
    }
    //Open outputFile
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: File '" << outputFilename << "' could not be opened" << std::endl;
        return 1;
    }

    //loop through each line
    std::string line;
    std::vector<std::string> lines;
    std::cout << "Reading input file..." << std::endl;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    std::vector<FileType> fileTypes;

    //Close inputFile
    inputFile.close();
    for(auto l : lines){
        //Split line by comma
        std::string pronom = l.substr(0, l.find(','));
        l.erase(0, l.find(',') + 1);
        std::string fullName = l.substr(0, l.find(','));
        l.erase(0, l.find(',') + 1);
        std::string version = l.substr(0, l.find(','));
        fileTypes.push_back({pronom, fullName, version});
    }

    //Sort fileTypes by pronom
    std::sort(fileTypes.begin(), fileTypes.end(), compareFileType);

    std::cout << "Writing to output file..." << std::endl;
    //Print header
    outputFile << "switch(pronom){\n";
    outputFile << "case " << std::setw(10) << std::left << "\"\"";
    outputFile << ": output = " << std::setw(60) << std::left << "Empty" << "; break;\n";
    outputFile << "case " << std::setw(10) << std::left << "default";
    outputFile << ": output = " << std::setw(60) << std::left << "Unknown" << "; break;\n";

    for(auto filetype : fileTypes){
        //remove " from fullName and version
        filetype.fullName = filetype.fullName.substr(1, filetype.fullName.size() - 2);
        filetype.version = filetype.version.substr(1, filetype.version.size() - 2);
        std::string fileName = "\"" + filetype.fullName + " " + filetype.version + "\"";
        outputFile << "case " << std::setw(10) << std::left << filetype.pronom;
        outputFile << ": output = " << std::setw(60) << std::left << fileName << "; break;\n";
    }
    outputFile << "}\n";

    //Close outputFile
    outputFile.close();
    std::cout << "Output written to " << outputFilename << std::endl;
    return 0;
}
