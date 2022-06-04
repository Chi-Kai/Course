#输入一个数字n，打印出1-n之间的所有数字，去掉包含7的数字和7的倍数
#!/bin/sh

#请输入n
read -p "请输入n: " n
for i in `seq 1 $n`
do
    #转换为字符串
    str=$i
		#判断是否包含7
		if [ `expr $i % 7` -eq 0 ] || [[ $str =~ 7 ]]
		then
				continue
		else
				echo $i
		fi
done
