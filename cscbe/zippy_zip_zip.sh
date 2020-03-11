filename=$1

rm -rf tmp
mkdir tmp
cp $filename tmp
cd tmp

while true
do
    filename=$(ls *)
    mv $filename myfile
    file myfile
    file myfile|grep "bzip2"
    if [ "$?" -eq "0" ]
    then
        bunzip2 myfile
    fi
    file myfile|grep "gzip"
    if [ "$?" -eq "0" ]
    then
        mv myfile myfile.gz
        gunzip myfile.gz
    fi

done

