/**
 * \authors Rafał Banaś, Jakub Wróblewski
 */
#include "dictglobal.h"
#include "dict.h"

unsigned long dict_global() {
    static unsigned long global_id;
    static bool first_call = true;
    if (first_call) {
        first_call = false;
        global_id = dict_new();
    }
    return global_id;
}
