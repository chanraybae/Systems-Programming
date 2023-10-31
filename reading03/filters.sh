#!/bin/bash

q1_answer() {
    # TODO: Complete pipeline
    echo "Read the fine manual" | tr a-z A-Z
}

q2_answer() {
    # TODO: Complete pipeline
    echo "BTW, I use Arch" | sed 's/Arch/Pop/g'
}

q3_answer() {
    # TODO: Complete pipeline
    echo "     Yes, do as I say" | awk '{$1=$1;print}'
}

q4_answer() {
    # TODO: Complete pipeline
    curl -sL https://yld.me/raw/yWh | cut -d : -f 7- | head -n 1
}

q5_answer() {
    # TODO: Complete pipeline
    curl -sL https://yld.me/raw/yWh | grep '4[0-9]*7'
}

q6_answer() {
    # TODO: Complete pipeline
    curl -sL https://yld.me/raw/yWh | sed 's/\/bin\/sh/\/bin\/zsh/g' | sed 's/\/bin\/bash/\/bin\/zsh/g' | sed 's/\/bin\/csh/\/bin\/zsh/g' | sed 's/\/bin\/tcsh/\/bin\/zsh/g' | grep zsh
}
