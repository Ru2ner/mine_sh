# 42minishell

cd /tmp ; mcd /tmp ; mkdir -p test_dir/subdir ; touch test_dir/file1.txt test_dir/subdir/file2.log ; echo "Hello World"

bash-5.1$ echo "'$USER'"

minishell> cd /tmp ; mcd /tmp ; mcd /tmp ; mkdir -p test_dir/subdir ; touch test_dir/file1.txt test_dir/subdir/file2.log ; echo "Hello World"
==194688== Conditional jump or move depends on uninitialised value(s)
==194688==    at 0x40220B: specify_each_words (lexer.c:65)
==194688==    by 0x401F19: lexer (lexer.c:122)
==194688==    by 0x4023FC: create_lexicon (main_test_parsing.c:46)
==194688==    by 0x402589: readline_loop (main_test_parsing.c:75)
==194688==    by 0x402477: main (main_test_parsing.c:91)
==194688== 
==194688== Conditional jump or move depends on uninitialised value(s)
==194688==    at 0x402239: specify_each_words (lexer.c:70)
==194688==    by 0x401F19: lexer (lexer.c:122)
==194688==    by 0x4023FC: create_lexicon (main_test_parsing.c:46)
==194688==    by 0x402589: readline_loop (main_test_parsing.c:75)
==194688==    by 0x402477: main (main_test_parsing.c:91)
==194688== 
==194688== Invalid read of size 1
==194688==    at 0x401B63: extract_quoted_string (extractors.c:66)
==194688==    by 0x401EF6: lexer (lexer.c:117)
==194688==    by 0x4023FC: create_lexicon (main_test_parsing.c:46)
==194688==    by 0x402589: readline_loop (main_test_parsing.c:75)
==194688==    by 0x402477: main (main_test_parsing.c:91)
==194688==  Address 0x57206f6c6c654822 is not stack'd, malloc'd or (recently) free'd
==194688== 
==194688== 
==194688== Process terminating with default action of signal 11 (SIGSEGV)
==194688==  General Protection Fault
==194688==    at 0x401B63: extract_quoted_string (extractors.c:66)
==194688==    by 0x401EF6: lexer (lexer.c:117)
==194688==    by 0x4023FC: create_lexicon (main_test_parsing.c:46)
==194688==    by 0x402589: readline_loop (main_test_parsing.c:75)
==194688==    by 0x402477: main (main_test_parsing.c:91)
==194688== 
==194688== HEAP SUMMARY:
==194688==     in use at exit: 222,199 bytes in 723 blocks
==194688==   total heap usage: 1,107 allocs, 384 frees, 241,041 bytes allocated
==194688== 
==194688== LEAK SUMMARY:
==194688==    definitely lost: 5,099 bytes in 303 blocks
==194688==    indirectly lost: 1,630 bytes in 120 blocks
==194688==      possibly lost: 0 bytes in 0 blocks
==194688==    still reachable: 215,470 bytes in 300 blocks
==194688==         suppressed: 0 bytes in 0 blocks
==194688== Rerun with --leak-check=full to see details of leaked memory
==194688== 
==194688== Use --track-origins=yes to see where uninitialised values come from
==194688== For lists of detected and suppressed errors, rerun with: -s
==194688== ERROR SUMMARY: 21 errors from 3 contexts (suppressed: 0 from 0)
[1]    194688 segmentation fault (core dumped)  valgrind ./minishell