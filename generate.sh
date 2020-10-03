flex ./lex.l # lex
mv lex.yy.c lex.yy.cc
/usr/local/opt/bison/bin/bison -d ./parser.y # bison
mv parser.tab.c parser.tab.cc
