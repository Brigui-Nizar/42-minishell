# Fonctionnement de Minishell

## Introduction

Minishell est un interpréteur de commandes minimaliste qui permet d'exécuter des commandes shell de manière interactive ou non interactive. Ce document explique en détail le fonctionnement de Minishell, depuis l'entrée utilisateur jusqu'à l'exécution des commandes.

## Structure du Programme

Le programme est structuré en plusieurs fichiers et dossiers :

- `includes/`: Contient les fichiers d'en-tête.
- `src/`: Contient les fichiers source.
- `bin/`: Contient les scripts de test.
- `libft/`: Contient les fonctions utilitaires de la bibliothèque.

## Entrée Utilisateur

### Mode Interactif

En mode interactif, l'utilisateur interagit directement avec le shell en tapant des commandes. Le shell affiche un prompt et attend l'entrée de l'utilisateur.

### Mode Non Interactif

En mode non interactif, les commandes sont passées en argument lors de l'exécution du programme. Par exemple :

```sh
./minishell -c "ls -l | grep foo && echo bar || echo boo"
```
## Initialisation

### Initialisation du Shell

La fonction `init_minishell` initialise l'état du shell ([`t_shell_state`](./includes/structure.h)) avec les variables d'environnement et d'autres paramètres nécessaires.

void init_minishell(t_shell_state *shell_state, char **envp);

### Construction du Prompt

La fonction `build_shell_prompt` construit le prompt du shell.
```sh
char *build_shell_prompt(t_shell_state *shell_state);
```
## Parsing des Commandes

Les commandes entrées par l'utilisateur sont analysées et transformées en une structure de données interne appelée AST (Abstract Syntax Tree).

### Analyse Lexicale

Les tokens sont extraits de l'entrée utilisateur et stockés dans une liste de tokens.

### Analyse Syntaxique

Les tokens sont ensuite analysés pour construire l'AST. La fonction `parser` effectue cette tâche.
```sh
t_ast_node *parser(t_token **tokens, int min_precedence);
```
## Exécution des Commandes

### Gestion des Builtins

Les commandes internes (builtins) sont gérées par la fonction `launch_builtin`.
```sh
int launch_builtin(char **args, t_shell_state *shell_state);
```
### Exécution des Commandes Externes

Les commandes externes sont exécutées par la fonction `launch_process`.
```sh
int launch_process(char **args, t_shell_state *shell_state);
```
### Gestion des Redirections et Pipes

Les redirections et les pipes sont gérés en modifiant les descripteurs de fichiers avant l'exécution des commandes.

### Sauvegarde et Restauration des Descripteurs de Fichiers

Les descripteurs de fichiers sont sauvegardés et restaurés à l'aide des fonctions `save_fds` et `restore_fds`.

void save_fds(t_shell_state *shell_state);
void restore_fds(t_shell_state *shell_state);

## Nettoyage

Après l'exécution des commandes, les ressources allouées sont libérées et l'historique des commandes est effacé.

### Libération des Ressources

Les ressources allouées pour les commandes et l'état du shell sont libérées par les fonctions `free_commands` et [`exit_shell`](./src/utils/utils_input.c).

void free_commands(t_command *head);
void exit_shell(t_shell_state *shell_state);

### Effacement de l'Historique

L'historique des commandes est effacé à l'aide de la fonction `rl_clear_history`.

## Conclusion

Ce document a fourni une vue d'ensemble détaillée du fonctionnement de Minishell, depuis l'entrée utilisateur jusqu'à l'exécution des commandes. Pour plus de détails, veuillez consulter les fichiers source et les en-têtes correspondants.
