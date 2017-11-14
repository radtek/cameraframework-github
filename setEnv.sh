#!/bin/sh



# if [ $# -eq 0 ]
#     then echo "add args : ubuntu passwd  |  eg. source setEnv.sh aaaa"
#     return
# else
#     for a in $*
#     do
#         passwd=$a
#         echo $passwd
# done
# fi



export ADAS_ROOT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export cpm_adas_adservice_PATH="$ADAS_ROOT_PATH/../cpm_adas_adservice"
export camfw_gwmv2_PATH="$ADAS_ROOT_PATH/../camfw_gwmv2"

export sdkPATH="/opt/elina/2.0.2015143A"

alias sdk='cd $sdkPATH'

if [ -f "$sdkPATH/environment-setup-corei7-64-elina-linux" ]; then
    echo "SDK EXIT"
    echo "source environment-setup-corei7-64-elina-linux"
    source "$sdkPATH/environment-setup-corei7-64-elina-linux"
    echo "CXX" = $CXX
    echo "CC" = $CC
    export CMAKE_SYSROOT="/opt/elina/2.0.2015143A/sysroots/corei7-64-elina-linux"

    if [ -d "$CMAKE_SYSROOT/usr/include/adas" ]; then
		echo "adas(include) dir exist"
    else
        sudo mkdir -p $CMAKE_SYSROOT/usr/include/adas
		echo "adas(include) dir create ok"
    fi

	if [ -d "$CMAKE_SYSROOT/usr/lib/adas" ]; then
		echo "adas(lib) dir exist"
	else
	    sudo mkdir -p $CMAKE_SYSROOT/usr/lib/adas
		echo "adas(lib) dir create ok"
	fi

else
    echo "SDK do not EXIT"
    export CXX="g++"
    export CC="gcc"
    echo "set CXX = g++"
    echo "set CC = gcc"
fi


alias adas='cd $ADAS_ROOT_PATH'
alias publish='cd $camfw_gwmv2_PATH'
if [ -d "$cpm_adas_adservice_PATH/build" ]; then
    alias project='cd $cpm_adas_adservice_PATH/build && git branch -a && echo "" && echo "must work depends on owner branch (not master branch)" && echo ""'
else
    sudo mkdir -p $cpm_adas_adservice_PATH/build
	sudo chmod 777 -R $cpm_adas_adservice_PATH/build
    alias project='cd $cpm_adas_adservice_PATH/build && git branch -a && echo "" && echo "must work depends on owner branch (not master branch)" && echo ""'
fi

alias ftest='cd $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/'

alias foundation='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/src'
alias foundationlib='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux'

alias abase='cd $ADAS_ROOT_PATH/000_Framework/libABase'
alias abaselib='cd $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux'

alias graphic='cd $ADAS_ROOT_PATH/000_Framework/libAGraphic'
alias graphiclib='cd $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux'

alias caseclient='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/src/SocketIPC'
alias caseclientlib='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux'

alias cmakeconfig='cmake -DELINA_LITE_DCIF_GENERATOR=/opt/elinaidelitelinux/elina -DCDEPL_PATH=$ADAS_ROOT_PATH/../contracts-gwm/contracts-gwm-v2mh/packages/adas/ADAS.cdl -DCMAKE_SYSROOT=/opt/elina/2.0.2015143A/sysroots/corei7-64-elina-linux  ../'

alias m='make'

alias c='printf "\033c"'

alias mc='make clean'

alias cm='printf "\033c" && make clean && make'

alias makeall='foundation && cm  &&  abase && cm  &&  caseclient && cm  &&  graphic && cm  && project && rm -fr * && cmakeconfig && make target'


alias mfoundation='foundation && cm'
alias mabase='abase && cm'
alias magraphic='graphic && cm'
alias mcaseclient='caseclient && cm'

alias makealllib='foundation && cm  &&  abase && cm  &&  caseclient && cm  &&  graphic && cm'

alias h='history'

alias opendir='nautilus .'

remoteIP="10.80.105.55"

alias board='ssh root@$remoteIP'

alias remote='ssh snow@10.80.105.179'


#echo -n "snow" | sudo -S $(CP) -fv ../lib/linux/libAFoundation.so /opt/elina/2.0.2015143A/sysroots/corei7-64-elina-linux/lib/

#echo -n $passwd | sudo -S $(CP) -fv ../lib/linux/libAFoundation.so /opt/elina/2.0.2015143A/sysroots/corei7-64-elina-linux/lib/

alias pushfoundation='sudo scp $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux/libAFoundation.so root@$remoteIP://usr/lib/'
alias pushabase='sudo scp $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux/libABase.so root@$remoteIP://usr/lib/'
alias pushgraphic='sudo scp $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux/libAGraphic.so root@$remoteIP://usr/lib/'
alias pushcaseclient='sudo scp $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux/libACaseSocket.so root@$remoteIP://usr/lib/'

alias pushadasdbus='sudo scp $cpm_adas_adservice_PATH/build/gen/libadas-dbus.so root@$remoteIP://usr/lib/'
alias pushadas='sudo scp $cpm_adas_adservice_PATH/build/src/adas root@$remoteIP://usr/bin/'

alias pushproject='sudo scp $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Camera/Test/cameraStateTest root@$remoteIP://usr/bin/'
