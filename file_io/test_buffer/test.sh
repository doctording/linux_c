#!/bin/bash

echo "please wait"
logfile=log

if [ -e $logfile ]
then
	rm $logfile
fi

# 可以利用find -size在系统中查找特定大小范围的文件
cpfile=apache-maven-3.3.9-bin.tar.gz 
filesize=`ls -lh $cpfile | awk '{print $5}'`
echo "cp a file,it's size is "$filesize >> $logfile

size=4 #字节数
maxsize=8192
while [ $size -le $maxsize ]
do
	echo "when buffersize = $size bytes,the cost is " >> $logfile
	filename=$size".cp"
	#echo $size
	./filecp.exe $cpfile $filename $size  >> $logfile #执行文件并传入参数
	let "size*=2"
done

rm *.cp

echo "success,the output in file named: $logfile"
