#!/usr/bin/env  bash

dname=$(dirname "$PWD")
realname=${dname##*/}


[ -d pass ] || mkdir pass
[ -d fail ] || mkdir fail
[ -d unknown ] || mkdir unknown
[ -d unsupport ] || mkdir unsupport

unsupports=("7_1_3_2"  "7_1_4_14" "7_1_5_2" "7_1_5_3" "7_1_5_4" "7_1_5_5")
for file in "${unsupports[@]}"; do
	target=$(find . -type d | grep $file  2>/dev/null )
	[ -z "$target" ] || mv "$target" unsupport/ 2>/dev/null
done

mv *_Passed-* pass/ 2>/dev/null
mv *_Failed-* *_Inconclusive-* fail/ 2>/dev/null
mv *_UNKNOWN* unknown/ 2>/dev/null

sleep 1

for i in */; do
    zip -rq "$realname""_""${i%/}.zip" "$i"
done

echo "make up successfully!"


