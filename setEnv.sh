#!/bin/sh

export ADAS_ROOT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

sdkPATH="/opt/elina/2.0.2015143A"

alias sdk='cd $sdkPATH'
alias SDK='cd $sdkPATH'

if [ -f "$sdkPATH/environment-setup-corei7-64-elina-linux" ]; then  
	echo "SDK EXIT" 
	echo "source environment-setup-corei7-64-elina-linux" 
	source "$sdkPATH/environment-setup-corei7-64-elina-linux"
else  
	echo "SDK do not EXIT"
	echo "set CXX = g++"
	echo "set CC = gcc"
#export CXX="g++"
#export CC="gcc"
fi  

alias adas='cd $ADAS_ROOT_PATH'
alias ADAS='cd $ADAS_ROOT_PATH'

alias foundation='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/src'
alias foundationlib='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux'

alias caseclient='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/src/SocketIPC'
alias caseclientlib='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux'

alias abase='cd $ADAS_ROOT_PATH/000_Framework/libABase'
alias abaselib='cd $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux'

alias project='cd $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Camera/Test'

alias m='make'
alias M='make'

alias c='printf "\033c"'
alias C='printf "\033c"'

alias cm='printf "\033c" && make clean && make'
alias CM='printf "\033c" && make clean && make'

alias h='history'
alias H='history'

alias opendir='nautilus .'
alias OPENDIR='nautilus .'

alias pushfoundation='sudo scp $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux/libAFoundation.so root@10.80.105.21://usr/lib/'
alias pushabase='sudo scp $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux/libABase.so root@10.80.105.21://usr/lib/'
alias pushcaseclient='sudo scp $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux/libACaseSocket.so root@10.80.105.21://usr/lib/'
alias pushproject='sudo scp $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Camera/Test/cameraStateTest root@10.80.105.21://usr/bin/'
