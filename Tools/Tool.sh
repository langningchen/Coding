EtigerUsername=$(cat /workspaces/Coding/Keys/EtigerUsername.tmp);
EtigerPassword=$(cat /workspaces/Coding/Keys/EtigerPassword.tmp);
LuoguUsername=$(cat /workspaces/Coding/Keys/LuoguUsername.tmp);
LuoguPassword=$(cat /workspaces/Coding/Keys/LuoguPassword.tmp);
UVaUsername=$(cat /workspaces/Coding/Keys/UVaUsername.tmp);
UVaPassword=$(cat /workspaces/Coding/Keys/UVaPassword.tmp);
if echo "$1" | grep "Etiger" > /dev/null
then
    /workspaces/Coding/Tools/Tool Etiger $EtigerUsername $EtigerPassword $2 ${1:0-8:4}
elif echo "$1" | grep "Luogu" > /dev/null
then
    /workspaces/Coding/Tools/Tool Luogu $LuoguUsername $LuoguPassword $2 ${1:0-9:5}
elif echo "$1" | grep "UVa" > /dev/null
then
    /workspaces/Coding/Tools/Tool UVa $UVaUsername $UVaPassword $2 ${1:0-9:5}
else
    echo "Can not find pattern"
    exit 1
fi
