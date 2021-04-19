#! /bin/sh

# Prior to begin, ensure the folders exist
if [ ! -d ./cov/ ]; then mkdir -p ./cov/; fi
if [ ! -d ./gcov/ ]; then mkdir -p ./gcov/; fi
if [ ! -d ./gcov/aux ]; then mkdir -p ./gcov/aux; fi

cd ./gcov/aux

# searching files with gcno extension
files_with_gcno=$(find ../../ -type f "*.gcno")
for each_file in $files_with_gcno
do
     echo "$each_file"
done

# searching files with gcda extension
files_with_gcda=$(find ../../ -type f "*.gcda")
for each_file in $files_with_gcda
do
     echo "$each_file"
done
