
#include <stdio.h>
#include <stdlib.h>
#include "libio.h"


char* load_file(char* const filename) {
	
	printf("Opening %s...\n", filename);
	long unsigned int buf_inc = BUFFER; // Buffer increment.
	long unsigned int idx = 0; // Index counter for data array.
	// File content will be stored in this array.
	char* data = (char*) malloc (sizeof(char) * buf_inc);
	char line[BUFFER]; // Char array of BUFFER size to store file lines.
	FILE* FHIN = fopen(filename, "r"); // File handler.

	while (fgets(line, BUFFER, FHIN)) {

		// Iterates for every line extracted from file
		// until a "END_OF_CHR_ARRAY"  is found.
		for (int i = 0; i < BUFFER; i++) {

			if (idx == buf_inc) {
				// If buf_inc equals idx, increas buf_inc by BUFFER.
				buf_inc = buf_inc + BUFFER;
				// Increase dynamic memory of data array.
				data = realloc(data, sizeof(char) * buf_inc);
			}

			if (line[i] == END_OF_CHR_ARRAY) {
				break; // Breaks at end of line.
			}
			else {
				// Not at end of line. Allocates line[i]
				// to data[idx]. idx increments.
				data[idx] = line[i];
				idx++;
			}
		}
	}
	data[idx] = END_OF_CHR_ARRAY;
	return data;
}


/*###### Deployed strsplit ######*/

char** strsplit(char* string, char delimiter) {
	
	// Stacks the indexes where delimiter is
	// found in string.
	int* idxs;

	// Stores the index to iterate along idxs array.
	int i;

	// Stores the value which is before the current idxs[i].
	int j;

	// Stores the string length.
	int lstr;

	// Stores the int array length.
	int lidxs;

	// Stores the result of strsplit.
	// Who to malloc the first layer of pointers?
	char** results;

	idxs = which_idx(string, delimiter);
	lstr = len_str(string);
	lidxs = len_int_str(idxs);
	results = (char**) malloc (sizeof(char*) * lidxs+1);
	i = 0;
	j = 0;
	
	while (i < lidxs) {

		results[i] = subseq(string, j, idxs[i]);
		j = idxs[i]+1;
		i++;	

	}
	results[i] = subseq(string, j, lstr-1);
	results[i+1] = NULL;
	return results;
}

/*###### Deployed which_idx ######*/

int* which_idx(char* string, char delimiter) {

	int lstr; // Stores the length of string.
	int* idxs; // Indexes array.
	int i; // Iterates along string.
	int j; // Iterates along idxs.
	int buf_inc; // BUFFER increments.

	lstr = len_str(string);
	buf_inc = BUFFER;
	idxs = (int*) malloc (sizeof(int) * buf_inc);
	j = 0;
	for (i = 0; i < lstr; i++) {

		if (j == buf_inc) {

			buf_inc = buf_inc + BUFFER;
			idxs = realloc(idxs, sizeof(buf_inc));

		}

		if (string[i] == delimiter) {

			idxs[j] = i;
			j++;
		}
	}
	idxs[j] = END_OF_INT_ARRAY;
	return idxs;
	// remeber to free idxs.
}

/*###### Deployed len_str ######*/

int len_str(char* string) {

	int idx = 0;

	while (string[idx] != END_OF_CHR_ARRAY) {

		idx++;
	
	}
	return idx;
}

int len_int_str(int* string) {

	int idx = 0;

	while (string[idx] != END_OF_INT_ARRAY) {

		idx++;

	}
	return idx;
}

/*###### Deployed load_seqs ######*/

