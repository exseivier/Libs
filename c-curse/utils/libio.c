
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
	//free(FHIN);
	// When I use fclose, in char_cat function at
	// malloc assignment occurs a rare behavior.
	// Error.  malloc(): invalid nex size (unsorted).
	// I think fclose function remains some available data
	// around the heap, so trying to acces to those addresses
	// is prohibited and produces this error ("I think").
	// Quite opposite, when I use free, this error does
	// not occur but the program never ends.
	// "WHY IS IT SO COMPLEX!"
	//fclose(FHIN);
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
	int buf_inc; // BUFFER increments.
	
	buf_inc = BUFFER;
	container = (SEQ**) malloc (sizeof(SEQ*) * buf_inc);
	container_counter = 0;
	tmp_line = NULL;
	lines = strsplit(data, delimiter);
	i = 0;

	while (lines[i] != NULL) {

		tmp_line = lines[i];
		if (tmp_line[0] == '>') {
			//printf("Here is a sequence header!\n");
			container_counter++;
			if (container_counter == buf_inc) {
				buf_inc = buf_inc * 2;
				container = realloc(container, sizeof(SEQ*) * buf_inc);
			}
			tmp = (SEQ*) malloc (sizeof(SEQ));
			container[container_counter-1] = tmp;
			container[container_counter-1] -> header = tmp_line;
			container[container_counter-1] -> type = mol;
			container[container_counter-1] -> sequence = "";
			container[container_counter-1] -> seq_len = 0;
			container[container_counter-1] -> hide = FALSE;
		}
		else {
			//printf("Here is a sequence!\n");
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
	free(lines);
	//free(tmp);
	// If you free tmp free also container header
	// because both tmp and container are pointing
	// to the same memory address.
	return container;

}

/*###### Deploying split_genome ######*/

SEQ** split_genome(SEQ** container, int size, int step) {
	
	// Declaration
	SEQ** split_seqs; // Container for spit sequences.
	int cont_i; // Input sequences container counter.
	int spli_i; // Split sequences container counter.
	int buf_inc; // BUFFER increments.
	char** tmp_seqs; // Holds sequences.
	int tseq_i; // Counter for tmp_seqs.
	int num_of_frags; // Number of expected fragments after split_by_window.

	// Assignment.
	cont_i = 0;
	spli_i = 0;
	buf_inc = BUFFER;
	split_seqs = (SEQ**) malloc (sizeof(SEQ*) * buf_inc);
	
	// Iterates over input sequences container.
	while (container[cont_i] != NULL) {
		
		// Calculates the number of expected fragments by
		// dividing the sequence length between step number.
		num_of_frags = container[cont_i] -> seq_len / step;

		tmp_seqs = (char**) malloc (sizeof(char*) * num_of_frags);

		// Returns the split sequences of size "size" at each "step" step.
		tmp_seqs = split_by_window(container[cont_i] -> sequence, size, step);
		
		// Checks if more space is needed in the heap;
		if (spli_i == buf_inc) {

			buf_inc = buf_inc * 2;
			split_seqs = realloc(split_seqs, sizeof(SEQ*) * buf_inc);

		}
		
		// For each tmp seq fill the slots of a SEQ structure.
		for (tseq_i = 0; tseq_i < num_of_frags; tseq_i++) {

			split_seqs[spli_i] -> type = "DNA";
			snprintf(split_seqs[spli_i] -> header, \
					sizeof(container[cont_i] -> header) + sizeof(spli_i), \
					"%s_%d", \
					container[cont_i] -> header, \
					spli_i);

			split_seqs[spli_i] -> sequence = tmp_seqs[tseq_i];
			split_seqs[spli_i] -> seq_len = len_str(tmp_seqs[tseq_i]);
			split_seqs[spli_i] -> hide = FALSE;
			spli_i++;

		}

		cont_i++;
	}

}


/*###### Deploying split_by_window ######*/


char** split_by_window(char* sequence, int size, int step) {

	## Coding...

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


bool write_seqs(SEQ** container, char* outFilename) {

	FILE* OUTF;
	int i; // Counter for while loop.

	OUTF = fopen(outFilename, "w+");
	i = 0;
	while (container[i] != NULL) {

		if (container[i] -> hide == FALSE) {

			fprintf(OUTF, "%s\n%s\n", container[i] -> header, \
						container[i] -> sequence);

		}
		i++;
	}
	fclose(OUTF);
	return TRUE;
	
}


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
	if (result[result_idx] != END_OF_CHR_ARRAY) {
		result[result_idx] = END_OF_CHR_ARRAY;
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
