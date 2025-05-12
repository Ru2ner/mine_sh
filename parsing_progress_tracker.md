# TOKENIZER

Breaks down the raw input of the user into tokens : pipe, redirections, files, etc...
Outputs a linked lists with all the tokens, that will be later processed by the parser.

* fetch_user_input(readline)  :white_check_mark:
* trim_whitespaces  :white_check_mark:
* create_tokens  :white_check_mark:
* error_handling  :x:

#### TOKENS

* word  :white_check_mark:
* cmd  :white_check_mark:
* cmd_with_args  :white_check_mark:
* pipe  :white_check_mark:
* redirections(< && >)  :white_check_mark:
* redirections_append_and_here_doc(<< && >>)  :white_check_mark:
* infiles_and_outfiles  :white_check_mark:

# PARSER

* syntax_validation  :white_check_mark:
* command_grouping  :white_check_mark: