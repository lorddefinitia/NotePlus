#!/bin/bash

end=$1

if $( test -z "$end" ); then
    end="h"
fi

for vr in $(find . | grep "\.$end$"); do
    if $(test -e $vr); then
        orig=$vr;
        vrn=$(echo "$vr" | sed -rn "s/\/([a-Z|_|0-9]+).$end$/\/\L\1\E.$end/p")
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
