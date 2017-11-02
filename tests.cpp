#include "cdict"
#include "cdictglobal"


int main() {
    unsigned long id0 = jnp1::dict_global();
    unsigned long id = jnp1::dict_new();
    jnp1::dict_insert(id, "k1", "v");
    jnp1::dict_insert(id, "k2", "v");
    jnp1::dict_insert(id, "k3", "v");
    jnp1::dict_insert(id, "k4", "v");
    jnp1::dict_insert(id, "k5", "v");
    jnp1::dict_insert(id, "k6", "v");
    jnp1::dict_insert(id, "k7", "v");
    jnp1::dict_copy(id, id0);
}
