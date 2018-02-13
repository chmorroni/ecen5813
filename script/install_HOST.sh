install_path=""
executable=""
force=""
uninstall=""
while [ $# -gt "0" ]
do
    case "$1" in
	-e) executable=$2; shift;;
	-p) install_path=$2; shift;;
	-u) uninstall="true";;
	-f) force="true";;
	*) echo "usage: $0 [-fu] [-e executable] [-p install_path]"
    esac
    shift
done

if [ "$install_path" = "" ]; then
    echo "Provide an install path with the -p option."
    exit
else
    if [ "$executable" = "" ]; then
	echo "Provide an executable to install with the -e option."
	exit
    fi
fi

filename=`basename $executable .elf`

if [ "$uninstall" = "true" ]; then
    if [ -e "$install_path/$filename" ]; then
	rm -f "$install_path/$filename"
	echo "Uninstalled $install_path/$filename"
    else
	echo "$install_path/$filename not installed"
    fi
    exit
fi

if [ "$force" != "true" ]; then
    if [ -e "$install_path/$filename" ]; then
	echo "$install_path/$filename already installed"
	exit
    fi
else
    rm -f "$install_path/$filename"
fi

ln $executable $install_path/$filename >/dev/null 2>&1

if [ "$?" -eq "0" ]; then
    echo "Installed" $executable "into" $install_path
else
    echo "Could not install" $executable "into" $install_path "- are you root?"
fi
