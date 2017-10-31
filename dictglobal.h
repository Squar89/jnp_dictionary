/**
 * \authors Rafał Banaś, Jakub Wróblewski
 */
#ifndef JNP_DICTIONARY_DICTGLOBAL_H
#define JNP_DICTIONARY_DICTGLOBAL_H

#include <stddef.h>

#ifdef __cplusplus
namespace jnp1 {
    extern "C" {
#endif
        /**
         * Maximum size of global dictionary
         */
        extern const size_t MAX_GLOBAL_DICT_SIZE;

        /**
         * Returns id of global dictionary
         * @return global dictionary id
         */
        unsigned long dict_global();
#ifdef __cplusplus
    }
}
#endif

#endif //JNP_DICTIONARY_DICTGLOBAL_H
