i=1
while [ $i -lt `wc commands-for-teaching.txt | awk '{ print $1 }'` ]; do
  l=`sed -n "$i"p commands-for-teaching.txt`
  echo $l
  if [ "$l"a == a ]; then
    read b
  fi
  i=`echo $i | awk '{ print $1+1 }'`
done
