#!/bin/bash

TEMPDIR="out"
UNCRUSTIFY_BASE=$(dirname $0)

verbose="true"

while getopts :qh opt; do
	case $opt in
	q)
		verbose=""
		;;
	h)
		echo "run_uncrustify.sh [options] [<git diff args>]"
		echo ""
		echo "Check codestyle of a change. Change generated by bypassing"
		echo "diff-generating arguments to git-diff"
		echo ""
		echo "Options:"
		echo "-q : show only file names with codestyle issues, suppress"
		echo "     printing suggested fix"
		echo "-h : shows this message"
		exit 1
		;;
	?)
		break
		;;

	esac
done

# the rest will go to git diff directly
shift $(($OPTIND - 1))
diffargs="$@"

tmpundiff=$TEMPDIR/undiff
mkdir -p $tmpundiff

git diff --no-prefix $diffargs -- 'src/*.[ch]' | awk -v outpref=$tmpundiff -f $UNCRUSTIFY_BASE/undiff.awk

result=0

for f in $(cd $tmpundiff; find -type f); do
	from=$tmpundiff/$f 
	to=$TEMPDIR/fixed/$f
	mkdir -p $(dirname $to)

	uncrustify --frag -c $UNCRUSTIFY_BASE/uncrustify_cfg.ini -f $from > $to 2>/dev/null
	if [ ! -s $to ]; then 
		continue
	fi


	if [ $verbose ]; then 
		gitarg="--no-pager diff"
	else
		gitarg="diff --quiet"
	fi

	git $gitarg --no-index -- $from $to
	if [ $? != 0 ]; then
		[ $verbose ] || echo "Codestyle issue: $f"
		result=1
	fi
done

rm -rf $TEMPDIR
exit $result
