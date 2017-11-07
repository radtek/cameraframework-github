#!/bin/sh

#=====================================================================================================
# cp project's *.h
rm -rf $cpm_adas_adservice_PATH/include/
cp -rf 001_Project/001_GWMV2MH/include $cpm_adas_adservice_PATH/include/

# cp project's *.cpp
rm -rf $cpm_adas_adservice_PATH/src/
cp -rf 001_Project/001_GWMV2MH/src $cpm_adas_adservice_PATH/src/

# cp project's CMakeLists.txt
rm -rf $cpm_adas_adservice_PATH/CMakeLists.txt
cp -rf 001_Project/001_GWMV2MH/CMakeLists.txt $cpm_adas_adservice_PATH/CMakeLists.txt