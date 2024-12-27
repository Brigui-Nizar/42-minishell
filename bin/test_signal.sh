#!/bin/bash

# Couleurs pour un affichage plus lisible
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Fichiers temporaires pour les sorties
BASH_OUTPUT="bash_output.txt"
MINISHELL_OUTPUT="minishell_output.txt"

# Commandes à tester (sans boucles ni syntaxes avancées)
declare -a commands=(
    "echo 'Test de commande simple'"
    "ls"
    "pwd"
    "cat non_existent_file"  # Fichier inexistant pour tester les erreurs
    "echo 'test redirection' > temp_testfile"
    "cat temp_testfile"
)

clear
# Fonction pour lancer un shell et capturer son PID
launch_shell() {
    shell_name="$1"
    output_file="$2"
    shell_cmd="$3"

   # echo -e "${YELLOW}Lancement de ${shell_name}...${NC}"

    # Lancer le shell en arrière-plan et capturer le PID
   $shell_cmd -c "sleep 10" > "$output_file" 2>&1 &

    # Attendre que le processus se lance et récupérer le PID
    sleep 0.5  # Donner le temps au shell de se lancer
    pid=$(pgrep -n -f "$shell_name")  # Récupérer le dernier PID correspondant à la commande
    echo $pid
}
launch_bash() {
    shell_name="$1"
    output_file="$2"
    shell_cmd="$3"

   # echo -e "${YELLOW}Lancement de ${shell_name}...${NC}"

    # Lancer le shell en arrière-plan et capturer le PID
   $shell_cmd -c "sleep 10" > "$output_file" 2>&1 &

    # Attendre que le processus se lance et récupérer le PID
    sleep 0.5  # Donner le temps au shell de se lancer
    pid=$!  # Récupérer le dernier PID correspondant à la commande
    echo $pid
}
# Fonction pour envoyer des signaux à un shell donné
send_signals() {
    shell_name="$1"
    pid="$2"
    
    echo -e "${YELLOW}Envoi des signaux à ${shell_name} (PID: $pid)...${NC}"

    # Attendre un peu pour laisser le shell se lancer
    sleep 1

    # Envoi du signal SIGINT (Ctrl+C)
    echo -e "${BLUE}Envoi de SIGINT (Ctrl+C) à ${shell_name}...${NC}"
    kill -2 $pid
    sleep 1
    # Envoi du signal SIGINT (Ctrl+C)
    echo -e "${BLUE}Envoi de SIGINT (Ctrl+C) à ${shell_name}...${NC}"
    kill -2 $pid
    sleep 1

    # Envoi du signal SIGQUIT (Ctrl+\)
    echo -e "${BLUE}Envoi de SIGQUIT (Ctrl+\\) à ${shell_name}...${NC}"
    kill -3 $pid
    sleep 1

    # Envoi du signal EOF (simuler Ctrl+D)
    echo -e "${BLUE}Envoi de SIGTERM (simuler Ctrl+D) à ${shell_name}...${NC}"
    kill -TERM $pid  # Simuler Ctrl+D
}

# Comparer les résultats
compare_results() {
    echo -e "${BLUE}Comparaison des résultats :${NC}"
	 # Retirer le prompt des fichiers avant de les comparer
   # sed 's/^[^ ]*:[^ ]* *//g' "$BASH_OUTPUT" > bash_filtered.txt
    #sed 's/^[^ ]*:[^ ]* *//g' "$MINISHELL_OUTPUT" > minishell_filtered.txt
    
    diff -u "$BASH_OUTPUT"   "$MINISHELL_OUTPUT"
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Le comportement est identique entre bash et minishell.${NC}"
    else
        echo -e "${RED}Il y a des différences entre bash et minishell.${NC}"
    fi
}

# Fonction pour exécuter des commandes simples dans bash et minishell
run_commands() {
    shell_cmd="$1"
    output_file="$2"
    
    # Exécuter chaque commande dans le shell spécifié
    for CMD in "${commands[@]}"; do
        echo -e "${BLUE}Test de la commande :${NC} $CMD"
        echo "$CMD" | $shell_cmd >> "$output_file" 2>&1
    done
}

# Lancer bash et minishell pour tester les signaux
minishell_pid=$(launch_shell "minishell" "$MINISHELL_OUTPUT" "./minishell")
bash_pid=$(launch_bash "bash" "$BASH_OUTPUT" "/bin/bash")

# Envoi des signaux à bash et minishell
send_signals "minishell" $minishell_pid
send_signals "bash" $bash_pid

# Attendre la fin des processus
wait $minishell_pid
wait $bash_pid

# Comparer les résultats des signaux
compare_results

echo -e "${YELLOW}Exécution des commandes dans minishell...${NC}"
run_commands "./minishell" "$MINISHELL_OUTPUT"

# Exécuter les commandes dans bash et minishell et comparer les résultats
echo -e "${YELLOW}Exécution des commandes dans bash...${NC}"
run_commands "/bin/bash" "$BASH_OUTPUT"


# Comparer les résultats des commandes
compare_results
