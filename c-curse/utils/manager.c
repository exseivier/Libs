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

	char* intprocID; // Interprocess ID such as "hide_matched_seqs".
	intprocID = argv[1];

	if (cmp_str(intprocID, "hide_matched_seqs")) {

		/* Arguments order
		 * 1. InterProcID (*).
		 * 2. Sequences file name.
		 * 3. Headers file name.
		 * 4. Molecule type.
		 * 5. Out file name.
		 */

		if (argc != 6) {
			printf("Error in arguments.\n");
			exit(1);
		}

		char* seqs_data; // Stores the sequences into an array.
		char* head_data; // Stores the headers into an array.
		char* seqsFilename; // CLI argument.
		char* headFilename; // CLI argument.
		SEQ** sequences; // Container of SEQ structures.
		char** headers; // headers array
		char* molecule; // Type of molecule. CLI argument.
		char* outFilename; // Outfile name. CLI argument.

		seqsFilename = argv[2];
		headFilename = argv[3];
		molecule = argv[4];
		outFilename = argv[5];
	
		seqs_data = load_file(seqsFilename);
		head_data = load_file(headFilename);
		sequences = load_seqs(seqs_data, molecule, RETC);
		free(seqs_data);
		seqs_data = NULL;
		headers = strsplit(head_data, RETC);
		free(head_data);
		head_data = NULL;
		//print_seqs(sequences);
		hide_matched_seqs(sequences, headers);
		//print_seqs(sequences);
		if (write_seqs(sequences, outFilename)) {
		
			printf("Sequences stored in file %s...\n", outFilename);

		}
		else {

			printf("Something went wrong. Fixit with gdb...");

		}
	}
	else if (cmp_str(intprocID, "split_genome")) {

		/* Arguments order
		 * 1. InterProcID (*).
		 * 2. Sequences file name.
		 * 3. Fragment size.
		 * 4. Step size.
		 * 5. Out file name.
		 */

		if (argc != 6) {

			printf("Error in arguments!");
			exit(1);

		}
		else {

			char* seqsFilename = argv[2];
			char* a = argv[3];
			int frag_size = atoi(a);
			
			char* b = argv[4];
			int step = atoi(b);
			
			char* outFilename = argv[5];
			
			printf("Open %s file...\n", seqsFilename);
			char* seqs_data = load_file(seqsFilename);
			
			printf("Loading sequences...\n");
			SEQ** sequences = load_seqs(seqs_data, "DNA", RETC);
			
			printf("Split genome...\n");
			sequences = split_genome(sequences, frag_size, step);
			
			if (write_seqs(sequences, outFilename)) {

				printf("Split seqs were stored in %s...\n", outFilename);

			}
			else {

				printf("Something went wrong at storing seqs in file...\n");

			}

		}

	}
	else {
		printf("I do not understand you.\n");
	}

	return 0;

}
