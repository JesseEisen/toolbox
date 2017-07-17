#!/usr/bin/env  bash

csvfile="Pct_Case_Result_Band41 .CSV"
result="res.csv"
dos2unix "$csvfile" 2>/dev/null
awk 'BEGIN{FS=","} {gsub(/\./,"_",$1); printf("%s,%s\n", $1,$5)}' "$csvfile" > "$result"
sed -i '1,2d' "$result"
sed -i '240,$d' "$result"

declare -A res
while IFS="," read f1 f2
do
    res[$f1]=$f2
done < "$result"

[ -d failed ] || mkdir failed
[ -d passed ] || mkdir passed

regex_six="^6.*$"
regex_seven="^7.*$"
regex_eight="^8.*$"
regex_nine="^9.*$"
regex_ten="^[1][0].*$"
regex_eleven="^[1][1].*$"
regex_twelve="^[1][2].*$"
regex_thirteen="^[1][3].*$"

move() {
    local target
    local tdir="$2""$3"
    [ -d $tdir ] || mkdir $tdir
    
   target=($(find . -maxdepth 1 -type d | grep "$1"  2>/dev/null ))
    for t in "${target[*]}"
    do
        [ -z "$t" ] || mv "$t" "$tdir" 2>/dev/null
    done
}

classification() {
       if [[  $1 =~ $regex_six ]];then
           move "$1" "$2" "chapter_6" 
       elif [[ $1 =~ $regex_seven ]]; then
           move "$1" "$2" "chapter_7"
       elif [[ $1 =~ $regex_eight ]]; then
           move "$1" "$2" "chapter_8"
       elif [[ $1 =~ $regex_nine ]]; then
           move "$1" "$2" "chapter_9"
       elif [[ $1 =~ $regex_ten ]]; then
           move "$1" "$2" "chapter_10"
       elif [[ $1 =~ $regex_eleven ]]; then
           move "$1" "$2" "chapter_11"
       elif [[ $1 =~ $regex_twelve ]]; then
           move "$1" "$2" "chapter_12"
       elif [[ $1 =~ $regex_thirteen ]]; then
           move "$1" "$2" "chapter_13"
       else
           move "$1" "$2" "unknown"
       fi
}

excute() {
    for k in "${!res[@]}"
    do
        temp="${res[$k]}"
        if [[ "$temp" == Failed ]]; then
            classification $k "./failed/"
        else
            classification $k "./passed/"
        fi
    done
}

excute
excute
echo "split complete..."

compress() {
    cd "$1"
    for f in ./*
    do
      zip -rqm "$f".zip "$f"
       # echo "$f"
    done
    cd ..
}

echo "start compress..."

if [[ "$1" == "-c" ]]; then
    compress "passed"
    compress "failed"
fi

rm -rf res.csv
echo "finished!!"
