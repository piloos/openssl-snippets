
runs=$1
abspath=$(readlink -f $0)
currdir=$(dirname $abspath)

echo Going to generate $runs private keys...

i=0
successes=0
failures=0

while [ $i -lt $runs ]
do
  let i++
  ${currdir}/generate_priv_key.o
  ret=$?
  if [ $ret -eq 0 ]
  then
    let successes++
  else
    let failures++
  fi
done

echo Attempted to generate $runs private keys...
echo ...$successes successes
echo ...$failures failures

if [ $failures -gt 0 ]
then
  exit 1
else
  exit 0
fi
