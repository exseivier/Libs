#ifndef __LIBIO_H__
#define __LIBIO_H__

#define BUFFER 256
#define END_OF_INT_ARRAY -127
#define END_OF_CHR_ARRAY '\0'
#define TRUE 1
#define FALSE 0

/* 
 * This data structure holds a sequence from fasta format.
 * type holds the type of molecule. [DNA | RNA | AA].
 * header holds the head of the sequence.
 * sequence holds the nucleotide sequence.
 * link links to another sequence data structure.
 */
struct sequence {
	char* type;
	char* header;
	char* sequence;
	int seq_len;
};
typedef struct sequence SEQ;

/* load_seqs function.
 * Requires an array (data) with data to be
 * processed to a sequencae data structure.
 * mol is a character array with the name of the
 * molecule, it could be DNA, RNA or AA.
 */
SEQ** load_seqs(char* data, char* mol, char delimiter);

/* load_file function
 * This function reads the file line by
 * line and stores each line into array
 * data structure.
 * It requires the filename passed to it
 * as a char const array.
 */
char* load_file(char* const filename);

/* subseq function
 * This function takes an array and two
 * integers and returns the characters of
 * an the array delimited by the two integers.
 * Requires a char array and two integers a, b.
 */
char* subseq(char* array, int start, int end);

/* strsplit function
 * Splits a string of characters into substrings
 * using a character as delimiter.
 * Requires a pinter to an array (string). And
 * A char variable as delimiter (delimiter).
 * Example.
 * 	char str[] = "name=jhon";
 * 	char** substrings = strsplit(str, '=');
 * substrings has a double pinter to a 2D array
 * dynamically allocated in memory.
 */
char** strsplit(char* string, char delimiter);

/* which_idx function
 * Find the index numbers when a character match
 * is found into an array.
 * Requires a pointer to an array (string), and a character
 * used to search for it in the array (delimiter).
 * Example.
 * 	char str[] = "hello world!";
 * 	int* idx = which_idx(str, 'o');
 * 
 * Idx contains the index numbers where the character
 * 'o' is found. So if you print on screen idx you
 * gonna get the following.
 * #	[4, 7].
 */
int* which_idx(char* string, char delimiter);

/* len_str function
 * Calculates the length of a charcters string.
 * Returns an integer and requires a char pointer
 * to the array.
 */
int len_str(char* string);
int len_int_str(int* string);

/* char_cat function
 * Concatenates two char strings.
 * Require two pointers to char arrays.
 */
char* char_cat(char* s1, char* s2);

#endif
