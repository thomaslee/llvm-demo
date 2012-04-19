#!/bin/bash

set -ex

aclocal
autoconf
automake --add-missing --copy
./configure "$@"

