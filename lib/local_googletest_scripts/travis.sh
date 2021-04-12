#!/usr/bin/env sh

if [ $OSTYPE != "cygwin" ]
then
  # "Not cygwin"
 set -evx
else
    echo "Using cygwin..."
 BUILD_TYPE="-O2"
 CXX_FLAGS=“-D_GNU_SOURCE -D_POSIX_C_SOURCE=200809 -std=gnu++11 -fms-extensions -fdata-sections -ffunction-sections”
fi
. lib/local_googletest_scripts/get-nprocessors.sh
# Tell make to use the processors. No preceding '-' required.
MAKEFLAGS="j${NPROCESSORS}"
export MAKEFLAGS
env | sort
# Set default values to OFF for these variables if not specified.
: "${NO_EXCEPTION:=ON}"
: "${NO_RTTI:=ON}"
: "${COMPILER_IS_GNUCXX:=ON}"
mkdir build_gtest || true
cd build_gtest
cmake -Dgtest_build_samples=OFF \
      -Dgtest_build_tests=OFF \
      -Dgmock_build_tests=OFF \
      -Dcxx_no_exception="$NO_EXCEPTION" \
      -Dcxx_no_rtti="$NO_RTTI" \
      -DCMAKE_COMPILER_IS_GNUCXX="$COMPILER_IS_GNUCXX" \
      -DCMAKE_CXX_FLAGS="$CXX_FLAGS" \
      -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
      ../lib/googletest
make
cd ..
cp -r build_gtest/lib/*.* lib/
cp -r lib/googletest/googletest/include/* include/
cp -r lib/googletest/googlemock/include/* include/
