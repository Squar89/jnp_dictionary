/**
 * \authors Rafał Banaś, Jakub Wróbelski
 */
#ifndef JNP_DICTIONARY_DICT_H
#define JNP_DICTIONARY_DICT_H

/**
 * Creates new dictionary
 * @return new dictionary id
 */
unsigned long dict_new();

/**
 * Removes dictionary with given id
 * @param id
 */
void dict_delete(unsigned long id);

/**
 * Returns size of dictionary with given id or 0 when such dictionary does not exist
 * @param id
 * @return dictionary size
 */
size_t dict_size(unsigned long id);

/**
 * Inserts pair (key, value) into dictionary with given id
 * @param id
 * @param key
 * @param value
 */
void dict_insert(unsigned long id, const char* key, const char* value);

/**
 * Removes key from dictionary with given id, or does nothing if dictionary does not contain such key
 * @param id
 * @param key
 */
void dict_remove(unsigned long id, const char* key);

/**
 * Returns value for given key in dict with id if it's found,
 * otherwise value from the global dictionary if it contains given key, or NULL in other case
 * @param id
 * @param key
 * @return value for given key
 */
const char* dict_find(unsigned long id, const char* key);

/**
 * Clears dictionary with given id
 * @param id
 */
void dict_clear(unsigned long id);

/**
 * Copies all pairs from dictionary with id src_id to dictionary with id dst_id
 * @param src_id
 * @param dst_id
 */
void dict_copy(unsigned long src_id, unsigned long dst_id);


#endif //JNP_DICTIONARY_DICT_H
