#!/bin/sh
find ${PWD} -name '*.c' -type f -exec sed -E -i 's/(^(\w+\s)+\w+\([^)]*\))\{/\1\n\{/g' {} \;