SEQ** load_seqs(char* data, char* mol, char delimiter) {
	
	SEQ* tmp; // Declaring temporary SEQ structure.
	SEQ** container; // Declaring container double pointer SEQ.
	char** lines; // To recieve split data.
	char* tmp_line; // temporary storage for each line in lines.
	int i; // To iterate along lines.
	int container_counter; // Counts the elements in container.
	
	container = (SEQ**) malloc (sizeof(SEQ*));
	container_counter = 0;
	tmp_line = NULL;
	lines = strsplit(data, delimiter);
	i = 0;

	while (lines[i] != NULL) {

		tmp_line = lines[i];
		if (tmp_line[0] == '>') {
			printf("Here is a sequence header!\n");
			container_counter++;
			container = realloc(container, sizeof(SEQ*) * container_counter);
			tmp = (SEQ*) malloc (sizeof(SEQ));
			container[container_counter-1] = tmp;
			container[container_counter-1] -> header = tmp_line;
			container[container_counter-1] -> type = mol;
			container[container_counter-1] -> sequence = "";
			container[container_counter-1] -> seq_len = 0;
			container[container_counter-1] -> hide = FALSE;
		}
		else {
			printf("Here is a sequence!\n");
			container[container_counter-1] -> sequence = \
				char_cat(container[container_counter-1] -> sequence, \
				tmp_line);
		}
		i++;

	}
	i = 0;
	container = realloc(container, sizeof(SEQ*) * (container_counter+1));
	container[container_counter] = NULL;
	while (container[i] != NULL) {

		container[i] -> seq_len = len_str(container[i] -> sequence);
		i++;

	}
	return container;

}

/*###### Deploying split_genome ######*/

SEQ** split_genome(SEQ** container, int size, int step) {

	// Coding...

}


/*###### Deployed print_seqs ######*/

void print_seqs(SEQ** container) {
	
	int i; // Iterator.

	i = 0;

	while (container[i] != NULL) {
		printf("%s\n%s - %d\n", container[i] -> header, \
					container[i] -> sequence, \
					container[i] -> hide);
		i++;
	}

}

/*###### Deploying write_seqs ######*/


	// HERE!


/*###### Deployed update_seqs ######*/

SEQ** hide_matched_seqs(SEQ** container, char** headers) {

	int i; // SEQ container counter.
	int j; // headers counter.
	
	i = 0;
	while (container[i] != NULL) {
		j = 0;
		while (headers[j] != NULL ) {

			if (cmp_str(headers[j], container[i] -> header)) {

				container[i] -> hide = TRUE;
				break;

			}
			j++;

		}
		i++;

	}
	return container;
}


/*###### Deployed subseq ######*/

char* subseq(char* array, int start, int end) {
	
	// Dynamic memory allocation for result array.
	// The length equals end - start.
	char* result =  (char*) malloc (sizeof(char) * end-start+1);
	// Index for result array. It initialises 0.
	int result_idx = 0;
	// for loop begins at 3 and ends at 8-1.
	for (int i = start; i < end; i++) {
		// If end of array is found, break.
		if (array[i] == END_OF_CHR_ARRAY) {
			result[result_idx] = END_OF_CHR_ARRAY;
			break;
		}
		else {
			result[result_idx] = array[i]; // copies every character of array.
			result_idx++;
		}

	}

	return result;

}

/*###### Deployed char_cat ######*/

char* char_cat(char* s1, char* s2) {

	int ls1; // Length of s1.
	int ls2; // Length of s2.
	char* join; // Stores the whole string.
	int i; // For loop iterator #1.
	int j; // Temporary index storage for join.

	j = 0;
	ls1 = len_str(s1);
	ls2 = len_str(s2);
	join = (char*) malloc (sizeof(char) * (ls1 + ls2));
	
	for (i = 0; i < ls1; i++) {

		join[j] = s1[i];
		j++;

	}

	for (i = 0; i < ls2; i++) {

		join[j] = s2[i];
		j++;

	}
	join[j] = END_OF_CHR_ARRAY;
	return join;
}


/*###### Deployed cmp_str ######*/

bool cmp_str(char* s1, char* s2) {

	int ls1; // Length of string 1.
	int ls2; // Length of string 2.
	int i; // Iterator.

	ls1 = len_str(s1);
	ls2 = len_str(s2);

	if (ls1 != ls2) {

		return FALSE;

	}
	else {

		for (i = 0; i < ls1; i++) {

			if (s1[i] != s2[i]) {

				return FALSE;

			}

		}

	}
	return TRUE;
}
