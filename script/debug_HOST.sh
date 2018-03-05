binary=""

while [ $# -gt "0" ]
do
  case "$1" in
    -b) binary=$2; shift;;
    *) echo "usage: $0 [-b binary]"
  esac
  shift
done

echo "Starting GDB with binary: $binary"
gdb "./$binary"
