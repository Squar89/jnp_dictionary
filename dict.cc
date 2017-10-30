/**
 * \authors Rafał Banaś, Jakub Wróblewski
 */
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cassert>
#include "dict.h"
#include "dictglobal.h"

#ifndef DNDEBUG
const bool DEBUG = true;
#else
const bool DEBUG = false;
#endif

static const unsigned long GLOBAL_ID = dict_global();

using dictionary_t = std::unordered_map<std::string, std::string>;

static std::unordered_map<unsigned long, dictionary_t> &dictionaries() {
    static auto *_dictionaries = new std::unordered_map<unsigned long, dictionary_t>();
    assert(_dictionaries != nullptr);
    return *_dictionaries;
};

static unsigned long &next_id() {
    static auto *id = new unsigned long(0);
    assert(id != nullptr);
    return *id;
}

static bool dict_is_global(unsigned long id) {
    return id == GLOBAL_ID;
}

static bool dict_exists(unsigned long id) {
    return dictionaries().count(id) > 0;
}

static const char *string_or_null(const char *str) {
    return (str == nullptr) ? "NULLPTR" : str;
}

static void dict_new_debug(unsigned long created_id) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "dict_new()" << std::endl << "dict_new: dict " << created_id << " created" << std::endl;
}

unsigned long dict_new() {
    dictionaries().emplace(next_id(), dictionary_t());
    dict_new_debug(next_id());
    return next_id()++;
}

static void dict_delete_debug(unsigned long id, bool existed, bool is_global) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "dict_delete(" << id << ")" << std::endl;
    if (is_global) {
        std::cerr << "dict_delete: attempt to delete global dict" << std::endl;
    } else if (existed) {
        std::cerr << "dict_delete: dict " << id << " deleted" << std::endl;
    } else {
        std::cerr << "dict_delete: dict " << id << " does not exist" << std::endl;
    }
}

void dict_delete(unsigned long id) {
    bool is_global = dict_is_global(id);
    bool exists = dict_exists(id);
    if (is_global && exists) {
        dictionaries().erase(id);
    }
    dict_delete_debug(id, exists, is_global);
}

static void dict_size_debug(bool exists, size_t size, unsigned long id) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "dict_size(" << id << ")" << std::endl;
    if (exists) {
        std::cerr << "dict_size: dict " << id << " contains " << size << " element(s)" << std::endl;
    } else {
        std::cerr << "dict_size: dict " << id << " does not exist" << std::endl;
    }
}

size_t dict_size(unsigned long id) {
    bool exists = dict_exists(id);
    size_t size;
    if (exists) {
        size = dictionaries()[id].size();
    } else {
        size = 0;
    }
    dict_size_debug(exists, size, id);
    return size;
}

static bool dict_global_insert(unsigned long id, const char *key, const char *value) {
    if (dict_size(id) < MAX_GLOBAL_DICT_SIZE || dictionaries()[id].count(key) > 0) {
        dictionaries()[id][std::string(key)] = std::string(value);
        return false;
    } else {
        return true;
    }
}

static void dict_insert_debug(unsigned long id,
                              const char *key,
                              const char *value,
                              bool exists,
                              bool overflow,
                              bool null_pointers) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "dict_insert(" << id << ", \"" << string_or_null(key) << "\", \"" << string_or_null(value) << "\")"
              << std::endl;
    if (!exists) {
        std::cerr << "dict_insert: dict " << id << " does not exist" << std::endl;
        return;
    }
    if (null_pointers) {
        std::cerr << "dict_insert: null pointers" << std::endl;
    } else {
        if (overflow) {
            std::cerr << "dict_insert: cannot insert to global dictionary over maximum size";
        } else {
            std::cerr << "dict_insert: inserted pair (\"" << string_or_null(key) << "\", \""
                      << string_or_null(value) << "\") into dict " << id << std::endl;
        }
    }
}

void dict_insert(unsigned long id, const char *key, const char *value) {
    bool null_pointers = (key == nullptr) || (value == nullptr);
    bool exists = dict_exists(id);
    bool is_global = dict_is_global(id);
    bool global_overflow = false;
    if (exists && !null_pointers) {
        if (is_global) {
            global_overflow = dict_global_insert(id, key, value);
        } else {
            dictionaries()[id][std::string(key)] = std::string(value);
        }
    }
    dict_insert_debug(id, key, value, exists, global_overflow, null_pointers);
}

