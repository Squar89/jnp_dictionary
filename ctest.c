#include <stdio.h>
#include "dict.h"


int main() {
    unsigned long id1 = dict_new();
    dict_insert(id1, "key1", "value1");
    const char* str = dict_find(id1, "key1");
    printf("%s", str);
}