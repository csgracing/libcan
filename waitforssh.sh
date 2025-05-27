#!/bin/sh

ssh $1 $2
while test $? -gt 0
do
   sleep 5 # highly recommended - if it's in your local network, it can try an awful lot pretty quick...
   echo "Trying again..."
   ssh $1 $2
done