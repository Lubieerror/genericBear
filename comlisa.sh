#clang++ gen-own.cc -Ofast -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe 
#g++ gen-own.cc -O3 -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe 
clear
g++ gen-own-lisa.cc -O3 -Wall -Wextra -m64 -std=gnu++0x -o lisa.exe
echo clang++ gen-own-lisa.cc -O3 -Wall -Wextra -m64 -std=gnu++0x -o lisa.exe
./lisa.exe