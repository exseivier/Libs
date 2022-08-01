#!/usr/bin/env bash

#
#	not_alike pipeline.
#	Finds dissimilar sequences of a query genome
#	Comparing it to a database of determined size.
#	This database could have hugh size.
#

#
#	Author: Javier Montalvo-Arredondo.
#	Versin: 3.0.0.
#	Contact: Calzada Antonio Narro 1923
#	Buenavista Saltillo Coahuila México.
#	Basic Sciences division.
#


while getopts "i:s:S:d:h" opt;
do

	case $opt in

		h) echo "Usage: ...";;
		i) sequences=$OPTARG;;
		s) size=$OPTARG;;
		S) step=$OPTARG;;
		d) dbase=$OPTARG;;
		*) echo "Usage ...";;

	esac

done
shift $((OPTIND-1))

#	NOT_ALIKE BEGINS.

echo -e "\n[NOT_ALIKE][BEGINS]\n"

echo "Sequences file name $sequences"
echo "Size value = $size"
echo "Step size value = $step"
split_seqs_file=$(basename ${sequences%.*}_split.$size.$step.fasta)
echo "Output file name = $split_seqs_file"
echo "DataBase name is = $dbase"
dbase_dirname=$(dirname $dbase)

#	MANAGER :: SPLIT_GENOME BEGINS.

echo -e "\n[MANAGER::SPLIT_GENOME][BEGINS]\n"

if [ ! -d split_out ];
then
	mkdir split_out
else
	echo "split_out directory exists!"
fi

if [ ! -f split_out/${split_seqs_file}  ];
then
	./manager split_genome $sequences $size $step split_out/${split_seqs_file}
else
	echo "split_out/${split_seqs_file} exists!"
fi



echo -e "\n[MANAGER::SPLIT_GENOME][ENDS]\n"


if [ ! -d blast_out ];
then
	mkdir blast_out
else
	echo "blast_out directory exists!"
fi

#	MEGABLAST BEGINS.

echo "Copy split_out/${split_seqs_file} to split_out/input_seqs.txt"
cp split_out/${split_seqs_file} split_out/input_seqs.txt

cat $dbase | \
	while read -r line;
	do
	echo "BLAST split_out/input_seqs.txt against $dbase_dirname/${line%.*}.db"
	blastn -query split_out/input_seqs.txt \
		-db $dbase_dirname/${line%.*}.db \
		-task megablast \
		-out blast_out/$(basename ${sequences%.*}).blast \
		-evalue 1 \
		-outfmt "6 qseqid" \
		-max_target_seqs 1

##		FOR EACH BLAST HITS FILE.
##		MANAGER :: HIDE_MATCHED_SEQS BEGINS.

	cat blast_out/$(basename ${sequences%.*}).blast | while read line; do echo ">${line}" >> blast_out/tmp; done
	uniq blast_out/tmp > blast_out/tmp2
	rm blast_out/tmp

	#### I introduced the line tagged below because the *.blast file is corrupted in somehow.
	#### I do not know if it came from cat, from while loop or from uniq linux command.
	#### But such corruption also corrupts the memory allocation in fopen function in
	#### write_seqs function in libio.c.
	#### Adding a last return character to the *.blast file reverts the corruption.
	#### Do not ask me why, please.
	
	echo "" >> blast_out/tmp2 ### This is the line I introduced to the code.
	
	mv blast_out/tmp2 blast_out/$(basename ${sequences%.*}).blast
	echo -e "\n[MANAGER::HIDE_MATCHED_SEQS][BEGINS]\n"
		
	./manager hide_matched_seqs split_out/input_seqs.txt blast_out/$(basename ${sequences%.*}).blast DNA split_out/tmp.txt

	echo -e "\n[MANAGER::HIDE_MATCHED_SEQS][ENDS]\n"

	mv split_out/tmp.txt split_out/input_seqs.txt

	done

#	BLASTN BEGINS.
##		FOR EACH BLAST HITS FILE.
##		MANAGER :: HIDE_MATCHED_SEQS BEGINS.



#	NOT_ALIKE BEGINS.
echo -e "\n[NOT_ALIKE][ENDS]\n"



