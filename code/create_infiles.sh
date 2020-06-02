#!/bin/bash

echo "Your command line contains $# arguments"

if [ $# -ne 5 ] 
then
    echo "Usage: ./create_infiles.sh diseaseFile countriesFile input_dir numFilesPerDirectory numRecordsPerFile"
    exit -1
fi

echo "Positional Parameters"
echo '$0 = ' $0 ; echo '$1 = ' $1 ; echo '$2 = ' $2 ; echo '$3 = ' $3 ; echo '$4 = ' $4 ; echo '$5 = ' $5

# mkdir $3
DISEASEFILE="$1"
COUNTRIESILE="$2"
INPUT_DIR="$3"
NFPD="$4"
NRPF="$5"

ID=1

declare -a array

random (){

    FLOOR=$1
    RANGE=$2
    # Combine above two techniques to retrieve random number between two limits.
    number=0   #initialize
    while [ "$number" -le $FLOOR ]
    do
    number=$RANDOM
    let "number %= $RANGE"  # Scales $number down within $RANGE.
    done
    # echo "Random number between $FLOOR and $RANGE ---  $number"
    # echo
    return "$number"  
}

random_string () {
    name=''
    random 2 13
    length=$?
    for (( i = 0; i < "$length"; i++ )); 
    do
        random 96 123
        name+=$(printf "\\$(printf '%03o' "$?")")
    done

    echo "$name"
    # echo $?
    # return "$name"
}

write_file () {
    df="$2"


    output=$(eval "wc -l < $df")
    # echo "$output"
    output=$((output + 1))
    random 0 "$output"
    num=$?
    # echo "$num"
    
    dis=$(eval "sed '$num!d' "$df"")
    # echo "$dis"
    # random_string
    ret_name=$(random_string)    
    # echo "$ret_name"
    # random_string
    ret_surname=$(random_string)
    # echo "$ret_surname"
    arr[0]="ENTER"
    arr[1]="EXIT"

    rand=$[ $RANDOM % 2 ]
    random 0 121
    age=$?

    oldid=$ID
    if [[ "${arr[$rand]}" == "ENTER" ]];
    then
        array+=($ID)
        # echo "ENTER ENTRY"
    else
        # echo "EXIT ENTRY"
        if [[ "${#array[@]}" != "0" ]]; then
            # echo "non empty array"
            oldid=${array[-1]}
            # echo "$oldid"
            unset 'array[-1]'
        fi
    fi
    echo "$oldid ${arr[$rand]} $ret_name $ret_surname $dis $age" >> "$1"
    # echo "ade gami" 
    ID=$((ID + 1))
}

new_entry () {
    # echo "$1 $2 $3"
    # "$3" "$DIR/$DAY-$MONTH-20$YEAR" "$DISEASEFILE"
    for (( j = 0; j < "$1"; j++ )); 
    do
        # echo "stili1 stili2 stili3" > "$2"
        # echo "kalispera"
        write_file "$2" "$3"
        # echo $?
    done
    # echo
}


make_files () {
    # echo kalispera
    # echo "$2 $3 $4"
    # "$NFPD" "$NRPF" "$DISEASEFILE" 
    for (( i = 0; i < "$2"; i++ )); 
    do
        # echo "kalispera"
        random 0 31
        DAY=$?
        # echo "DAY-------- $DAY"

        random 0 13
        MONTH=$?
        # echo "MONTH-------- $MONTH"

        random 17 21
        YEAR=$?
        # echo "YEAR-------- $YEAR"

        DIR=$1
        touch "$DIR/$DAY-$MONTH-20$YEAR"
        new_entry "$3" "$DIR/$DAY-$MONTH-20$YEAR" "$4"
    done
    echo 
}




mkdir $INPUT_DIR


if [ ! $NFPD -gt 0 ]
then
    echo "Non Positive value"
    exit -1
fi

if [ ! $NRPF -gt 0 ]
then
    echo "Non Positive value"
    exit -1
fi

while IFS= read -r line
do
    dirName="$INPUT_DIR/$line"
    mkdir -p "$dirName"
    # printf 'array----------------------- %s\n' "${array[@]}"
    unset array
    make_files "$dirName" "$NFPD" "$NRPF" "$DISEASEFILE"
    # touch "$INPUT_DIR/$line"
    
done < "$COUNTRIESILE"

# mkdir -p $3/{1..10}/
 # | touch images/{100..110}/192x128/index.md




exit 0
