#ifndef G58_DIVIDIR_E_CONQUISTAR_PA_26_2_WORDNORMALIZATION_HPP
#define G58_DIVIDIR_E_CONQUISTAR_PA_26_2_WORDNORMALIZATION_HPP

#include <cctype>
#include <string>

namespace modelo::nucleo {
    inline std::string normalizedWord(std::string word) {
        for (char& letter : word) letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
        return word;
    }
}

#endif //G58_DIVIDIR_E_CONQUISTAR_PA_26_2_WORDNORMALIZATION_HPP