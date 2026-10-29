#ifndef G58_DIVIDIR_E_CONQUISTAR_PA_26_2_FONEMAS_HPP
#define G58_DIVIDIR_E_CONQUISTAR_PA_26_2_FONEMAS_HPP

#include "modelo/nucleo/Phoneme.hpp"

using modelo::nucleo::Phoneme;

namespace fonemas {

    // Monta uma vogal
    inline Phoneme vogal(const std::string& symbol, int stress) {
        return {symbol, true, stress};
    }

    // Monta uma consoante. Consoante não tem tônica, stress = -1.
    inline Phoneme consoante(const std::string& symbol) {
        return {symbol, false, -1};
    }

    // Devolve só os símbolos
    static std::vector<std::string> simbolos(const std::vector<Phoneme>& fonemas) {
        std::vector<std::string> resultado;

        for (const Phoneme& fonema : fonemas) {
            resultado.push_back(fonema.symbol);
        }

        return resultado;
    }

}

#endif //G58_DIVIDIR_E_CONQUISTAR_PA_26_2_FONEMAS_HPP