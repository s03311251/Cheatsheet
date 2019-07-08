#!/bin/bash
#shebang: tell the system that the following commands are to be executed by the Bourne shell

# either use new line or ; to separate commands

#print
echo "Hello World!"
echo -n "Hello World!" # no new line

#declare variable: must begin with alphabet or _, followed by alphanumeric characters; usually in UPPERCASE
VARIABLE_NAME=VARIABLE_VALUE # no space-> treat as program
STRING="Hello World!"

#declare interger
declare -i INTERGER
INTERGER=0

#array
declare -a ARRAYNAME 
ARRAYNAME=(value1 value2 ... valueN)
ARRAYNAME[indexnumber]=value
echo ${ARRAYNAME[indexnumber]}
echo ${ARRAYNAME[*]}

#calculation
#no need declare interger
a=1
let "a = $a + 9"
echo $a # -> 10
let "a = $a * $a - $a / $a"
echo $a # -> 99
let "a = ($a + 1) % 9"
echo $a # -> 1
#another method
a=$(($a+9))

#print newline
printf "hello\nworld\n"

#read user input
echo "what is your name?"
read name
echo "Hello $name!"
echo 'Hello $name!' #exact string
# "Hello $name!" = "Hello "$name"!"

#read file words by words
# Method 1
for word in $(<$FILENAME)
do
    echo "$word"
done
# Method 2 (no for-loop -> lines by lines)
while read line; do
    for word in $line; do
        echo "$word"
    done
done < $FILENAME

#enclose bash commands: executed as shell command and replaced by the result of the command
a=`date`
echo date # -> Wed Sep 14 15:41:29 HKT 2016

a="`wc -l file | cut -d\" \" -f1`" # <- \" here

#-----STRING-----

#get string length
a="Apple"
echo ${#a} # -> 5 

#substring
a="Pine apple"
echo "$a substring 5:5 is ${a:5:5}" # -> apple

#replace a part of a string
a="Apple pie"
from="pie"
to="juice"
echo ${a/$from/$to} # -> "Apple juice"
#The FIRST occurrence of "pie" in "Apple pie" will be replaced by "juice", therefore the result is "Apple juice"



#-----FILE MANIPULATION-----
#append line
echo "hello world" >> my_file.txt

#delete last line
sed -i '$ d' 100_0_crop.txt



#-----FLOW OF CONTROL-----

#condition
#[[ ]] is improvement to [ ]: [ -f "$FILE" ] = [[ -f $FILE ]]

#string
[ "$string" ]					#True iff the length of $string is non-zero
[ "$string1" == "$string2" ]	#True iff the strings are equal
[ "$string1" != "$string2" ]	#True iff the strings are different

[ "$string1" \> "$string2" ]	#True iff $string1 is sorted after $string2
[ "$string1" \< "$string2" ]	#True iff $string1 is sorted before $string2

#file
[ -e $file ]	#True iff file exists
[ -f $file ]	#True iff file is a file
[ -d $file ]	#True iff file is a directory
[ -s $file ]	#True iff file has size > 0

[ -r $file ]	#True iff file is readable
[ -w $file ]	#True iff file is writable
[ -x $file ]	#True iff file is executable

#comparison
[ $a -eq $b ]	#True iff a = b
[ $a -ne $b ]	#True iff a != b
[ $a -lt $b ]	#True iff a < b
[ $a -le $b ]	#True iff a <= b
[ $a -gt $b ]	#True iff a > b
[ $a -ge $b ]	#True iff a >= b

#if-else
if [ condition1 ] # [ <-SPACES HERE ARE IMPORTANT-> ]
then
	echo "Action 1"
elif [ condition2 ]
then
	echo "Action 2"
else
	echo "Action neither"
fi

## and
if [ condition1 ] && [ condition2 ]
then
	echo "Hello, World!"
fi

#for loop
LIST="1 2 3 4 15"
for i in $LIST
do
   echo -ne "$i " # -> 1 2 3 4 15
done
#eg	compile all .cpp file
list="`ls *.cpp`"
for name in $list
do
    cp $name "$name.backup"
done

#while loop
while [ $PAGE -lt 28 ]
do
	FILENAME="cropped_"$PAGE".jpg"
	PAGE=$PAGE+1
	NEWNAME="renamed_"$PAGE".jpg"
	echo $FILENAME" -> "$NEWNAME
done

#command line arguments
#$1, $2, $3,..., ${10}, ${11},...
#$0 is the name of the shell script
#$# returns the number of arguments when executes
#eg. ./script.sh a b c -> $1=a, $2=b, $3=c, $#=3

if [ -n "$1" ]
then
    echo "$1"
else
    echo "argument error"
fi

AAAA=$1
echo $AAAA # AAAA is string
declare -i AAAA # now AAA is interger
AAAA=$AAAA+1
echo $AAAA

#redirect to standard error
#echo normally output to standard output
echo "Hello!" >&2 # redirect to standard error (>2)

#function
function myBackupFunction()
{
	$1 #the first parameter PASSED to the function
	# pass parameter: myBackupFunction $VAR
}

## call function
myBackupFunction

#Add a Progress Bar
http://stackoverflow.com/questions/238073/how-to-add-a-progress-bar-to-a-shell-script

You can implement this by overwriting a line. Use \r to go back to the beginning of the line without writing \n to the terminal.
Write \n when you are done to advance the line.
Use echo -ne to:
    not print \n and
    to recognize escape sequences like \r.

Here is a demo:

echo -ne '#####                     (33%)\r'
sleep 1
echo -ne '#############             (66%)\r'
sleep 1
echo -ne '#######################   (100%)\r'
echo -ne '\n'

#Most frequent word
#WORTH ANALYSE!!!!!
#Array, (( )), For-loop, $(< "")

#!/bin/bash
file=$1
declare -A count
for word in $(< "$file"); do
    echo $word
    (( count[$word]++ ))
done

max=0
for word in "${!count[@]}"; do
    if (( ${count[$word]} > $max )); then
        max=${count[$word]}
        max_word=$word
    fi
done
echo "most seen word: '$max_word', seen $max times"

#Highlight
echo -e "\e[1m$word\e[m"



#Date
date
date +"%Y" # year
date +"%m" # month
date +"%d" # date
date +"%H" # hour

date -d "tomorrow 08:00:00" # tomorrow 08:00
date -d "tomorrow 8" # tomorrow 08:00
date -d "0830" # today 08:30
date -d "170627" # 2017/06/27



#Sleep
sleep 5 # 5 sec
sleep 2m # 2 min
sleep 3h # 3 hr
sleed 5d # 5 days
