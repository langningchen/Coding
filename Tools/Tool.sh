#!/bin/fish
LuoguPattern=".*Luogu.*"
LuoguUsername="langningc2009"
LuoguPassword="1!2@3#qQwWeE"
EtigerPattern=".*Etiger.*"
EtigerUsername="18117121393"
EtigerPassword="LangNing0117"
UVaPattern=".*UVa.*"
UVaUsername="langningc2009"
UVaPassword="1!2@3#qQwWeE"
if [[ $1 =~ $EtigerPattern ]]
then
    /workspaces/Coding/Tools/Tool Etiger $EtigerUsername $EtigerPassword $2 ${1:0-8:4}
elif [[ $1 =~ $LuoguPattern ]]
then
    # echo /workspaces/Coding/Tools/Tool Luogu $LuoguUsername $LuoguPassword $2 ${1:0-9:5}
    /workspaces/Coding/Tools/Tool Luogu $LuoguUsername $LuoguPassword $2 ${1:0-9:5}
elif [[ $1 =~ $UVaPattern ]]
then
    # echo /workspaces/Coding/Tools/Tool UVa $UVaUsername $UVaPassword $2 ${1:0-9:5}
    /workspaces/Coding/Tools/Tool UVa $UVaUsername $UVaPassword $2 ${1:0-9:5}
else
    echo "Can not find pattern"
    exit 1
fi
