#include <iostream>
#include <cassert>
#include "dict.h"

using namespace jnp1;

int main() {

    unsigned long id1 = dict_new();
    dict_insert(id1, "key", "value");
    const char* v = dict_find(id1, "key");
    assert(std::string(v) == "value");
    dict_delete(id1);
    assert(dict_size(id1) == 0);

}