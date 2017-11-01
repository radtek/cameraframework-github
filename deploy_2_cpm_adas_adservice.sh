#!/bin/sh

# Everyone modify "cpm_adas_adservice_PATH" into Everyone's own
cpm_adas_adservice_PATH="../cpm_adas_adservice"



#=====================================================================================================
# cp libAFoundation's *.h
rm -rf $cpm_adas_adservice_PATH/libAFoundation/include/
cp -rf 000_Framework/libAFoundation/include/ $cpm_adas_adservice_PATH/libAFoundation/include/

# cp libAFoundation's libAFoundation.so
rm -rf $cpm_adas_adservice_PATH/libAFoundation/lib/linux/
cp -rf 000_Framework/libAFoundation/lib/linux/ $cpm_adas_adservice_PATH/libAFoundation/lib/linux/



#=====================================================================================================
# cp libABase's *.h
rm -rf $cpm_adas_adservice_PATH/libABase/include/
cp -rf 000_Framework/libABase/include/ $cpm_adas_adservice_PATH/libABase/include/

# cp libABase's libABase.so
rm -rf $cpm_adas_adservice_PATH/libABase/lib/linux/
cp -rf 000_Framework/libABase/lib/linux/ $cpm_adas_adservice_PATH/libABase/lib/linux/



#=====================================================================================================
# cp libACaseSocket's *.h
rm -rf $cpm_adas_adservice_PATH/CaseClient/include/
cp -rf 000_Framework/CaseClient/include/ $cpm_adas_adservice_PATH/CaseClient/include/

# cp libACaseSocket's libACaseSocket.so
rm -rf $cpm_adas_adservice_PATH/CaseClient/lib/linux/
cp -rf 000_Framework/CaseClient/lib/linux/ $cpm_adas_adservice_PATH/CaseClient/lib/linux/



#=====================================================================================================
# cp libAGraphic's *.h
rm -rf $cpm_adas_adservice_PATH/libAGraphic/include/
cp -rf 000_Framework/libAGraphic/include/ $cpm_adas_adservice_PATH/libAGraphic/include/

# cp libAGraphic's libAGraphic.so
rm -rf $cpm_adas_adservice_PATH/libAGraphic/lib/linux/
cp -rf 000_Framework/libAGraphic/lib/linux/ $cpm_adas_adservice_PATH/libAGraphic/lib/linux/



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