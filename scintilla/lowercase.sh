#!/bin/bash

for vr in $(find . | grep '\.h$'); do
    if $(test -e $vr); then
        orig=$vr;
        vrn=$(echo "$vr" | sed -rn 's/\/([a-Z|_|0-9]+).h$/\/\L\1\E.h/p')
        if $(test -z "$vrn"); then
            echo "problem with $orig"
        fi
        if [[ $vrn != $orig ]]; then
            echo "1: $orig 2: $vrn"
            mv $orig $vrn
            continue
        fi
    fi
    echo "not processing $vr"
done
