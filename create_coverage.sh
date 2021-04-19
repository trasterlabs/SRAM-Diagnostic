#! /bin/sh

# Prior to begin, ensure the folders exist
if [ ! -d ./cov/ ]; then mkdir -p ./cov/; fi
if [ ! -d ./gcov/ ]; then mkdir -p ./gcov/; fi
if [ ! -d ./gcov/aux ]; then mkdir -p ./gcov/aux; fi

# me voy de paseo a la carpeta auxiliar
cd ./gcov/aux

files_with_gcno=$(find ../../ -type f "*.gcno")
for each_file in $files_with_gcno
do
     echo "$each_file"
done
