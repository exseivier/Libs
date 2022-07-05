

#include <stdio.h>
#include <stdlib.h>
#include "libio.h"

int main(int argc, char* argv[]) {
	printf("---------------- Testing load_file function ---------------\n");
	char* data = load_file(argv[1]);
	printf("%s\n", data);
	printf("---------------- Testing subseq function ----------------\n");
	char* sub = subseq(data, 3, 8);
	printf("Subsequence: %s\n", sub);
	printf("----------------- Testing len_str function ----------------\n");
	int lstr = len_str(data);
	printf("Length of string = %d\n", lstr);
	printf("----------------- Testing which_idx function ---------------\n");
	int* idxs = which_idx(data, '\n');
	printf("Position of the first %c is %d\n", '\n', idxs[0]);
	printf("Position of the second %c is %d\n", '\n', idxs[1]);
	printf("----------------- Testing strsplit function ----------------\n");
	char** results = strsplit(data, '\n');
	int i = 0;
	while (results[i] != NULL) {
		printf("%s\n", results[i]);
		i++;
	}
	i = 0;
	while (1) {

		if (results[i] == NULL) {
			printf("End of results array!\n");
			break;
		}
		i++;
	}

	printf("------------------- Testing load_seqs -------------------\n");

	SEQ** seqs = load_seqs(data, "DNA", '\n');
	
	i = 0;
	while (seqs[i] != NULL) {

		printf("%s|%s\n%s - len: %d\n",\
				seqs[i] -> header,\
				seqs[i] -> type,\
				seqs[i] -> sequence,\
				seqs[i] -> seq_len);
		i++;

	}
	
	printf("------------------- Testing char_cat --------------------\n");

	char* string;
	char* s1 = "Hello ";
	char* s2 = "world!";
	string = char_cat(s1, s2);
	printf("Concatenate %s and %s, resulted in: %s\n", s1, s2, string);
	free(idxs);
	free(data);
	free(sub);
	//To free results.
	//I hope it works.
	results = NULL;
	free(string);
	/* Works pretty good
	SEQ one_seq = {.type = "DNA",\
			.header = "Sequence_1",\
			.sequence = "ATGCGTAGCT",\
			.seq_len = 10,\
			.link = NULL};

	printf(">%s|%s\n%s - %d\n", one_seq.type,\
				one_seq.header,\
				one_seq.sequence,\
				one_seq.seq_len);
	*/

	return 0;
}
