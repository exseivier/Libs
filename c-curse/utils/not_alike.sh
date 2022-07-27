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


while getopts "i:s:S:h" opt;
do

	case $opt in

		h) echo "Usage: ...";;
		i) sequences=$OPTARG;;
		s) size=$OPTARG;;
		S) step=$OPTARG;;
		*) echo "Usage ...";;

	esac

done
shift $((OPTIND-1))

# CHECKS.

echo "Sequences file name $sequences"
echo "Size value = $size"
echo "Step size value = $step"
split_seqs_file=${sequences%.*}_split.fasta
echo "Output file name $split_seqs_file"

./manager split_genome $sequences $size $step $split_seqs_file

echo "[NOT_ALIKE][FINISHED]"
