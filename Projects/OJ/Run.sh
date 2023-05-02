#!/usr/bin/fish
for mount_point in (mount | awk '{print $3}')
    if string match -q --regex "/home/Judger/Submissions/*" "$mount_point"
        umount "$mount_point"
    end
end
rm -rf "/home/Judger/Submissions" "/home/Judger/VerifyCodes"
mkdir "/home/Judger/Submissions" "/home/Judger/VerifyCodes"
rm -f (find -name "*.log")
echo "Cleaned"
cd ./build
make
cd ../
while true;
    if [ (echo (netstat -anp | grep ":80")) = "" ]
        break
    end
end
echo "Start running program..."
./build/main
