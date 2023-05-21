#!/usr/bin/fish
clear
for mount_point in (mount | awk '{print $3}')
    if string match -q --regex "/home/Judger/Submissions/*" "$mount_point"
        umount "$mount_point"
    end
end
rm -rf "/home/Judger/Submissions" "/home/Judger/VerifyCodes"
mkdir "/home/Judger/Submissions" "/home/Judger/VerifyCodes"
rm -f (find "/home/Judger/" -name "*.log")
rm -f /home/langningc2009/Coding/Projects/OJ/Database/*.h
echo "Cleaned"
for SQLFile in (find ./Database -name "*.sql")
    python3 /home/langningc2009/sqlpp11/scripts/sqlite2cpp.py $SQLFile (echo $SQLFile | sed 's/\.sql//g') DatabaseTables
end
echo "Generated headers"
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
