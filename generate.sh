# C
# flex ./lex.l # lex
# bison -d ./parser.y # bison

# C++
flex --c++ ./lex.l
/usr/local/opt/bison/bin/bison --language=C++ -d ./parser.y