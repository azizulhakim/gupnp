#!/bin/bash

declare -i number lastoctet
for number in {1..10}
do
  echo $number
  lastoctet=200+$number
  interface=enp0s3:$number
  ifconfig $interface 10.0.2.$lastoctet
  ip="10.0.2."$lastoctet
  echo $ip
  ./light-server $interface 49153 &
done

exit 0
