#! /bin/bash

# read -p "Enter your name: " NAME

# if [ "$NAME" != "" ]
# then
# 	echo "Hello $NAME"
# else
# 	echo "no name"
# fi


# NUM1=1
# NUM2=12 

# if [ $NUM1 -gt $NUM2 ] 
# then
# 	echo greater 
# else 
# 	echo not greater	
# fi


# FILE="test.txt"
# if [ -f "$FILE" ] 
# then
# 	echo "$FILE is a FILE"
# else
# 	echo "not a file"	
# fi


# read  -p "Are you 21 or over? Y/N" ANSWER 

# case "$ANSWER" in
# 	[yY] | [yY][eE][sS])
# 		echo "bravo"
# 		;;
# 	[nN] | [nN][oO])
# 		echo "paketo"
# 		;;
# 	*)
# 		echo "dwse kati"		
# esac

# NAMES="pame ligo gamw"
# for NAME in $NAMES
# 	do 
# 		echo "hello $NAME"
# done

# FILES=$(ls *.txt)
# NEW="neo"
# for FILE in $FILES
# 	do
# 		mv $FILE $NEW-$FILE
# done


# LINE=1
# while read -r CUR
# 	do 
# 		echo "$LINE: $CUR"
# 		((LINE++))
# done <"./neo-new-new-1.txt"		

# function foo(){
# 	echo "hello, im $1 and i am $2"
# }

# foo "dim" "23"

mkdir hello 
touch "hello/world.txt"
echo "Hello world" >> "hello/world.txt"
echo "created"














