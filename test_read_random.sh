
killcount=0

handler()
{
    killall read_random.o
    echo -e "\n\nPerformed $killcount kills\n"
    exit 0
}

currdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo $currdir

trap handler SIGINT
trap handler SIGTERM

#start the read_random process
${currdir}/read_random.o &
pid=$!
echo $pid

#give the process some time to setup
sleep 1

#fire SIGINTs on the process
while [ 1 ]
do
    kill -s SIGINT $pid
    let killcount++
done

#kill the read_random process
kill $pid
