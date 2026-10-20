cmake_minimum_required(VERSION 4.1)
project(G58_Dividir_e_Conquistar_PA_26_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(modelo)

add_executable(G58_Dividir_e_Conquistar_PA_26_2
        src/impl/AcousticTranslator.cpp
        include/AcousticTranslator.hpp
        src/impl/CmuDictionary.cpp
        include/CmuDictionary.hpp
        src/impl/DivideConquerFinder.cpp
        include/DivideConquerFinder.hpp
        modelo/IClosestPair.cpp
        include/IClosestPair.hpp
        modelo/IDictionaryLookUp.cpp
        include/IDictionaryLookUp.hpp
        modelo/IPhoneticConverter.cpp
        include/IPhoneticConverter.hpp
        include/Phoneme.hpp
        include/PhoneticPoint.hpp
        src/impl/RhymeEngine.cpp
        include/RhymeEngine.hpp
        include/RhymePair.hpp
        src/main.cpp
)
