# 42minishell

1. Create_prompt
2. Récup l'input avec readline
3. Ajouter à l'historique
4. Lexer
5. Expander
6. Parser qui check le lexicon
7. Convertir l'env en tableau
8. Créer l'exec_list
9. Checker les fichiers d'IO
10. Lancer l'exec à partir de l'exec_list
11. Cleanup_garbage, lexicon, et exec_list
12. Nouvelle boucle readline


TODO REWORK BUILTINS FOR EXIT CODE


### Functions to use

* readline :white_check_mark:
* rl_clear_history :white_check_mark:
* rl_on_new_line :white_check_mark:
* rl_replace_line :white_check_mark:
* rl_redisplay :white_check_mark:
* add_history :white_check_mark:
* printf :white_check_mark:
* malloc :white_check_mark:
* free :white_check_mark:
* write :white_check_mark:
* access :white_check_mark:
* open :white_check_mark:
* read :white_check_mark:
* close :white_check_mark:
* fork :white_check_mark:
* wait :x:
* waitpid :white_check_mark:
* wait3 :x:
* wait4 :question:
* signal :x:
* sigaction :white_check_mark:
* sigemptyset :white_check_mark:
* sigaddset :x:
* kill :question:
* exit :white_check_mark:
* getcwd :white_check_mark:
* chdir :white_check_mark:
* stat :x:
* lstat :x:
* fstat :x:
* unlink :white_check_mark:
* execve :white_check_mark:
* dup :x:
* dup2 :white_check_mark:
* pipe :white_check_mark:
* opendir :question:
* readdir :question:
* closedir :question:
* strerror :white_check_mark:
* perror :white_check_mark:
* isatty :x:
* ttyname :x:
* ttyslot :x:
* ioctl :x:
* getenv :white_check_mark:
* tcsetattr :x:
* tcgetattr :x:
* tgetent :x:
* tgetflag :x:
* tgetnum :x:
* tgetstr :x:
* tgoto :x:
* tputs :x: