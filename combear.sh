#clang++ gen-own.cc -Ofast -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe 
#g++ gen-own.cc -O3 -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe 
clear
clang++ gen-own.cc -Ofast -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe
echo clang++ gen-own.cc -Ofast -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe
# clang++ gen-own.cc -O3 -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe
# echo clang++ gen-own.cc -O3 -Wall -Wextra -m64 -std=gnu++0x -o bearit.exe
./bearit.exe