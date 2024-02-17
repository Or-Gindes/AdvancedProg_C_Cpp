#!/bin/bash
# Comments start with "#" sign 

# Directory name variable
WORKING_DIR="Lab1.pb"

# File name variable
DATA="$WORKING_DIR/phonebook" 

# Create the directory here:
mkdir $WORKING_DIR

# Creates the file here: (this file will contain the phonebook registries)
touch $DATA

# The main-menu function - 
# an endless loop that prints the menu, gets input from user and 
# call the appropiate functions. 
mainMenu(){
	while true; do 
		clear;
		echo "**************"
		echo "Phonebook App"
		echo "**************"
		echo "Please select an option"
		echo "a) add a record "
		echo "s) search a record "
		echo "v) view all records "
		echo "d) delete a record "
		echo "e) erase all records "
		echo "q) quit "
		read -p 'Option:' -n 1 option
		# drops one line
		echo ""

		# That's how a 'switch'	looks like in bash
		case $option in
			a) addRecord ;;
			s) searchRecord ;;
			v) viewRecords ;;
			d) deleteRecord ;;
			e) eraseRecords ;;
			q) exit ;;
			*) echo "Please type a valid option" ; sleep 1 ;; 
		esac
	done
}

name_regex='^[A-Za-z ]+$'
number_regex='^[0-9]+$'

addRecord(){
	echo -n "Enter name to add to records and press [ENTER]: "
	read name
	echo -n "Enter phone number associate with name and press [ENTER]: "
	read number
	if [[ $name =~ $name_regex ]] && [[ $number =~ $number_regex ]]; then
		echo $name $number >> $DATA
	else
		echo "Either $name or $number were found invalid and weren't added to phonebook" 
		sleep 5
	fi
}

searchRecord(){
	echo -n "Enter name to search and press [ENTER]: "
	read name
	if [[ $name =~ $name_regex ]]; then
		result=`grep -wi $name $DATA`
		if [ ! -z "$result" ]; then echo "$result"
		else echo "$name not found in phonebook"
		fi
	else
		echo "$name isn't valid, please provide alphabetical name"
	fi
	echo -n "Press any key to return to menu"
	read -n 1 -s
}

viewRecords(){
	echo "Displaying Phonebook - Press any key to return to manu"
	cat $DATA
	read -n 1 -s
}

deleteRecord(){
	echo -n "Enter row number to delete from records and press [ENTER]: "
	read row_number
	if [[ $row_number =~ $number_regex ]] && [ $row_number -gt 0 ]; then
		sed -i "${row_number}d" $DATA
		echo "row number $row_number was deleted"
	else echo "$row_number isn't a valid number, please provide a number greater than zero"
	fi
	sleep 5
}

eraseRecords(){
	echo "Are you sure you want to erase all records?"
	read -p '[y/n]:' -n 1 option
	echo ""
	case $option in
		y) rm -r $WORKING_DIR ; echo "Record erase action complete" ; sleep 2 ;;
		n) echo "Record erase cancelled" ; sleep 2 ;;
	esac
}


mainMenu
