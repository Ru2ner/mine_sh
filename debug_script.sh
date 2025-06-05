#/bin/zsh

export MINISHELL_FOLDER=/home/tlutz/Documents/SaveGithub/42minishell/

gnome-terminal -- zsh -c "valgrind-listener; exec zsh"

make val -C $MINISHELL_FOLDER

