# 删除tmp文件夹和结果文件
if [ -f "date" ]; then 
   rm -rf date
fi 
# 删除tmp文件夹
if [ -d "tmp" ]; then 
	 rm -rf tmp
fi
# 创建tmp文件夹
mkdir tmp
path=$1
files=$(ls $path)
# 遍历文件 将前8个字符相同的文件名放入一个文件中
for file in $files
do 
	if [ -f $path/$file ]
	then
		if [ -f tmp/${file:0:8} ]
		then
			cat $path/$file >> tmp/${file:0:8}
		else
			touch tmp/${file:0:8}
			cat $path/$file >> tmp/${file:0:8}
		fi
	fi
done

# 统计两个文件中关键词出现的次数
res=$(ls tmp)

for f in $res 
do 
  # 使用awk 统计 用空格间隔的第一个字段 抽出stu的学生字段，排序,去重后输入到结果文件
  awk '{print $1}' tmp/$f | grep 'stu' | sort -n | uniq >> d
done

for id in $(cat d|sort -n|uniq)
do
    num=$(grep -c $id d)
    echo "$id:$num"
done
rm -rf d
rm -rf tmp
exit 0
