#!/bin/bash

if [ -z "$1" ]; then
	echo "Please specify the version number."
	exit
fi

sed -i s/android:versionName=\"[^\"]*\"/android:versionName=\"$1\"/ src/android/AndroidManifest.xml
sed -i s/std::string\ VERSION\ =\ \"[^\"]*\"/std::string\ VERSION\ =\ \"$1\"/ src/main.h
