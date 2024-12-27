#!/bin/bash

# Path to the minishell executable
MINISHELL=./minishell
# Initialisation des compteurs
count_total=0
count_ok=0
count_ko=0
count_sub_ko=0
ko_tests=()
ko_cmd_line=()
# Color codes for output formatting
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
file_a=a file_b=b file_c=c file_d=d file_e=e file_final_test=final_test
#outfile1=outfile1 outfile2=outfile2 outfile3=outfile3 infile=infile fin=fin 
# Liste des commandes à tester
declare -a commands=(
    "echo 'Hello Nizar' > \$file_a> \$file_b> \$file_c> \$file_d> \$file_e> \$file_final_test"
    "echo 'Hello Nizar' > \$file_a"
    "echo 'Append this' >> \$file_a"
    "cat \$file_a > \$file_b"
    "cat < \$file_b"
    "cat < \$file_b > \$file_c"
    "echo 'Another test' >> \$file_b"
    "echo 'More data' >> \$file_c"
    "cat \$file_c > \$file_d"
    "echo 'MORE MORE MOReee' > \$file_e"
    "echo 'Bavo nizar!!! c est fini' > \$file_final_test"
    "echo 'The End'>\$fin"
    "echo A >\$infile"
    "cat < \$infile > \$outfile"
    "cat < \$infile > \$outfile"
    "cat \$outfile | cat -e > \$outfile2"
    "(cat \$outfile2 | cat -e) | cat -e"
    "cat < \$outfile2  cat -e > \$outfile3"
    "< \$outfile2  cat -e >> \$outfile3"
    # "< b > c"
    "< \$outfile2  cat -e > \$outfile3"
    "< \$infile  cat -e > \$outfile"
    "cat < \$infile | cat -e > \$outfile"
    "< \$infile > \$outfile"

)

# Préparation
echo -e "${YELLOW}Préparation des fichiers de test...${NC}"
rm -f temp_bash* temp_minishell* bash_output minishell_output error_output_bash error_output_minishell infile outfile outfile1 outfile2 outfile3

# Définir le préfixe
prefix_bash="temp_bash"
prefix_minishell="temp_minishell"

