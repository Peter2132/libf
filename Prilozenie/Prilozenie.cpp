#include <iostream>
#include <windows.h>
#include <string>
#include <set>
#include <algorithm>
#include <cctype>




int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    HINSTANCE hGetProcIDDLL = LoadLibraryA("LibDyn.dll");

    if (hGetProcIDDLL == nullptr) {
        std::cout << "Could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    typedef bool(*Searchwords)(const char*, const char*);
    Searchwords checkWordsAndSentence =
        (Searchwords)GetProcAddress(hGetProcIDDLL, "Searchwords");

    if (!checkWordsAndSentence) {
        std::cout << "Could not locate the function" << std::endl;
        FreeLibrary(hGetProcIDDLL);
        return EXIT_FAILURE;
    }

    std::string sentence, forwords;
    std::cout << "Введите слово или предложение: ";
    std::getline(std::cin, sentence);
    std::cout << "Введите слово или букву, которую хотите найти: ";
    std::getline(std::cin, forwords);

    bool result = checkWordsAndSentence(sentence.c_str(), forwords.c_str());
    std::cout << "Результат: " << (result ? "есть!" : "нету") << std::endl;

    FreeLibrary(hGetProcIDDLL);

    return EXIT_SUCCESS;
}

