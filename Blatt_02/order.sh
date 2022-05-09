#!/bin/bash

# Use getopts to parse options to our script
while getopts ":chl" opt; do
    case $opt in
	c)
	    MODE="Created"
	    ;;
	h)
	    echo "Usage: ./order -[chl] [Directory]"
	    echo "Option -h: Help"
	    echo "Option -l: Sort by last modified (default)"
	    echo "Option -r: Sort by created"
	    exit 1
	    ;;
	l)
	    MODE="LastModified"
	    ;;
    esac
    #Shift arguments, if option has been set
    shift $(($OPTIND - 1))
done

# Check if the argument is a directory
if [ -d "$1" ]; then
    DIRECTORY="$1"
else
    if [ "$1" = "" ]; then
	echo "The argument is missing! Use order -h to display the help information"
    else
	echo "Error! $1 is not a directory! Use order -h to display the help information"
	#exiting the script
    fi
    exit
fi

# Choose a default mode
if [ $OPTIND -eq 1 ]; then
    echo "Warning: No options were passed. (Default: Last Modified)"
    MODE="LastModified"
fi


# Save current dir to get back to it in the end
PWD=$(pwd)

# Go into the given directory
cd "$DIRECTORY" 

# Iterate over all .png and .jpg files in given directory
for i in $(ls | grep -e ".jpg\|.png" ); do
    # Get date in form of YYYY-MM-DD Time Timezone
    # the cuts are needed to get rid of the Time and Timezone and DD
    if [[ "$MODE" == "LastModified" ]]; then
	DIRNAME=$(stat -c %y "$i" | cut -d ' ' -f1 | cut -d '-' --fields="1 2")
    elif [[ "$MODE" == "Created" ]]; then
	DIRNAME=$(stat -c %w "$i" | cut -d ' ' -f1 | cut -d '-' --fields="1 2")
    fi
    # Create directory for month YYYY-MM and check if directory already exists
    if ! [ -d "$DIRNAME" ]; then
	mkdir "$DIRNAME"
	# Move i, the picture, in the directory of month
    fi
    mv "$i" "$DIRNAME"
done

# Go back to dir we started in
cd "$PWD" 

echo "Success!"

