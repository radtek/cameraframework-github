#!/bin/sh

#=====================================================================================================
# cp libAFoundation's *.h
rm -rf $camfw_gwmv2_PATH/libAFoundation/include/
cp -rf 000_Framework/libAFoundation/include/ $camfw_gwmv2_PATH/libAFoundation/include/

# cp libAFoundation's libAFoundation.so
rm -rf $camfw_gwmv2_PATH/libAFoundation/lib/linux/
cp -rf 000_Framework/libAFoundation/lib/linux/ $camfw_gwmv2_PATH/libAFoundation/lib/linux/



#=====================================================================================================
# cp libABase's *.h
rm -rf $camfw_gwmv2_PATH/libABase/include/
cp -rf 000_Framework/libABase/include/ $camfw_gwmv2_PATH/libABase/include/

# cp libABase's libABase.so
rm -rf $camfw_gwmv2_PATH/libABase/lib/linux/
cp -rf 000_Framework/libABase/lib/linux/ $camfw_gwmv2_PATH/libABase/lib/linux/



#=====================================================================================================
# cp libACaseSocket's *.h
rm -rf $camfw_gwmv2_PATH/CaseClient/include/
cp -rf 000_Framework/CaseClient/include/ $camfw_gwmv2_PATH/CaseClient/include/

# cp libACaseSocket's libACaseSocket.so
rm -rf $camfw_gwmv2_PATH/CaseClient/lib/linux/
cp -rf 000_Framework/CaseClient/lib/linux/ $camfw_gwmv2_PATH/CaseClient/lib/linux/



#=====================================================================================================
# cp libAGraphic's *.h
rm -rf $camfw_gwmv2_PATH/libAGraphic/include/
cp -rf 000_Framework/libAGraphic/include/ $camfw_gwmv2_PATH/libAGraphic/include/

# cp libAGraphic's libAGraphic.so
rm -rf $camfw_gwmv2_PATH/libAGraphic/lib/linux/
cp -rf 000_Framework/libAGraphic/lib/linux/ $camfw_gwmv2_PATH/libAGraphic/lib/linux/