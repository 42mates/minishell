# Description: Test the minishell program.

RED="\033[1;31m"
LRED="\033[0;31m"
GREEN="\033[1;32m"
LGREEN="\033[0;32m"
YELLOW="\033[1;33m"
LYELLOW="\033[0;33m"
BLUE="\033[1;34m"
LBLUE="\033[0;34m"
GREY="\033[1;37m"
NC="\033[0m"

test1=(ls cat);			pipe1=("ls" "|" "cat");
test2=(cat ls);			pipe2=("cat" "|" "ls");
test3=(ls wc);			pipe3=("ls" "|" "wc");
test4=(ls ls wc);		pipe4=("ls" "|" "ls" "|" "wc");
test5=(ls cat ls);		pipe5=("ls" "|" "cat" "|" "ls");
test6=(cat cat ls);		pipe6=("cat" "|" "cat" "|" "ls");
test7=(ls wc wc);		pipe7=("ls" "|" "wc" "|" "wc");
test8=(cat ls cat wc);	pipe8=("cat" "|" "ls" "|" "cat" "|" "wc");
test9=(cat ls cat wc cat);	pipe9=("cat" "|" "ls" "|" "cat" "|" "wc" "|" "cat");

start=$1
if [ -z "$start" ]; then start=1; fi

printtab() {
	local str="$1"
	for string in $(eval echo "\${$str${i}[@]}"); do
		echo -n "$string "
	done
}

for ((i=start; i<=9; i++)); do
	echo ""
	echo -e "${YELLOW}TEST $i${NC}\n"
	echo -e "${LRED}PIPEX> $(printtab test)${NC}"
	eval "./tmp \${test${i}[@]}"
	#echo -e "$LBLUE"; read -p "continue, quit {any/q}: " q; echo -e "$NC"
	#if [ "$q" == "q" ]; then break; fi
	echo -e "${LRED}BASH> $(printtab pipe)${NC}"
	eval "eval \"\${pipe${i}[@]}\""
	echo -e "$LBLUE"; read -p "continue, quit {c/q}: " cq; echo -e "$NC"
	if [ "$cq" == "q" ]; then
		break
	fi
done
