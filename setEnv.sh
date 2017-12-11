#!/bin/sh

#============= tree : cameraframework ================================
export ADAS_ROOT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
alias adas='cd $ADAS_ROOT_PATH'

#============= tree : cameraframework/Test ===========================
alias ftest='cd $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/'

#============= tree : cpm_adas_adservice =============================
export cpm_adas_adservice_PATH="$ADAS_ROOT_PATH/../cpm_adas_adservice"
if [ -d "$cpm_adas_adservice_PATH/build" ]; then
    alias project='cd $cpm_adas_adservice_PATH/build && git branch -a && echo "" && echo "must work depends on owner branch (not master branch)" && echo ""'
else
    sudo mkdir -p $cpm_adas_adservice_PATH/build
    sudo chmod 777 -R $cpm_adas_adservice_PATH/build
    alias project='cd $cpm_adas_adservice_PATH/build && git branch -a && echo "" && echo "must work depends on owner branch (not master branch)" && echo ""'
fi

#============= tree : camfw_gwmv2 ====================================
export camfw_gwmv2_PATH="$ADAS_ROOT_PATH/../camfw_gwmv2"
alias publish='cd $camfw_gwmv2_PATH'

#============= tree : cpm-gwm-v2mh ====================================
export cpm_gwm_v2mh_PATH="$ADAS_ROOT_PATH/../cpm-gwm-v2mh"
alias bb='cd $cpm_gwm_v2mh_PATH'

#============= sdk ===================================================
export sdkPATH="/opt/elina/2.0.2015143A"
alias sdk='cd $sdkPATH'

#================= make cmd ==========================================
alias foundation='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/src'
alias foundationlib='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux'
alias makefoundation='foundation && cm'

alias abase='cd $ADAS_ROOT_PATH/000_Framework/libABase'
alias abaselib='cd $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux'
alias makeabase='abase && cm'

alias graphic='cd $ADAS_ROOT_PATH/000_Framework/libAGraphic'
alias graphiclib='cd $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux'
alias makegraphic='graphic && cm'

alias caseclient='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/src/SocketIPC'
alias caseclientlib='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux'
alias makecaseclient='caseclient && cm'

alias cmakeconfig='cmake -DELINA_LITE_DCIF_GENERATOR=/opt/elinaidelitelinux/elina -DCDEPL_PATH=$ADAS_ROOT_PATH/../contracts-gwm/contracts-gwm-v2mh/packages/adas/ADAS.cdl -DCMAKE_SYSROOT=/opt/elina/2.0.2015143A/sysroots/corei7-64-elina-linux  ../'

alias makelib='makefoundation && makeabase && makegraphic && makecaseclient && adas'
alias makeproject='project && rm -fr * && cmakeconfig && make target && adas'
alias makecamera='ftest && cd camera && cm'
alias makeguideline='ftest && cd guideline && cm'


#=================make a distinction between platform[ubuntu/board]===
if [ x$1 = x ]; then
    echo ""
    echo "=====platform [board]======"
    echo ""
    export PLATFORM="board"

    if [ -f "$sdkPATH/environment-setup-corei7-64-elina-linux" ]; then
        source "$sdkPATH/environment-setup-corei7-64-elina-linux"
        echo "CXX" = $CXX
        echo "CC" = $CC
        export CMAKE_SYSROOT="$sdkPATH/sysroots/corei7-64-elina-linux"

        echo ""

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

        echo ""
        echo "cp *.h ========> "$CMAKE_SYSROOT/usr/include/adas
        echo "cp *.so ========> "$CMAKE_SYSROOT/usr/lib/adas
        echo ""
        echo "make sure dir : /opt/elina/  &&  /opt/elinaidelitelinux/"
        echo ""
        echo "using cmd : [adas] go to Tree : cameraframework"
        echo "using cmd : [publish] go to Tree : camfw_gwmv2"
        echo "using cmd : [project] go to Tree : cpm_adas_adservice/build"
        echo "using cmd : [ftest] go to Tree : cameraframework/001_Project/001_GWMV2MH/"
        echo ""
        echo "using cmd : [makelib] to build (*.so)"
        echo "using cmd : [makeproject] to build (greatwall project)"
        echo "using cmd : [makecamera] to build (cameraStateTest)"
        echo "using cmd : [makeall] to build (*.so + project + cameraStateTest)"
        echo ""
        echo "using cmd : [pushlib] push (*.so) to board"
        echo "using cmd : [pushproject] push (libadas-dbus.so + adas) to board"
        echo "using cmd : [pushcamera] push (cameraStateTest) to board"
        echo "using cmd : [pushall] push (*.so + libadas-dbus.so + adas + cameraStateTest) to board"
        echo ""

        alias makeall='makelib && makecamera && makeproject  && adas'

    else
        echo "SDK do not EXIT"
        export CXX="g++"
        export CC="gcc"
        echo "set CXX = g++"
        echo "set CC = gcc"
        echo ""
        echo "cp *.h ========> nowhere"
        echo "cp *.so ========> /usr/lib"
        echo ""
        echo "using cmd : [adas] go to Tree : cameraframework"
        echo "using cmd : [ftest] go to Tree : cameraframework/001_Project/001_GWMV2MH/"
        echo ""
        echo "using cmd : [makelib] to build (*.so)"
        echo "using cmd : [makecamera] to build (cameraStateTest)"
        echo "using cmd : [makeall] to build (*.so + cameraStateTest)"
        echo ""
        alias makeall='makelib && makecamera && adas'

    fi
