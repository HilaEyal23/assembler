#include "utils.h"

const char base32[32] = {
        '!', '@', '#', '$', '%', '^', '&', '*',
        '<','>', 'a', 'b', 'c','d', 'e', 'f',
        'g','h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p','q', 'r', 's', 't', 'u', 'v'
};

char *create_file_name(char *original, int type)
{
    char *modified = (char *) malloc(strlen(original) + MAX_EXTENSION_LENGTH);
    if(modified == NULL)
    {
        fprintf(stderr, "Dynamic allocation error.");
        exit(1);
    }
    strcpy(modified, original);

    switch (type)
    {
        case FILE_INPUT:
            strcat(modified, ".as");
            break;

        case FILE_OBJECT:
            strcat(modified, ".ob");
            break;

        case FILE_ENTRY:
            strcat(modified, ".ent");
            break;

        case FILE_EXTERN:
            strcat(modified, ".ext");

    }
    return modified;
}

unsigned int extract_bits(unsigned int word, int start, int end)
{
    unsigned int result;
    int length = end - start + 1; /* Length of bit-sequence */
    unsigned int mask = (int) pow(2, length) - 1; /* Creating a '111...1' mask with above line's length */

    mask <<= start; /* Moving mask to place of extraction */
    result = word & mask; /* The bits are now in their original position, and the rest is 0's */
    result >>= start; /* Moving the sequence to LSB */
    return result;
}

char *convert_to_base_32(unsigned int num)
{
    char *base32_seq = (char *) malloc(BASE32_SEQUENCE_LENGTH);

    /* To convert from binary to base 32 we can just take the 5 right binary digits and 5 left */
    base32_seq[0] = base32[extract_bits(num, 5, 9)];
    base32_seq[1] = base32[extract_bits(num, 0, 4)];
    base32_seq[2] = '\0';
    return base32_seq;
}


unsigned int insert_are(unsigned int info, int are)
{
    return (info << BITS_IN_ARE) | are;
}