# Boucle pour tester chaque commande
for CMD in "${commands[@]}"; do
	count_total=$((count_total + 1))
    count_sub_ko=0

    prefix=$prefix_minishell 
   expanded_cmd=$(echo "$CMD" | sed "s/\\\$prefix/$prefix/g;
                                     s/\\\$file_a/$file_a/g;
                                     s/\\\$file_b/$file_b/g;
                                     s/\\\$file_c/$file_c/g;
                                     s/\\\$file_d/$file_d/g;
                                     s/\\\$file_e/$file_e/g;
                                     s/\\\$fin/fin/g;
                                     s/\\\$infile/infile/g;
                                     s/\\\$outfile/outfile/g;
                                     s/\\\$outfile1/outfile1/g;
                                     s/\\\$outfile2/outfile2/g;
                                     s/\\\$outfile3/outfile3/g;
                                     s/\\\$file_final_test/$file_final_test/g")
    
   # echo  -e "${BLUE}Test de la commande :${NC} $expanded_cmd"
	echo -e "${YELLOW}=== TEST $count_total ==============================${NC}"
    echo -e "${GREEN}Testing command: ${NC}${expanded_cmd}"
    # Exécution dans bash
   # echo -e "${YELLOW}Exécution dans bash...${NC}"

    prefix=$prefix_bash
   file_a=$prefix'a' file_b=$prefix'b' file_c=$prefix'c' file_d=$prefix'd' file_e=$prefix'e' file_final_test=$prefix'final_test' fin=$prefix'fin' infile=$prefix'infile' outfile=$prefix'outfile' outfile1=$prefix'outfile1' outfile2=$prefix'outfile2' outfile3=$prefix'outfile3'
    bash -c "file_a=$file_a; file_b=$file_b; file_c=$file_c; file_d=$file_d; file_e=$file_e; file_final_test=$file_final_test; fin=$fin; infile=$infile; outfile=$outfile; outfile1=$outfile; outfile2=$outfile2; outfile3=$outfile3 ; $CMD" > bash_output 2> error_output_bash
    bash_exit_code=$?
  

    # Exécution dans minishell
   # echo -e "${YELLOW}Exécution dans minishell...${NC}"
    prefix=$prefix_minishell
     file_a=$prefix'a' file_b=$prefix'b' file_c=$prefix'c' file_d=$prefix'd' file_e=$prefix'e' file_final_test=$prefix'final_test' fin=$prefix'fin' infile=$prefix'infile' outfile=$prefix'outfile' outfile1=$prefix'outfile1' outfile2=$prefix'outfile2' outfile3=$prefix'outfile3'
    ./minishell -c "export file_a=$file_a file_b=$file_b file_c=$file_c file_d=$file_d file_e=$file_e file_final_test=$file_final_test fin=$fin infile=$infile outfile=$outfile outfile1=$outfile outfile2=$outfile2 outfile3=$outfile3 && $CMD" > minishell_output 2> error_output_minishell
    minishell_exit_code=$?

    # Comparaison des résultats
   # echo -e "${GREEN}Comparaison des résultats pour la commande : ${NC}${expanded_cmd}"
    if [ "$bash_exit_code" == "$minishell_exit_code" ] && [ "$(cat bash_output)" == "$(cat minishell_output)" ]; then
       # echo -e "${GREEN}Test réussi${NC}"
        echo -n
    else
        count_sub_ko=$((count_sub_ko + 1))
        echo -e "${RED}Test échoué${NC}"
    fi

   # echo -e "${GREEN}Valeurs de retour :${NC}"
   # echo -e "Bash exit code: ${BLUE}$bash_exit_code${NC}"
   # echo -e "Minishell exit code: ${BLUE}$minishell_exit_code${NC}"

   # echo ""
   # echo -e "${GREEN}Comparaison des sorties standard :${NC}"
    diff bash_output minishell_output
    if [ $? -eq 0 ]; then
        echo -n
       # echo -e "${GREEN}Les sorties standard sont identiques.${NC}"
    else
        count_sub_ko=$((count_sub_ko + 1))
        echo -e "${RED}Différences dans les sorties standard.${NC}"
    fi

   # echo ""
    #echo -e "${GREEN}Comparaison des erreurs :${NC}"
    diff error_output_bash error_output_minishell
    if [ $? -eq 0 ]; then
        echo -n
        #echo -e "${GREEN}Les sorties erreur sont identiques.${NC}"
    else
        count_sub_ko=$((count_sub_ko + 1))
        echo -e "${RED}Différences dans les sorties d'erreur.${NC}"
    fi

  #  echo ""
   # echo -e "${BLUE}Comparaison des contenus des fichiers générés après la commande :${NC}"
    for file in "$prefix_bash"*; do
        if [ -f "$file" ]; then
          #  echo -e "${BLUE}Fichier $file :${NC}"
          #  cat "$file"
          #  echo ""

            # Comparaison avec le fichier correspondant dans Minishell
            minishell_file="${file/temp_bash/temp_minishell}"
          #  echo -e "${GREEN}Comparaison du contenu de $file avec le fichier minishell...${NC}"
            diff "$file" "$minishell_file" > /dev/null
            if [ $? -eq 0 ]; then
                echo  -n #-e "${GREEN}Le contenu de $file est identique à celui de $minishell_file.${NC}"
            else
               count_sub_ko=$((count_sub_ko + 1))
                echo -e "${BLUE}Fichier $file :${NC}"
                echo -e "${RED}Le contenu de $file diffère de celui de $minishell_file.${NC}"
            fi
        fi
    done
    if [ $count_sub_ko -eq 0 ]; then
        echo -e "${GREEN}Tous les tests ont réussi pour la commande : ${expanded_cmd}${NC}"
        count_ok=$((count_ok + 1))
    else
        echo -e "${RED}Au moins un test a échoué pour la commande : ${expanded_cmd}${NC}"
        count_ko=$((count_ko + 1))
        ko_cmd_line+=("[$cmd]")
    fi

    echo ""
done

# Nettoyage des fichiers
echo -e "${YELLOW}Nettoyage des fichiers...${NC}"
rm -f temp_bash* temp_minishell* bash_output minishell_output error_output_bash error_output_minishell infile outfile outfile1 outfile2 outfile3
# Afficher le nombre de tests réussis et échoués
  echo -e "\n\n${YELLOW}=== Resume =================================${NC}"
  echo -e "${BLUE}Résumé des $count_total tests:${NC}"
  echo -e "${GREEN}Tests OK: $count_ok / $count_total ${NC}"
  if [ "$count_ko" != "0" ]; then
  echo -e "${RED}Tests KO: $count_ko ${NC}"
  else 
  echo -e "${GREEN}*** bravo **********************************${NC}"
  fi
  if [ ${#ko_tests[@]} -ne 0 ]; then
    echo -e "Index des tests KO: ${RED} ${ko_tests[*]} ${NC} "
    echo -e "cmd: ${RED} ${ko_cmd_line[*]} ${NC} "
else
    echo "      Aucun test KO."
fi
  echo -e "${YELLOW}=== END ====================================${NC}"

