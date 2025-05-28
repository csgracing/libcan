#!/bin/bash

# $1 - pwd
# $2 - path from pwd to test binary

port=10022
host=root@localhost

get_params() {
    echo "-oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null"
}

# do_ssh "<cmd>"
do_ssh () {
    sshpass -proot ssh -q -p$port $(get_params) $host -t  $1
}

do_scp ()  {
    sshpass -proot scp -P$port $(get_params) -r $1 $2
}

echo "::group::vm: booting virtual machine"

cd build/sil-kit

# start vm in background, note that the image will verbose log kernel messages!
./tools/run-silkit-qemu-demos-guest.sh & 

pid = $!

# wait for system to be up
do_ssh "echo success"
while test $? -gt 0
do
   sleep 5
   echo "unable to connect. sleeping for 5 seconds..."
   # wait for system to be up
   do_ssh "echo success"
done

echo "::endgroup::"
echo "::group::vm: loading can kernel modules"

do_ssh "modprobe -a can can-dev can-raw can-isotp vcan" || :

echo "::endgroup::"
echo "::group::vm: adding virtual can interface"

do_ssh "ip link add dev vcan0 type vcan" || :
do_ssh "ip link set up vcan0" || :

echo "::endgroup::"
echo "::group::vm: copying test binary"

do_ssh "mkdir -p /work" || :
do_scp $1/$2 $host:/work/test || :

echo "::endgroup::"
echo "::group::vm: executing test binary"

do_ssh "cd /work && ./test --gtest_output=xml" || :

echo "::endgroup::"
echo "::group::vm: copying test results"

do_scp $host:/work/test_detail.xml $1/ || :

echo "::endgroup::"
echo "::group::vm: copying coverage data"

do_scp $host:$1/build $1/ || :

echo "::endgroup::"
echo "::group::vm: shutting down virtual machine"

do_ssh "shutdown 00"

wait $pid

echo "::endgroup::"