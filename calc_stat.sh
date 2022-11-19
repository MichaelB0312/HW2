#!/bin/bash
read argument
args_num=$(echo "$argument" | wc -w)
if(( args_num!=1 ));then
	echo "Wrong number of arguments" 1>&2
	exit 0
fi

