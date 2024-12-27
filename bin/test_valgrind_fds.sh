#!/bin/bash

# Initialisation des compteurs
count_total=0
count_leaks=0
leak_tests=()
ko_cmd_line=()
# Couleurs pour les sorties
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m'  # No Color

# Chemin vers ton minishell
MINISHELL="./minishell"

# Exécuter une commande simple pour obtenir le nombre de descripteurs de fichiers ouverts par défaut
valgrind_output_ref=$(valgrind --leak-check=full --track-fds=yes --quiet --log-file=valgrind_output_ref.txt bash -c "echo Hello Nizar")
if grep -q "FILE DESCRIPTORS:" valgrind_output_ref.txt; then
    basefds=$(grep "FILE DESCRIPTORS:" valgrind_output_ref.txt | awk '{print $4}' | sort -u)
fi
echo -e "${GREEN}Base file descriptors: $basefds${NC}"
# Liste des commandes à tester
 export nizar=test1
 export VARTESTER=VARTESTER is working
# Test cases
commands=(
  "echo Hello World"
  "echo -n Hello World"
  "echo Hello \$VARTESTER"
  "echo Hello \$USER"
  "echo 'Hello \$USER'"
  "echo \"Testing quotes\""
  "ls -l"
  "pwd"
  "export VAR=test && echo \$VAR"
  "export nizar=\"test2 test3 test4\""
  "export nizar=\"test2 test3 test4\" && echo \$nizar"
  "export nizar=\"test2 test3 test4\" && echo \$nizar && export nizar=\"ok\" && echo \$nizar"
  "export nizar=\"test2\" \"test3\" \"test4\""
  "export nizar=\"test2\" \"test3\" \"test4\" &&  echo \$nizar"
  "unset VAR && echo \$VAR"
  "cat /etc/passwd | grep root"
  "echo \"testing subshell\" && (echo \"subshell running\")"
  "echo \"multiple commands\" && ls && pwd"
  "ls -l | grep src"
  "echo \$nizar"
  "unset nizar"
  "echo \$nizar"
  "echo \$nizar && nizar=hello && echo \$nizar && set | grep nizar"
  "cd src/ && pwd"
  "cd src/ && pwd && ls -l | grep m && cd .. && pwd && ls -l | grep b"
  "cd src/ && pwd && ls -l | grep m && cd /home && pwd && ls -l | grep b"
  "cd src/ && ls -l | grep *.c"
  "ls *"
  "exit"
  "0"
  ""
  " "
  "  ' '   "
  "exit 0"
  "exit 1"
  "echo ''\$USER''"
  "echo \"une phrase très longue avec l'arrivée d'une apostrophe\" ''\$?''"
  "pwd .."
  "pwd ."
  "./minishell -c \"echo un terminal dans un autre\""
  "cd src/ && ./minishell -c \"echo un terminal dans un autre\""
  "unset PATH && ls -l"
  "ls -l"
  "echo qq \$HOME \$HO'ME' . "er"9 "
  "echo qq\$HOME \$HO'ME' . "er"9 "
  "echo qq\$HOME\$HO'ME' . "er"9 "
  "echo qq\$HOME\$HO'ME' ."er"9 "
  "echo qq\$HOME\$HO'ME'."er"9 "
  ">>> "
  ">> >>"
  "< >>"
  "     \"\"echo \$HO\"ME\""
  "''    \"\"echo \$HO\"ME\""
  "''''\"\"echo \$HO\"ME\""
  "echo \"'HO''ME'\""
  "echo \"'\$HO''ME'\""
  " /bin/echo"
 	" /bin/echo Hola Que Tal"
 	" /bin/env | wc -l"
 	" /bin/cd Desktop"
 	" (ls && ( ( pwd ) ) )"
 	" (ls && ( ( pwd ) ) )"
	"  ( ( ( ( ( pwd) ) ) ) )"
 	" exit "
 	" exit exit "
 	" exit hola "
 	" exit hola que tal "
 	" exit 42 "
 	" exit 000042 "
 	" exit 666 "
 	" exit 666 666 "
 	" exit -666 666 "
  "echo A > testA && echo B >testB && cat < testA >testC && ls -l | grep x | grep m > testD && cat testD"
  "echo A > testA && (echo B >testB && cat < testA >testC) && (ls -l | grep x | grep m) > testD && cat testD"
  "echo A >> testA && (echo B >>testB && cat < testA >>testC) && (ls -l | grep x | grep m) >> testD && cat testD"
     "echo 'Hello Nizar' > file_a> file_b> file_c> file_d> file_e> file_final_test"
    "echo 'Hello Nizar' > file_a"
    "echo 'Append this' >> file_a"
    "cat file_a > file_b"
    "cat < file_b"
    "cat < file_b > file_c"
    "echo 'Another test' >> file_b"
    "echo 'More data' >> file_c"
    "cat file_c > file_d"
    "echo 'MORE MORE MOReee' > file_e"
    "echo 'Bavo nizar!!! c est fini' > file_final_test"
    "echo 'The End'>fin"
    "echo A >infile"
    "cat < infile > outfile"
    "cat < infile > outfile"
    "cat outfile | cat -e > outfile2"
    "(cat outfile2 | cat -e) | cat -e"
    "cat < outfile2  cat -e > outfile3"
    "< outfile2  cat -e >> outfile3"
    # "< b > c"
    "< outfile2  cat -e > outfile3"
    "< infile  cat -e > outfile"
    "cat < infile | cat -e > outfile"
    "< infile > outfile"
)

