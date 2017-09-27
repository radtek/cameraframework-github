#!/bin/sh

usage() {
	echo "Usage: $0 <cam_idx1 width1xheight1 fmt1> [cam_idxn widthnxheightn fmtn] ... "
	echo "fmt=RGB565/RGB888/YUYV/UYVY/SGRBG10/SGRBG12"
	echo "e.g: $0 0 1280x1088 SGRBG12 1 1280x1088 SGRBG12 2 1280x1088 SGRBG12 3 1280x1088 SGRBG12"
}

if [ $# -le 2 ]; then
	usage
	exit
fi

CAM_MAP=(-1 -1 -1 -1)
RES=("0x0" "0x0" "0x0" "0x0")
FMTS=("UYVY" "UYVY" "UYVY" "UYVY")

if [ $# -ge 3 ]; then
	i=$1
	RES[$i]=$2
	FMTS[$i]=$3
	CAM_MAP[0]=$i
	echo "Camera$i: ${RES[$i]} ${FMTS[$i]}"
fi

if [ $# -ge 6 ]; then
	i=$4
	RES[$i]=$5
	FMTS[$i]=$6
	CAM_MAP[1]=$i
	echo "Camera$i: ${RES[$i]} ${FMTS[$i]}"
fi

if [ $# -ge 9 ]; then
	i=$7
	RES[$i]=$8
	FMTS[$i]=$9
	CAM_MAP[2]=$i
	echo "Camera$i: ${RES[$i]} ${FMTS[$i]}"
fi

if [ $# -ge 12 ]; then
	i=${10}
	RES[$i]=${11}
	FMTS[$i]=${12}
	CAM_MAP[3]=$i
	echo "Camera$i: ${RES[$i]} ${FMTS[$i]}"
fi

FPS=30
BUFFER_NR=10
FRAME_COUNT=10
I2C_ADAPTER=6
CSI_PORT=0
DISPLAY=0
DISP_MODE=2

#SUPPORTED_RES=("1920x1080" "1280x720" "720x576" "640x480" "1920x540" "720x240" "720x288")

#ovl=200
#disp_win_h=$(expr 1920 \* 800 / $(expr 1280 \* 4 - 4 \* $ovl ))
#disp_win_w=$(expr $disp_win_h \* 1280 / 800)
#ovld=$(expr $disp_win_h \* $ovl / 800)
#pos1=$(expr $disp_win_w - $ovld)
#pos2=$(expr $pos1 + $disp_win_w - $ovld)
#pos3=$(expr $pos2 + $disp_win_w - $ovld)
#echo pos1=$pos1 pos2=$pos2 pos3=$pos3
#disp_win_pos=("0,0" "$pos1,0" "$pos2,0" "$pos3,0")

if [ $DISP_MODE -eq 1 ]; then
#   Cam2
#Cam3   Cam1
#   Cam0
disp_win_w=640
disp_win_h=400
disp_win_pos=("640,680" "1280,340" "640,0" "0,340")
elif [ $DISP_MODE -eq 2 ]; then
#Cam0  Cam1
#Cam2  Cam3
disp_win_w=960
disp_win_h=540
disp_win_pos=("0,0" "960,0" "0,540" "960,540")
fi

fmt_convert() {
	i=0
	for fmt in ${FMTS[*]}
	do
		if [ $fmt = "YUYV" ]; then
			FMTS[$i]="YUYV"
			FMTS_YAVTA[$i]="YUYV"
		fi
		if [ $fmt = "UYVY" ]; then
			FMTS[$i]="UYVY"
			FMTS_YAVTA[$i]="UYVY"
		fi
		if [ $fmt = "RGB565" ]; then
			FMTS[$i]="RGB16"
			FMTS_YAVTA[$i]="XRGB32"
		fi
		if [ $fmt = "RGB888" ]; then
			FMTS[$i]="RGB24"
			FMTS_YAVTA[$i]="XBGR32"
		fi
		if [ $fmt = "SGRBG10" ]; then
			FMTS[$i]="SGRBG10"
			FMTS_YAVTA[$i]="SGRBG10"
		fi
		if [ $fmt = "SBGGR10" ]; then
			FMTS[$i]="SBGGR10"
			FMTS_YAVTA[$i]="SBGGR10"
		fi
		if [ $fmt = "SRGGB10" ]; then
			FMTS[$i]="SRGGB10"
			FMTS_YAVTA[$i]="SRGGB10"
		fi
		if [ $fmt = "SGBRG10" ]; then
			FMTS[$i]="SGBRG10"
			FMTS_YAVTA[$i]="SGBRG10"
		fi
		if [ $fmt = "SGRBG12" ]; then
			FMTS[$i]="SGRBG12"
			FMTS_YAVTA[$i]="SGRBG12"
		fi
		if [ $fmt = "SBGGR12" ]; then
			FMTS[$i]="SBGGR12"
			FMTS_YAVTA[$i]="SBGGR12"
		fi
		if [ $fmt = "SRGGB12" ]; then
			FMTS[$i]="SRGGB12"
			FMTS_YAVTA[$i]="SRGGB12"
		fi
		if [ $fmt = "SGBRG12" ]; then
			FMTS[$i]="SGBRG12"
			FMTS_YAVTA[$i]="SGBRG12"
		fi
		echo  "FMTS[$i]=${FMTS[$i]}, FMTS_YAVTA[$i]=${FMTS_YAVTA[$i]}"
		i=$((i+1))
	done
}

main() {

	fmt_convert

	mkdir IMAGE_VC_BE_${RES[0]}_${FMTS[0]}_${RES[1]}_${FMTS[1]}_${RES[2]}_${FMTS[2]}_${RES[3]}_${FMTS[3]} 
	cd IMAGE_VC_BE_${RES[0]}_${FMTS[0]}_${RES[1]}_${FMTS[1]}_${RES[2]}_${FMTS[2]}_${RES[3]}_${FMTS[3]} 

	rm -rf stream*

	#yavta -w "0x00981982 1" $(media-ctl -e "Intel IPU4 CSI-2 $CSI_PORT")

	media-ctl -r

	for((j=0; j<4; j++))
	do
		m=`expr $j + 1`
		k=`expr $j + 8`
		media-ctl -v -t "\"Intel IPU4 CSI-2 $CSI_PORT\":0($j) => $m($j)[0]"
		media-ctl -v -t "\"Intel IPU4 CSI2 BE SOC\":$j($j) => $k($j)[0]"
		media-ctl -v -t "\"MAX9286 $I2C_ADAPTER-0048\":$j(0) => 4($j)[0]"
	done

	for j in ${CAM_MAP[*]}
	do
		if [ $j -eq -1 ]; then
			continue
		fi
		m=`expr $j + 1`
		k=`expr $j + 8`
		media-ctl -v -t "\"Intel IPU4 CSI-2 $CSI_PORT\":0($j) => $m($j)[1]"
		media-ctl -v -t "\"MAX9286 $I2C_ADAPTER-0048\":$j(0) => 4($j)[1]"
		media-ctl -v -t "\"Intel IPU4 CSI2 BE SOC\":$j($j) => $k($j)[1]"

		media-ctl -v -V "\"MAX9286 $I2C_ADAPTER-0048\":$j/0 [fmt:${FMTS[$j]}/${RES[$j]}]"
		media-ctl -v -V "\"MAX9286 $I2C_ADAPTER-0048\":4/$j [fmt:${FMTS[$j]}/${RES[$j]}]"

		media-ctl -v -V "\"Intel IPU4 CSI-2 $CSI_PORT\":0/$j [fmt:${FMTS[$j]}/${RES[$j]}]"
		m=`expr $j + 1`
		media-ctl -v -V "\"Intel IPU4 CSI-2 $CSI_PORT\":$m [fmt:${FMTS[$j]}/${RES[$j]}]"
		media-ctl -v -V "\"ar1043-max pixel array $I2C_ADAPTER-003$m\":0 [fmt:${FMTS[$j]}/1280x800]"
		media-ctl -v -V "\"ar1043-max binner $I2C_ADAPTER-003$m\":0 [fmt:${FMTS[$j]}/1280x800]"
		media-ctl -v -V "\"ar1043-max binner $I2C_ADAPTER-003$m\":0 [compose:(0,0)/${RES[$j]}]"
		media-ctl -v -V "\"ar1043-max binner $I2C_ADAPTER-003$m\":1 [fmt:${FMTS[$j]}/${RES[$j]}]"
		media-ctl -l "\"ar1043-max binner $I2C_ADAPTER-003$m\":1 -> \"MAX9286 $I2C_ADAPTER-0048\":$j[1]"

		media-ctl -v -V "\"Intel IPU4 CSI2 BE SOC\":$j [fmt:${FMTS[$j]}/${RES[$j]}]"
		media-ctl -v -V "\"Intel IPU4 CSI2 BE SOC\":$k [fmt:${FMTS[$j]}/${RES[$j]}]"

		media-ctl -l "\"Intel IPU4 CSI-2 $CSI_PORT\":$m -> \"Intel IPU4 CSI2 BE SOC\":$j[5]"
		media-ctl -l "\"Intel IPU4 CSI2 BE SOC\":$k -> \"Intel IPU4 BE SOC capture $j\":0[5]"
	done

	media-ctl -l "\"MAX9286 $I2C_ADAPTER-0048\":4 -> \"Intel IPU4 CSI-2 $CSI_PORT\":0[1]"
	
	sleep 4
	for j in ${CAM_MAP[*]}
	do
		if [ $j -eq -1 ]; then
			continue
		fi
		dev_node_stream=$(media-ctl -e "Intel IPU4 BE SOC capture $j")
		#width=$(echo ${RES[$j]} | awk -F 'x' '{print $1}')
		#height=$(echo ${RES[$j]} | awk -F 'x' '{print $2}')
		#if [ $DISPLAY -eq 1 ]; then
		#	WIN_X=$(echo ${disp_win_pos[$j]} | awk -F ',' '{print $1}')
		#	WIN_Y=$(echo ${disp_win_pos[$j]} | awk -F ',' '{print $2}')
		#	DISP_OPT="-D --winx=$WIN_X --winy=$WIN_Y --winw=$disp_win_w --winh=$disp_win_h"
		#else
		#	DISP_OPT=
		#	WIN_X=0
		#	WIN_Y=0
		#fi

		if [ $FPS -eq 1 ]; then
			FILE_OPT=
		else
			FILE_OPT="-Fstream_#_${RES[0]}_${FMTS_YAVTA[0]}_$j"
		fi

		#yavta --data-prefix -B capture -u $DISP_OPT -c$FRAME_COUNT -n$BUFFER_NR -I -s${RES[j]} $FILE_OPT -f ${FMTS_YAVTA[j]} $dev_node_stream &
		#yavta -u -c$FRAME_COUNT -n$BUFFER_NR -I -s${RES[j]} $FILE_OPT -f ${FMTS_YAVTA[j]} $dev_node_stream &
		#yavta --data-prefix -B capture -u -c$FRAME_COUNT -n$BUFFER_NR -I -s${RES[j]} $FILE_OPT -f ${FMTS_YAVTA[j]} $dev_node_stream &
		#yavta --skip 195 -u -c200 -n4 -I -s${RES[j]} -F -f ${FMTS_YAVTA[j]}  $dev_node_stream &
		#adas

	done

	wait
	echo "Done!"
}

main
