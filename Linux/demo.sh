#!/bin/bash

OPERA=src/opera

if [ ! -x "$OPERA" ]; then
    $(cd src && ./configure && make)
fi

if [ ! -x "$OPERA" ]; then
    echo "can't build opera :("
    exit 1
fi

echo "Opera detected in $OPERA"

for file in $(ls demo/*.txt); do
    echo "Testing $file..."
    $OPERA $file
done
