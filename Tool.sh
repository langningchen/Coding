LuoguPattern=".*Luogu.*"
LuoguUsername="langningc2009"
LuoguPassword="1!2@3#qQwWeE"
EtigerPattern=".*Etiger.*"
EtigerUsername="18117121393"
EtigerPassword="LangNing0117"
if [[ $1 =~ $EtigerPattern ]]
then
    ./Tool Etiger $EtigerUsername $EtigerPassword $2 ${1:0-8:4}
elif [[ $1 =~ $LuoguPattern ]]
then
    ./Tool Luogu $LuoguUsername $LuoguPassword $2 ${1:0-9:5}
else
    echo "Can not find"
    exit 1
fi
