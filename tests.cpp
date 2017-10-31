#include <iostream>
#include <cassert>
#include "dict.h"

int main() {

    unsigned long id1 = jnp1::dict_new();
    jnp1::dict_insert(id1, "key", "value");
    const char* v = jnp1::dict_find(id1, "key");
    assert(std::string(v) == "value");
    jnp1::dict_delete(id1);
    assert(jnp1::dict_size(id1) == 0);

}