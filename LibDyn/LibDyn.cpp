#include <windows.h>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <cctype>

extern "C" __declspec(dllexport) bool Search(const char* sentence, const char* wordsToFind) {
   
    std::string lowerSentence(sentence);
    std::transform(lowerSentence.begin(), lowerSentence.end(), lowerSentence.begin(), ::tolower);

    std::string lowerWordsToFind(wordsToFind);
    std::transform(lowerWordsToFind.begin(), lowerWordsToFind.end(), lowerWordsToFind.begin(), ::tolower);

    
    std::set<std::string> Searchword;
    std::string word;
    std::istringstream iss(lowerWordsToFind);
    while (std::getline(iss, word, ' ')) {
        Searchword.insert(word);
    }

    for (const auto& word : Searchword) {
        if (lowerSentence.find(word) == std::string::npos) {
            return false;
        }
    }

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

