i=1
while [ $i -le 100 ]; do
  echo `./race1`
  i=`echo $i | awk '{ print $1+1 }'`
done
