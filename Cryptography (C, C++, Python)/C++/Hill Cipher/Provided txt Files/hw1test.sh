case $1 in
hw1.c)
	gcc hw1.c 
	EXE="./a.out"
	;;
hw1.cpp)
	g++ hw1.cpp
	EXE="./a.out"
	;;
hw1.java)
	javac hw1.java
	EXE="java hw1"
	;;
*)
	echo "Invalid source file name"
	exit 1
esac

echo "Case #0"
eval $EXE k0.txt p0.txt >stu0.txt
read -n 1 -p "Enter to continue:" mainmenuinput
diff stu0.txt base0.txt
echo "Case #0 - complete"

echo "Case #1"
eval $EXE k1.txt p1.txt >stu1.txt
read -n 1 -p "Enter to continue:" mainmenuinput
diff stu1.txt base1.txt
echo "Case #1 - complete"

echo "Case #2"
eval $EXE k2.txt p2.txt >stu2.txt
read -n 1 -p "Enter to continue:" mainmenuinput
diff stu2.txt base2.txt
echo "Case #2 - complete"

echo "Case #3"
eval $EXE k3.txt p3.txt >stu3.txt
read -n 1 -p "Enter to continue:" mainmenuinput
diff stu3.txt base3.txt
echo "Case #3 - complete"