static void dict_remove_debug(unsigned long id, const char *key, bool exists, bool contains, bool null_pointer) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "dict_remove(" << id << ", \"" << string_or_null(key) << "\")" << std::endl;
    if (!exists) {
        std::cerr << "dict_remove: dict " << id << " does not exist" << std::endl;
    }
    if (!null_pointer) {
        if (contains) {
            std::cerr << "dict_remove: removed key \"" << string_or_null(key) << "\" from dict " << id << std::endl;
        } else {
            std::cerr << "dict_remove: dict " << id << " does not contain key \"" << string_or_null(key) << "\""
                      << std::endl;
        }
    } else {
        std::cerr << "dict_remove:  null pointer" << std::endl;
    }
}

void dict_remove(unsigned long id, const char *key) {
    bool exists = dict_exists(id);
    bool contains = false;
    bool null_pointer = key == nullptr;
    if (exists) {
        contains = dictionaries()[id].erase(std::string(key)) > 0;
    }
    dict_remove_debug(id, key, exists, contains, null_pointer);
}

static void dict_find_debug(unsigned long id,
                            const char *key,
                            bool null_pointer,
                            bool has_key,
                            bool global_has_key,
                            const char *value) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "dict_find(" << id << ", \"" << string_or_null(key) << "\")" << std::endl;
    if (null_pointer) {
        std::cerr << "dict_find: null pointer" << std::endl;
        return;
    }
    if (value == nullptr) {
        std::cerr << "dict_find: key not found in dict with given id nor in the global dict" << std::endl;
        return;
    }
    if (has_key) {
        std::cerr << "dict_find: found value \"" << string_or_null(value) << "\" for key \""
                  << string_or_null(key) << "\" in dict" << id << std::endl;
        return;
    }
    if (global_has_key) {
        std::cerr << "dict_find: key \"" << string_or_null(key) << "\" not found in dict " << id << ". Value \""
                  << string_or_null(value) << "\" taken from the global dict" << std::endl;
        return;
    }
}

const char *dict_find(unsigned long id, const char *key) {
    bool exists = dict_exists(id);
    bool null_pointer = key == nullptr;
    bool has_key = false;
    bool global_has_key = false;
    const char *value = nullptr;
    global_has_key = dictionaries()[GLOBAL_ID].count(key) > 0;
    if (!null_pointer) {
        value = (global_has_key) ? dictionaries()[GLOBAL_ID][key].c_str() : value;
        if (exists) {
            has_key = dictionaries()[id].count(key) > 0;
            value = (has_key) ? dictionaries()[id][key].c_str() : value;
        }
    }
    dict_find_debug(id, key, null_pointer, has_key, global_has_key, value);
    return value;
}

static void dict_clear_debug(unsigned long id, bool exists) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "dict_clear(" << id << ")" << std::endl;
    if (!exists) {
        std::cerr << "dict_clear: dict " << id << " does not exist" << std::endl;
    }
    std::cerr << "dict_clear: cleared dict " << id << std::endl;
}

void dict_clear(unsigned long id) {
    bool exists = dict_exists(id);
    dict_clear_debug(id, exists);
    if (exists) {
        dictionaries()[id].clear();
    }
}

static void dict_copy_debug(unsigned long src_id, unsigned long dst_id, bool src_exists, bool dst_exists) {
    if (!DEBUG) {
        return;
    }
    std::cerr << "dict_copy(" << src_id << ", " << dst_id << ")" << std::endl;
    if (!src_exists) {
        std::cerr << "dict_copy: source dict " << src_id << " does not exist" << std::endl;
    }
    if (!dst_exists) {
        std::cerr << "dict_copy: destination dict " << dst_id << " does not exist" << std::endl;
    }
    if (src_exists && dst_exists) {
        std::cerr << "dict_copy: copied pairs from dict " << src_id << " to dict " << dst_id << std::endl;
    }
}

void dict_copy(unsigned long src_id, unsigned long dst_id) {
    bool src_exists = dict_exists(src_id);
    bool dst_exists = dict_exists(dst_id);

    if (src_exists && dst_exists) {
        for (auto &key_value_pair : dictionaries()[src_id]) {
            if (dict_is_global(dst_id) &&
                (dict_size(dst_id) < MAX_GLOBAL_DICT_SIZE || dictionaries()[dst_id].count(key_value_pair.first) > 0)) {
                dictionaries()[dst_id][key_value_pair.first] = key_value_pair.second;
            } else {
                dictionaries()[dst_id][key_value_pair.first] = key_value_pair.second;
            }

        }
    }
    dict_copy_debug(src_id, dst_id, src_exists, dst_exists);
}

