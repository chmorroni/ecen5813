device_name=""
binary=""

while [ $# -gt "0" ]
do
    case "$1" in
	-b) binary=$2; shift;;
	-n) device_name=$2; shift;;
	-u) echo "$0: bare-metal software doesn't need to be uninstalled."; exit 0;;
	*) echo "usage: $0 [-b binary] [-n device_name]"
    esac
    shift
done

if [ "$device_name" = "" ]; then
    echo "Provide a device name to search for with the -n option."
    exit 1
else
    if [ "$binary" = "" ]; then
	echo "Provide a binary file to install with the -e option."
	exit 1
    fi
fi

echo "Looking for device in mounting table with name matching $device_name..."
df | grep $device_name >/dev/null 2>&1

if [ "$?" -eq "0" ]; then
    device=`df | grep $device_name | awk '{print $1}'`
    device_path=`df | grep $device_name | awk '{print $6}'`
    echo "Found $device_name on $device and mounted on $device_path."
else
    echo "$device_name not found."
    exit 2
fi

echo "Copying binary..."
cp $binary $device_path

if [ "$?" -eq "0" ]; then
    echo "Done."
    exit 0
else
    echo "Failed to copy binary - are you root?"
    exit 3
fi

