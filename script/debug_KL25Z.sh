binary=""

while [ $# -gt "0" ]
do
  case "$1" in
    -b) binary=$2; shift;;
    *) echo "usage: $0 [-b binary]"
  esac
  shift
done

path=$(find /opt -iname pegdbserver_console)
if [ "$path" = "" ]; then
  echo "Could not find PNE GDB server console."
  exit 1
fi

#nohup
echo "Starting PNE GDB server"
#x-terminal-emulator -e "/opt/Freescale/KDS_v3/eclipse/plugins/com.pemicro.debug.gdbjtag.pne_2.3.6.201602211227/lin/pegdbserver_console -device=NXP_KL2x_KL25Z128M4 -startserver -singlesession -serverport=7224 -interface=OPENSDA -speed=5000 -port=USB1"
x-terminal-emulator -e "$path -device=NXP_KL2x_KL25Z128M4 -startserver -singlesession -serverport=7224 -interface=OPENSDA -speed=5000 -port=USB1"

sleep 5

echo "Starting GDB with binary: $binary"
arm-none-eabi-gdb -ex "target remote localhost:7224" -ex "load $binary" -ex "symbol-file $binary"
