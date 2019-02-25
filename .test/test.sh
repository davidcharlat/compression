errorExit()
{
  echo "$1";
  exit 1;
}

cd ./.test

gcc -o testa test.c ../src/*.c || errorExit "Compilation failed"
./testa || errorExit "program failed"

