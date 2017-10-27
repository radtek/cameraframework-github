#!/bin/bash

Board_IP="10.80.105.55"

#sudo scp -p ./004_ToBoard/camera_setup.sh   root@10.80.105.48://
#sudo scp -p ./004_ToBoard/ar1043_vc_test.sh   root@10.80.105.48://usr/bin
#sudo scp -p ./004_ToBoard/yavta ./004_ToBoard/yavtaAdas ./004_ToBoard/media-ctl  root@10.80.105.48://usr/bin/
#sudo scp -p ./004_ToBoard/media-ctl  root@10.80.105.48://usr/bin/
#sudo scp -p ./004_ToBoard/adas  root@10.80.105.48://usr/bin/
#sudo scp ./004_ToBoard/libmediactl.so.0.0.0     root@10.80.105.48://usr/lib/
#sudo scp ./004_ToBoard/libv4l2subdev.so.0.0.0    root@10.80.105.48://usr/lib/

sudo scp  $ADAS_ROOT_PATH/000_Framework/libAFoundation/lib/linux/libAFoundation.so root@$Board_IP://usr/lib/
sudo scp  $ADAS_ROOT_PATH/000_Framework/libABase/lib/linux/libABase.so root@$Board_IP://usr/lib/
sudo scp  $ADAS_ROOT_PATH/000_Framework/CaseClient/lib/linux/libACaseSocket.so root@$Board_IP://usr/lib/
sudo scp -p $ADAS_ROOT_PATH/001_Project/001_GWMV2MH/src/Camera/Test/cameraStateTest root@$Board_IP://usr/bin/