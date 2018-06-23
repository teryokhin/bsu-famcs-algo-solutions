while true
do
    ./testgen.out
    ./33.out
    mv output.txt ans.txt
    ./33_2.out
    if cmp -s "ans.txt" "output.txt" 
    then
        echo "OK"
    else
        echo "FAIL!"
        break
    fi
done