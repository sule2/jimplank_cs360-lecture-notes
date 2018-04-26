#/bin/sh

if [ $# -ne 4 ]; then
  echo 'usage: sh kill_it.sh host port nentries nclients' >&2
  exit 1
fi

i=0
while [ $i -lt $4 ]; do
  ./inclient $1 $2 $3 $i lns > /dev/null &
  i=`echo $i + 1 | bc`
done

i=0
while [ $i -lt $4 ]; do
  wait
  i=`echo $i + 1 | bc`
done
