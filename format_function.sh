#!/bin/sh
find . -name '*.c' -type f -exec sed -E -i 's/(^\w+\s\w+\([^)]*\))\{/\1\n\{/g' {} \;
find . -name '*.c' -type f -exec sed -E -i 's/(^\w+\s\w+\s\w+\([^)]*\))\{/\1\n\{/g' {} \;
