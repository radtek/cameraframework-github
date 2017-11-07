#!/bin/bash

remoteIP="10.80.105.55"

#sudo scp -p ./004_ToBoard/camera_setup.sh   root@10.80.105.48://
#sudo scp -p ./004_ToBoard/ar1043_vc_test.sh   root@10.80.105.48://usr/bin
#sudo scp -p ./004_ToBoard/yavta ./004_ToBoard/yavtaAdas ./004_ToBoard/media-ctl  root@10.80.105.48://usr/bin/
#sudo scp -p ./004_ToBoard/media-ctl  root@10.80.105.48://usr/bin/
#sudo scp -p ./004_ToBoard/adas  root@10.80.105.48://usr/bin/
#sudo scp ./004_ToBoard/libmediactl.so.0.0.0     root@10.80.105.48://usr/lib/
#sudo scp ./004_ToBoard/libv4l2subdev.so.0.0.0    root@10.80.105.48://usr/lib/

sudo scp  $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux/libAFoundation.so root@$remoteIP://usr/lib/
sudo scp  $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux/libABase.so root@$remoteIP://usr/lib/
sudo scp  $ADAS_ROOT_PATH/000_Framework/libAGraphic/lib/linux/libAGraphic.so root@$remoteIP://usr/lib/
sudo scp  $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux/libACaseSocket.so root@$remoteIP://usr/lib/
sudo scp  $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/build/gen/libadas-dbus.so root@$remoteIP://usr/lib/


sudo scp -p  $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/build/src/adas root@$remoteIP://usr/bin/
# sudo scp -p  $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Camera/Test/cameraStateTest root@$remoteIP://usr/bin/


#sudo scp -p  $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Pas/config/pdcusr.cfg root@$remoteIP://usr/share/pdcusr.cfg
#sudo scp -p -r  $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Pas/res/Night_Camera root@$remoteIP://usr/share/Night_Camera
