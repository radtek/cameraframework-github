
export ADAS_ROOT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

alias adas='cd $ADAS_ROOT_PATH'
alias ADAS='cd $ADAS_ROOT_PATH'
alias foundation='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/src'
alias FOUNDATION='cd $ADAS_ROOT_PATH/000_Framework/libAFoundation/src'
alias caseclient='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/src/SocketIPC'
alias CASECLIENT='cd $ADAS_ROOT_PATH/000_Framework/CaseClient/src/SocketIPC'
alias abase='cd $ADAS_ROOT_PATH/000_Framework/libABase'
alias ABASE='cd $ADAS_ROOT_PATH/000_Framework/libABase'
alias project='cd $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Camera/Test'
alias PROJECT='cd $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Camera/Test'

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
