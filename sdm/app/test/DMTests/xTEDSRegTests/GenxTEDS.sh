#!/bin/bash

FILES=`ls *.xml`

echo $FILES

for file in $FILES
do
	./xteds2str $file > ${file/xml/h}
done


