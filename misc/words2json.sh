#! /usr/bin/env bash

set -e
__SCRIPT_VERSION="0.0.1"
__SCRIPT_NAME=$( basename $0 )
__DESCRIPTION="Convert a file of words into a json \
  translating them through trans"
__OPTIONS=":hvf:o:e:s:t:"

engine=yandex
targetlang=en

usage_head() { echo "Usage :  $__SCRIPT_NAME [-h|-help] [-v|-version]"; }
usage ()
{
cat <<EOF
$(usage_head)

    $__DESCRIPTION

    Options:
      -h|help       Display this message
      -v|version    Display script version
      -f            Words file
      -o            Output json file
      -e            Engine ($engine)
      -s            Source lang
      -t            Target lang


    This program is maintained by Alejandro Gallo.
EOF
}    # ----------  end of function usage  ----------


while getopts $__OPTIONS opt; do
  case $opt in

  h|help     )  usage; exit 0   ;;

  v|version  )  echo "$__SCRIPT_NAME -- Version $__SCRIPT_VERSION"; exit 0   ;;
  f          )  words_file=$OPTARG ;;
  o          )  output_file=$OPTARG ;;
  e          )  engine=$OPTARG ;;
  s          )  sourcelang=$OPTARG ;;
  t          )  targetlagn=$OPTARG ;;

  * )  echo -e "\n  Option does not exist : $OPTARG\n"
      usage_head; exit 1   ;;

  esac    # --- end of case ---
done
shift $(($OPTIND-1))

echo "Reading words from ${words_file}"
echo "Writing json into ${output_file}"

[[ -f $words_file ]]
[[ ! -f $output_file ]]
touch $output_file
[[ -f $output_file ]]

counter=0

echo '[' > $output_file

echo "Proceeding with `which trans`"

for word in $(cat $words_file); do
  if [[ ! $counter = 0 ]]; then
    echo ',' >> $output_file
  fi
  let counter+=1
  translation="$(
    trans -t $targetlang -brief -e $engine --no-ansi "$word" |
    awk '{printf "%s\\n", $NL}'
  )"
  echo "${word} ($(echo $translation | wc))"
  json="{\
    \"word\": \"$word\", \
    \"value\": \"$translation\" \
  }"
  echo "${json}" >> $output_file
done

echo ']' >> $output_file
