#detect i2c device address
i2cdetect -y -r 6

#insmod camera and intel ipu4 driver module
insmod /camera/max9286.ko
insmod /camera/crlmodule.ko
insmod /camera/intel-ipu4-acpi.ko
insmod /camera/videobuf2-memops.ko
insmod /camera/videobuf2-dma-contig.ko
insmod /camera/videobuf2-core.ko
insmod /camera/intel-ipu4-mod-bxtB0.ko
insmod /camera/intel-ipu4-mmu-bxtB0.ko
insmod /camera/intel-ipu4-isys-mod-bxtB0.ko
insmod /camera/intel-ipu4-psys-mod-bxtB0.ko

sleep 1

#make sure the v4l2 subdevices are created for sensor(programed address is 0x31 on i2c-6)
cat /sys/class/video4linux/v4l-subdev*/name

#capture the frames
ar1043_vc_test.sh 0 1280x720 UYVY

