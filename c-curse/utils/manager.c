/*
 * Interprocess manager for not_alike pipeline
 *
 * Author: Javier Montalvo-Arredondo.
 * Contact: buitrejma@gmail.com
 * 		UAAAN.
 * Version: 0.0.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "libio.h"

int main (int argc, char* argv[]) {

	if (argc != 4) {
		exit(1);
	}

	char* intprocID; // Interprocess ID such as "hide_matched_seqs".
	char* seqs_data; // Stores the sequences into an array.
	char* head_data; // Stores the headers into an array.
	char* seqsFilename; // CLI argument.
	char* headFilename; // CLI argument.
	SEQ** sequences; // Container of SEQ structures.
	char** headers; // headers array
	char* molecule; // Type of molecule. CLI argument.

	intprocID = argv[1];
	seqsFilename = argv[2];
	headFilename = argv[3];
	molecule = argv[4];
	
	
	if (cmp_str(intprocID, "hide_matched_seqs")) {

		seqs_data = load_file(seqsFilename);
		head_data = load_file(headFilename);
		sequences = load_seqs(seqs_data, molecule, RETC);
		headers = strsplit(head_data, RETC);
		free(seqs_data);
		free(head_data);
		print_seqs(sequences);
		sequences = hide_matched_seqs(sequences, headers);
		print_seqs(sequences);
		// write_seqs(sequences, outFilename);

	}
	else {
		printf("I do not understand you.\n");
	}

	return 0;

}
