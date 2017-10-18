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