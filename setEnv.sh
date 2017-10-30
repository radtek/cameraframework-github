#!/bin/sh

ADAS_ROOT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cpm_adas_adservice_PATH="$ADAS_ROOT_PATH/../cpm_adas_adservice"

sdkPATH="/opt/elina/2.0.2015143A"

alias sdk='cd $sdkPATH'

if [ -f "$sdkPATH/environment-setup-corei7-64-elina-linux" ]; then
    echo "SDK EXIT"
    echo "source environment-setup-corei7-64-elina-linux"
    source "$sdkPATH/environment-setup-corei7-64-elina-linux"
    echo "CXX" = $CXX
    echo "CC" = $CC
else
    echo "SDK do not EXIT"
    export CXX="g++"
    export CC="gcc"
    echo "set CXX = g++"
    echo "set CC = gcc"
fi

alias adas='cd $ADAS_ROOT_PATH'
alias greatwall='cd $cpm_adas_adservice_PATH'

alias foundation='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/src'
alias foundationlib='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux'

alias abase='cd $ADAS_ROOT_PATH/000_Framework/libABase'
alias abaselib='cd $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux'

alias graphic='cd $ADAS_ROOT_PATH/000_Framework/libAGraphic/src'
alias graphiclib='cd $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux'

alias caseclient='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/src/SocketIPC'
alias caseclientlib='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux'

alias project='cd $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/'

alias cmakeconfig='cmake -DELINA_LITE_DCIF_GENERATOR=/opt/elinaidelitelinux/elina -DCDEPL_PATH=$ADAS_ROOT_PATH/../contracts-gwm/contracts-gwm-v2mh/packages/adas/ADAS.cdl -DCMAKE_SYSROOT=/opt/elina/2.0.2015143A/sysroots/corei7-64-elina-linux  ../'

alias m='make'

alias c='printf "\033c"'

alias cm='printf "\033c" && make clean && make'

alias h='history'

alias opendir='nautilus .'

remoteIP="10.80.105.55"

alias pushfoundation='sudo scp $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux/libAFoundation.so root@$remoteIP://usr/lib/'
alias pushabase='sudo scp $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux/libABase.so root@$remoteIP://usr/lib/'
alias pushgraphic='sudo scp $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux/libAGraphic.so root@$remoteIP://usr/lib/'
alias pushcaseclient='sudo scp $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux/libACaseSocket.so root@$remoteIP://usr/lib/'
alias pushadasdbus='sudo scp $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/build/gen/libadas-dbus.so root@$remoteIP://usr/lib/'


alias pushbinadas='sudo scp $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/build/src/adas root@$remoteIP://usr/bin/'
alias pushproject='sudo scp $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Camera/Test/cameraStateTest root@$remoteIP://usr/bin/'