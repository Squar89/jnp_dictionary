#include <iostream>
#include <cassert>
#include "cdict"
#include "cdictglobal"

static int streq(const char* s1, const char* s2, size_t len) {
    if (s1 == s2)
        return 1;

    if (s1 == NULL || s2 == NULL)
        return 0;

    return strncmp(s1, s2, len) == 0;
}

int main() {
    unsigned long id0, id1, id2, id3, id4, id5;

    id0 = jnp1::dict_global();
    assert(id0 == 0);

    /* dict_new i dict_delete (ostatnie mogą też sprawdzać inne funkcje) */
    id1 = jnp1::dict_new();
    assert(id1 == 1);

    id2 = jnp1::dict_new();
    assert(id2 == 2);

    jnp1::dict_delete(id1);
    id1 = jnp1::dict_new();
    
    jnp1::dict_delete(id2);
    jnp1::dict_delete(id2);
    id2 = jnp1::dict_new();
    
    id3 = jnp1::dict_new();
    
    jnp1::dict_delete(id3);
    assert(jnp1::dict_size(id3) == 0);
    jnp1::dict_insert(id3, "key", "value");
    assert(jnp1::dict_size(id3) == 0);
    jnp1::dict_remove(id3, "key");
    assert(jnp1::dict_size(id3) == 0);
    jnp1::dict_clear(id3);
    jnp1::dict_copy(id3, id3);
    assert(jnp1::dict_size(id3) == 0);

    jnp1::dict_delete(id0);

    jnp1::dict_delete(id1);
    jnp1::dict_delete(id2);
    /* */

    /* dict_size, dict_insert i dict_remove */
    assert(jnp1::dict_size(id1) == 0);
    id1 = jnp1::dict_new();
    assert(jnp1::dict_size(id1) == 0);
    jnp1::dict_insert(id1, "key1", "value1");
    assert(jnp1::dict_size(id1) == 1);
    jnp1::dict_insert(id1, "key2", "value2");
    assert(jnp1::dict_size(id1) == 2);
    jnp1::dict_insert(id1, "key1", "value2");
    assert(jnp1::dict_size(id1) == 2);
    jnp1::dict_remove(id1, "key1");
    assert(jnp1::dict_size(id1) == 1);
    jnp1::dict_insert(id1, "key1", "value2");
    assert(jnp1::dict_size(id1) == 2);
    jnp1::dict_remove(id1, "key1");
    assert(jnp1::dict_size(id1) == 1);
    jnp1::dict_remove(id1, "key1");
    assert(jnp1::dict_size(id1) == 1);
    jnp1::dict_remove(id1, "key3");
    assert(jnp1::dict_size(id1) == 1);

    assert(jnp1::dict_size(10) == 0);

    id2 = jnp1::dict_new();
    assert(jnp1::dict_size(id2) == 0);
    jnp1::dict_insert(id2, "nullptr", "nullptr");
    assert(jnp1::dict_size(id2) == 1);
    jnp1::dict_insert(id2, "nullptr", "");
    assert(jnp1::dict_size(id2) == 1);
    jnp1::dict_insert(id2, "", "");
    assert(jnp1::dict_size(id2) == 2);
    jnp1::dict_remove(id2, "nullptr");
    assert(jnp1::dict_size(id2) == 1);
    jnp1::dict_remove(id2, "");
    assert(jnp1::dict_size(id2) == 0);

    assert(jnp1::dict_size(id3) == 0);
    jnp1::dict_insert(3, "key", "value");
    assert(jnp1::dict_size(id3) == 0);

    id3 = jnp1::dict_new();
    assert(jnp1::dict_size(id3) == 0);
    jnp1::dict_remove(id3, "key");
    assert(jnp1::dict_size(id3) == 0);

    assert(jnp1::dict_size(id0) == 0);
    jnp1::dict_insert(jnp1::dict_global(), "global_key", "global_value");
    assert(jnp1::dict_size(id0) == 1);
    jnp1::dict_remove(jnp1::dict_global(), "global_key");
    assert(jnp1::dict_size(id0) == 0);
    jnp1::dict_remove(jnp1::dict_global(), "global_key");
    assert(jnp1::dict_size(id0) == 0);

    jnp1::dict_insert(jnp1::dict_global(), "global_key2", "global_value2");
    assert(jnp1::dict_size(id0) == 1);
    jnp1::dict_remove(10, "global_key2");
    assert(jnp1::dict_size(jnp1::dict_global()) == 1);

    id4 = jnp1::dict_new();
    assert(jnp1::dict_size(id4) == 0);
    jnp1::dict_insert(id4, NULL, NULL);
    assert(jnp1::dict_size(id4) == 0);
    jnp1::dict_insert(id4, "key", NULL);
    assert(jnp1::dict_size(id4) == 0);
    jnp1::dict_insert(id4, NULL, "value");
    assert(jnp1::dict_size(id4) == 0);

    jnp1::dict_remove(id4, NULL);
    assert(jnp1::dict_size(id4) == 0);

    assert(jnp1::dict_size(jnp1::dict_global()) == 0);
    jnp1::dict_insert(jnp1::dict_global(), "global_key", "global_value");
    assert(jnp1::dict_size(jnp1::dict_global()) == 1);
    for (int i = 1; i < 42; i++) {
        char* key = "key";
        char* value = "value";
        char* integer_string = NULL;
        sprintf(integer_string, "%d", i);
        strcat(key, integer_string);
        strcat(value, integer_string);
        jnp1::dict_insert(jnp1::dict_global(), key, value);
    }
    assert(jnp1::dict_size(jnp1::dict_global()) == 42);

    jnp1::dict_insert(id0, "new_key", "new_value");
    assert(jnp1::dict_size(id0) == 42);
    jnp1::dict_insert(id0, "global_key", "new_value");
    assert(jnp1::dict_size(id0) == 42);
    jnp1::dict_remove(id0, "new_key");
    assert(jnp1::dict_size(id0) == 42);
    jnp1::dict_remove(id0, "global_key");
    assert(jnp1::dict_size(id0) == 41);
    jnp1::dict_insert(id0, "global_key", "global_value");
    assert(jnp1::dict_size(id0) == 42);

    jnp1::dict_delete(id1);
    jnp1::dict_delete(id2);
    jnp1::dict_delete(id3);
    jnp1::dict_delete(id4);
    /* */

    /* dict_find */
    id1 = jnp1::dict_new();
    jnp1::dict_insert(id1, "key0", "local_value");
    jnp1::dict_insert(id1, "key", "value");
    assert(jnp1::dict_size(id1) == 2);

    assert(streq(jnp1::dict_find(id1, "key0"), "local_value", 12));
    assert(streq(jnp1::dict_find(id1, "key"), "value", 6));
    assert(streq(jnp1::dict_find(id1, "key1"), "value1", 7));
    assert(jnp1::dict_find(id1, "some_key") == NULL);

    assert(streq(jnp1::dict_find(id2, "global_key"), "global_value", 13));
    assert(jnp1::dict_find(id2, "some_key") == NULL);

    jnp1::dict_insert(id1, "key", "something");
    assert(jnp1::dict_size(id1) == 2);
    assert(streq(jnp1::dict_find(id1, "key"), "something", 10));

    assert(jnp1::dict_size(jnp1::dict_global()) == 42);
    assert(streq(jnp1::dict_find(id0, "global_key"), "global_value", 13));
    jnp1::dict_insert(jnp1::dict_global(), "global_key", "new_value");
    assert(jnp1::dict_size(jnp1::dict_global()) == 42);
    assert(streq(jnp1::dict_find(id0, "global_key"), "new_value", 10));

    assert(jnp1::dict_find(id0, "some_key") == NULL);

    jnp1::dict_delete(id1);
    /* */

    /* dict_clear */
    id1 = jnp1::dict_new();
    jnp1::dict_insert(id1, "key1", "value1");
    jnp1::dict_insert(id1, "key2", "value2");
    jnp1::dict_insert(id1, "key3", "value3");
    assert(jnp1::dict_size(id1) == 3);
    jnp1::dict_clear(id1);
    assert(jnp1::dict_size(id1) == 0);
    jnp1::dict_clear(id0);
    assert(jnp1::dict_size(id0) == 0);

    jnp1::dict_delete(id1);
    /* */

    /* dict_copy */
    id1 = jnp1::dict_new();
    jnp1::dict_insert(id1, "key1", "value1");
    assert(jnp1::dict_size(id1) == 1);
    id2 = jnp1::dict_new();
    jnp1::dict_insert(id2, "key2", "value2");
    assert(jnp1::dict_size(id2) == 1);
    id3 = jnp1::dict_new();
    jnp1::dict_insert(id3, "key1", "value3");
    jnp1::dict_insert(id3, "key3", "value3");
    assert(jnp1::dict_size(id3) == 2);

    jnp1::dict_copy(id2, id1);
    assert(jnp1::dict_size(id1) == 2);
    assert(streq(jnp1::dict_find(id1, "key2"), "value2", 7));

    jnp1::dict_copy(id3, id1);
    assert(jnp1::dict_size(id1) == 3);
    assert(streq(jnp1::dict_find(id1, "key1"), "value3", 7));
    assert(streq(jnp1::dict_find(id1, "key3"), "value3", 7));

    jnp1::dict_copy(id2, id1);
    assert(jnp1::dict_size(id1) == 3);
    assert(streq(jnp1::dict_find(id1, "key2"), "value2", 7));

    jnp1::dict_clear(id3);
    assert(jnp1::dict_size(id3) == 0);
    jnp1::dict_copy(id3, id2);
    assert(jnp1::dict_size(id2) == 1);
    assert(jnp1::dict_size(id3) == 0);

    id4 = jnp1::dict_new();
    assert(jnp1::dict_size(id4) == 0);

    id5 = jnp1::dict_new();
    assert(jnp1::dict_size(id5) == 0);

    jnp1::dict_delete(id3);
    assert(jnp1::dict_size(id3) == 0);

    jnp1::dict_copy(id3, id4);
    assert(jnp1::dict_size(id3) == 0);
    assert(jnp1::dict_size(id4) == 0);

    jnp1::dict_copy(id4, id3);
    assert(jnp1::dict_size(id3) == 0);
    assert(jnp1::dict_size(id4) == 0);

    jnp1::dict_copy(id4, id5);
    assert(jnp1::dict_size(id4) == 0);
    assert(jnp1::dict_size(id5) == 0);

    jnp1::dict_delete(id4);
    jnp1::dict_delete(id5);

    jnp1::dict_copy(id1, id1);
    assert(jnp1::dict_size(id1) == 3);

    assert(jnp1::dict_size(jnp1::dict_global()) == 42);
    jnp1::dict_remove(id0, "key2");
    assert(jnp1::dict_find(id0, "key2") == NULL);
    assert(jnp1::dict_size(jnp1::dict_global()) == 41);
    jnp1::dict_copy(id2, id0);
    assert(jnp1::dict_size(jnp1::dict_global()) == 42);
    assert(streq(jnp1::dict_find(id0, "key2"), "value2", 7));

    id3 = jnp1::dict_new();
    assert(jnp1::dict_size(id3) == 0);
    jnp1::dict_insert(id3, "some_key2", "some_value2");
    assert(jnp1::dict_size(id3) == 1);
    jnp1::dict_copy(id3, id0);
    assert(jnp1::dict_size(jnp1::dict_global()) == 42);
    assert(jnp1::dict_find(id0, "some_key2") == NULL);

    jnp1::dict_remove(id0, "key2");
    assert(jnp1::dict_find(id0, "key2") == NULL);
    assert(jnp1::dict_size(jnp1::dict_global()) == 41);
    jnp1::dict_copy(id1, id0);
    assert(jnp1::dict_size(jnp1::dict_global()) == 42);
    assert(streq(jnp1::dict_find(id0, "key2"), "value2", 7));
    assert(streq(jnp1::dict_find(id0, "key1"), "value3", 7));

    jnp1::dict_clear(id0);
    jnp1::dict_delete(id1);
    jnp1::dict_delete(id2);
    jnp1::dict_delete(id3);
    /* */
}