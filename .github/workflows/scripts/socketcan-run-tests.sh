
cd build/sil-kit
./tools/run-silkit-qemu-demos-guest.sh &


# wait for system to be up
ssh -q -p10022 -oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null root@localhost -p root
while test $? -gt 0
do
   sleep 5
   ssh -q -p10022 -oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null root@localhost -p root
done

sshpass -proot ssh -q -p10022 -oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null root@localhost -p root -t "mkdir -p /work" || :
sshpass -proot scp -P10022 -oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null $1 root@localhost:/work/test || :
sshpass -proot ssh -q -p10022 -oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null root@localhost -p root -t "cd /work && ./test" || :

sshpass -proot ssh -q -p10022 -oStrictHostKeyChecking=no -oUserKnownHostsFile=/dev/null root@localhost -q -t "shutdown 00"