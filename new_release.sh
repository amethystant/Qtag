#!/bin/bash

if [ $# -lt 3 ]; then
	echo "An argument is missing. Specify the version number, the current date in m/d/y format, and the changes you made in the other arguments."
	exit
fi

sed -i s/android:versionName=\"[^\"]*\"/android:versionName=\"$1\"/ src/android/AndroidManifest.xml
sed -i s/std::string\ VERSION\ =\ \"[^\"]*\"/std::string\ VERSION\ =\ \"$1\"/ src/main.h

touch file

num_of_changes=$(($# - 2))

echo "$2 *Qtag $1" > file

for i in "$@"
do
	if [ "$1" == "$i" ] || [ "$2" == "$i" ]; then
		continue
	fi

	echo "        - $i" >>file
done

echo "" >>file

echo "PLEASE CHECK THE CHANGELOG BELLOW AND FIX IT IN CASE YOU NEED IT:"
echo ""
cat file
cat file CHANGELOG > tmpfile
cat tmpfile > CHANGELOG
rm file tmpfile
