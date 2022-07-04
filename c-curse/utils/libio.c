
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

	int lstr;
	int* idxs;
	int i; // Iterates along string
	int j; // Iterates along idxs
	int buf_inc;

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

/*###### Deploying load_seqs ######*/

SEQ* load_seqs(char* data, char* mol, char delimiter) {
	
	SEQ* tmp; // Declaring temporary SEQ structure.
	SEQ* head; // Declaring head SEQ structure.
	char** lines; // To recieve split data.
	int i; // To iterate along lines.
	char* tmp_line;
	
	tmp = (SEQ*) malloc (sizeof(SEQ));
	head = NULL;
	tmp_line = NULL;
	lines = strsplit(data, delimiter);
	i = 0;

	while (lines[i] != NULL) {

		tmp_line = lines[i];
		if (tmp_line[0] == '>') {
			printf("Here is a sequence header!\n");
			if (tmp -> header == '\0') {
				tmp -> header = tmp_line;
				tmp -> type = mol;
				tmp -> sequence = NULL;
				tmp -> seq_len = 0;
				tmp -> link = head;
			}
			else {
				head = tmp;
				tmp = (SEQ*) malloc (sizeof(SEQ));
				continue;
			}
		}
		else {
			printf("Here is a sequence!\n");
			tmp -> sequence = tmp_line;
		}
		i++;

	}
	
	return head;

}



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

