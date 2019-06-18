#ifndef ENDECRYPT_H
#define ENDECRYPT_H

char *caesar_encrypt(char *message_to_encrypt, void *shift);
char *caesar_decrypt(char *message_to_decrypt, void *shift);
char *polyalphabetic_encrypt(char *message_to_encrypt, void *key_string);
char **combine_strings(char **messages, int n_messages, int grouping, char *salt);



#endif

