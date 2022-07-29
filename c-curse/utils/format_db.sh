####
#	BLAST DB FORMAT WRAPPER.
#
#	AUTHOR: JAVIER MONTALVO-ARREDONDO.
#	CONTACT: CALZADA ANTONIO NARRO 1923
#	BUENAVISTA SALTILLO COAHUILA.
#	UNIVERSIDAD AUTONOMA AGRARIA ANTONIO NARRO.
#	DEPARTAMENTO DE CIENCIAS BASCIAS.
####

while getopts "d:h" opt;
do

	case $opt in

		h) echo -e "UUUUU. No le sabe. hahahah!";;
		d) dbase=${OPTARG}; echo "database = $dbase";;
		*) echo "UUUUUU. No le sabe. Hahahaha!";;

	esac

done
shift $((OPTIND-1))


echo -e "\n[FORMAT_DB][BEGINS]\n"

directory=$(dirname $dbase)
file=$(basename $dbase)

cat $dbase | \
	while read -r line;
	do

		echo "Formating ${directory}/$line"
		makeblastdb -dbtype nucl \
				-in ${directory}/$line \
				-input_type fasta \
				-title ${line%.*} \
				-parse_seqids \
				-out ${directory}/${line%.*}.db \
				-blastdb_version 4


	done
echo -e "\n[FORMAT_DB][ENDS]\n"