# Boucle sur chaque commande à tester
for cmd in "${commands[@]}"; do
  count_total=$((count_total + 1))
  echo -e "${YELLOW}=== TEST $count_total ==============================${NC}"
  echo -e "${BLUE}Testing: $cmd${NC}"

  # Exécuter la commande avec Valgrind sur Minishell pour détecter les fuites
  valgrind_output=$(valgrind --leak-check=full --track-fds=yes --quiet --log-file=valgrind_output.txt $MINISHELL -c "$cmd")

  # Lire la sortie Valgrind depuis le fichier de log
  if grep -q "FILE DESCRIPTORS:" valgrind_output.txt; then
    leaks=$(grep "FILE DESCRIPTORS:" valgrind_output.txt | awk '{print $4}'  | sort -u)
     echo -e "${BLUE}Leaked file descriptors: $leaks${NC}" 
    if [ "$leaks" != "$basefds" ]; then
      echo -e "${RED}--------- ${NC}"
      echo -e "${RED} ${leaks} open  at exit leaks ${NC}"
      echo -e "${RED}--------- ${NC}"
      echo -e "${RED} ${basefds} open  at exit basefds ${NC}"
      echo -e "${RED}--------- ${NC}"
      cat valgrind_output.txt | grep "FILE DESCRIPTORS:"
      count_leaks=$((count_leaks + 1))
      leak_tests+=("$count_total")
    ko_cmd_line+=("[$cmd]")
    else
      echo -e "${GREEN}Ok ${basefds} open at exit.${NC}"
    fi
  else
    echo -e "${GREEN}No file descriptor leaks detected.${NC}"
  fi

  # Nettoyer le fichier temporaire
  rm -f valgrind_output.txt
done

# Afficher le résumé à la fin
echo -e "${YELLOW}=======================================${NC}"
echo -e "${BLUE}Résumé des tests:${NC}"
echo "Total tests: $count_total"
echo "Tests avec fuites de mémoire: $count_leaks"

if [ ${#leak_tests[@]} -ne 0 ]; then
  echo -e "${RED}Index des tests avec fuites de fds: ${leak_tests[*]}${NC}"
   echo -e "cmd: ${RED} ${ko_cmd_line[*]} ${NC} "
else
  echo -e "${GREEN}Aucune fuite détectée.${NC}"
fi
echo -e "${YELLOW}=======================================${NC}"

# Nettoyer les fichiers temporaires
echo -e "${BLUE}Nettoyage des fichiers temporaires...${NC}"
rm -f valgrind_output_ref.txt
rm -f valgrind_output.txt
rm -f testA testB testC testD
rm -f file_a file_b file_c file_d file_e file_final_test fin infile outfile outfile1 outfile2 outfile3