else
    if [ $1 = "ubuntu" ]; then
        echo ""
        echo "=====platform [ubuntu]====="
        echo ""
        export PLATFORM="ubuntu"
    else
        echo ""
        echo "=====platform [unknow]====="
        echo ""
        export PLATFORM="unknow"
    fi

    export CXX="g++"
    export CC="gcc"
    echo "set CXX = g++"
    echo "set CC = gcc"
    echo ""
    echo "cp *.h ========> nowhere"
    echo "cp *.so ========> /usr/lib"
    echo ""
    echo "using cmd : [adas] go to Tree : cameraframework"
    echo "using cmd : [ftest] go to Tree : cameraframework/001_Project/001_GWMV2MH/"
    echo ""
    echo "using cmd : [makelib] to build (*.so)"
    echo "using cmd : [makecamera] to build (cameraStateTest)"
    echo "using cmd : [makeall] to build (*.so + cameraStateTest)"
    echo ""
    alias makeall='makelib && makecamera && adas'
fi


#================= compile cmd ======================================

alias m='make'

alias c='printf "\033c"'

alias mc='make clean'

alias cm='printf "\033c" && make clean && make'

alias h='history'

alias opendir='nautilus .'

#================= deploy to board ======================================


#------------------------------------li hui----------------------------------------------
remoteIP="10.80.105.55"

alias board='ssh root@$remoteIP'
alias remote='ssh snow@10.80.105.179'

alias pushfoundation='sudo scp $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux/libAFoundation.so root@$remoteIP://usr/lib/adas/ && sudo scp $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux/libAFoundation.so root@$remoteIP://usr/lib/'
alias pushabase='sudo scp $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux/libABase.so root@$remoteIP://usr/lib/adas/ && sudo scp $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux/libABase.so root@$remoteIP://usr/lib/'
alias pushgraphic='sudo scp $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux/libAGraphic.so root@$remoteIP://usr/lib/adas/ && sudo scp $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux/libAGraphic.so root@$remoteIP://usr/lib/'
alias pushcaseclient='sudo scp $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux/libACaseSocket.so root@$remoteIP://usr/lib/adas/ && sudo scp $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux/libACaseSocket.so root@$remoteIP://usr/lib/'
alias pushlib='sudo scp $CMAKE_SYSROOT/usr/lib/adas/*.so root@$remoteIP://usr/lib/adas/ && sudo scp $CMAKE_SYSROOT/usr/lib/adas/*.so root@$remoteIP://usr/lib/'

alias pushadasdbus='sudo scp $cpm_adas_adservice_PATH/build/gen/libadas-dbus.so root@$remoteIP://usr/lib/adas/ && sudo scp $cpm_adas_adservice_PATH/build/gen/libadas-dbus.so root@$remoteIP://usr/lib/'
alias pushadas='sudo scp $cpm_adas_adservice_PATH/build/src/adas root@$remoteIP://usr/bin/'
alias pushproject='pushadasdbus && pushadas'

alias pushcamera='sudo scp $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/camera/cameraStateTest root@$remoteIP://usr/bin/'

alias pushall='pushlib && pushproject && pushcamera'
#------------------------------------li hui----------------------------------------------

#------------------------------------lin nan----------------------------------------------
remoteIPnlin="10.80.104.165"

alias npushfoundation='sudo scp $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux/libAFoundation.so root@$remoteIPnlin://usr/lib/'
alias npushabase='sudo scp $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux/libABase.so root@$remoteIPnlin://usr/lib/'
alias npushgraphic='sudo scp $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux/libAGraphic.so root@$remoteIPnlin://usr/lib/'
alias npushcaseclient='sudo scp $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux/libACaseSocket.so root@$remoteIPnlin://usr/lib/'
alias npushlib='npushfoundation && npushabase && npushgraphic && npushcaseclient'
alias pushguideline='sudo scp $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/guideline/GuideLineTest root@$remoteIPnlin://usr/bin/'

alias cleanfoundation='foundation && mc'
alias cleanabase='abase && mc'
alias cleangraphic='graphic && mc'
alias cleancaseclient='caseclient && mc'
alias cleanlib='cleanfoundation && cleanabase && cleangraphic && cleancaseclient'
alias cleanguideline='ftest && cd guideline && mc'
#------------------------------------lin nan----------------------------------------------