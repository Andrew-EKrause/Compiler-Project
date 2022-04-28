#!/bin/sh

failed=0
echo -e "\n   +===========================+"
echo -e "  /\033[1;36m   Kwin Compiler Tester    \033[0m/"
echo -e " +===========================+\n"

make -q
if (( $? == 0 ))
then
  echo "Nothing has changed :)"
  exit 0
fi

make > /dev/null 2>&1
if (( $? == 2 ))
then
     echo "Make failed"
     exit 1
fi

echo -e "\033[0;36m  TEST\t\t\tSTATUS\033[0m\n"

for i in $@
do
  echo -en "$i . . . . . . . . "
  ./kwinc $i > $i.asm

  # mars-mips $i.asm | tail --lines=+3 > $i.actual    # Arch command
  Mars $i.asm | tail --lines=+3 > $i.actual           # Fedora command

  diff -ZB $i.out $i.actual > out/$i.diff 2>&1
  if (( $? ))
  then
    echo -e "❌"
    failed=1
  else
    echo -e "✅"
  fi

  rm $i.asm $i.actual
done

echo -e "\n"

if (($failed))
then
  echo -e "\033[0;31mTEST(S) FAILED\033[0m"
else
  echo -e "\033[1;32mALL TESTS PASSED\033[0m"
fi