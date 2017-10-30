/**
 * \authors Rafał Banaś, Jakub Wróblewski
 */
#ifndef JNP_DICTIONARY_DICTGLOBAL_H
#define JNP_DICTIONARY_DICTGLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif
    
    #include <cstddef>

    /**
     * Maximum size of global dictionary
     */
    const size_t MAX_GLOBAL_DICT_SIZE = 42;

    /**
     * Returns id of global dictionary
     * @return global dictionary id
     */
    unsigned long dict_global();

#ifdef __cplusplus
}
#endif

#endif //JNP_DICTIONARY_DICTGLOBAL_H
