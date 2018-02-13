echo "Searching for BBB at" $1 "\b..."
ping -nq -c 2 -w 2 $1 >/dev/null 2>&1
if [ "$?" -eq "0" ]; then
    scp $2 debian@$1:$3
else
    echo "BBB not found at" $1 "\b.\nPass a different IP through the BBB_ADDRESS flag."
    exit
fi
echo $2 "installed to" $3 "on remote"
