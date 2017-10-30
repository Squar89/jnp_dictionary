/**
 * \authors Rafał Banaś, Jakub Wróblewski
 */
#ifndef JNP_DICTIONARY_DICTGLOBAL_H
#define JNP_DICTIONARY_DICTGLOBAL_H

#include <cstddef>

extern "C" {
    /**
     * Maximum size of global dictionary
     */
    const size_t MAX_GLOBAL_DICT_SIZE = 42;

    /**
     * Returns id of global dictionary
     * @return global dictionary id
     */
    unsigned long dict_global();
}

#endif //JNP_DICTIONARY_DICTGLOBAL_H
