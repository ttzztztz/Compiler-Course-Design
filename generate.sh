flex ./lex.l # lex
mv lex.yy.c lex.yy.cc
bison -d ./parser.y # bison
mv parser.tab.c parser.tab.cc
