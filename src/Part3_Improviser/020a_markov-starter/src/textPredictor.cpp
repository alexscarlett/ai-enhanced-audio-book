#include "../../MarkovModelCPP/src/MarkovManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

// Function to clean a word (remove punctuation and convert to lowercase)
std::string cleanWord(const std::string &word)
{
    std::string cleaned;
    for (char c : word)
    {
        if (std::isalnum(c))
        {
            // cleaned += std::tolower(c);
            cleaned += c;
        }
    }
    return cleaned;
}

// Function to read file and extract words
std::vector<std::string> extractWords(const std::string &filename)
{
    std::vector<std::string> words;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return words;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word)
        {
            std::string cleanedWord = cleanWord(word);
            if (!cleanedWord.empty())
            {
                words.push_back(cleanedWord);
            }
        }
    }

    file.close();
    return words;
}

int main(int argc, char *argv[])
{
    MarkovManager mm{};
    std::string filename = "./text.txt";
    std::vector<std::string> words = extractWords(filename);

    if (words.empty())
    {
        std::cout << "No words found or file could not be read." << std::endl;
        return 1;
    }

    std::cout << "Found " << words.size() << " words:" << std::endl;
    // std::cout << "[";

    // for (size_t i = 0; i < words.size(); ++i)
    // {
    //     std::cout << "\"" << words[i] << "\"";
    //     if (i < words.size() - 1)
    //     {
    //         std::cout << ", ";
    //     }
    // }

    // std::cout << "]" << std::endl;

    for (const std::string &word : words)
    {
        // std::cout << word << std::endl;
        mm.putEvent(word);
    }

    for (auto i = 0; i < 500; ++i)
    {
        state_single next = mm.getEvent();
        int order = mm.getOrderOfLastEvent();
        // std::cout << "Next state " << next << " order " << order << std::endl;
        std::cout << next << " ";
    }

    return 0;
}