clear
a=0
while [ $a != 8 ]
do
	echo "######################################"
    echo "#                                    #"
    echo "#     Fractal Generator in OpenGL    #"
    echo "#                                    #"
    echo "######################################"
	echo ""
	echo "Select from following option"
	echo "1. Fern"
	echo "2. Sierpinski Triangle"
	echo "3. Linear Fractal"
	echo "4. Tetrahedral"
	echo "5. Mandelbrot"
	echo "6. Julia"
	echo "7. 3D cube"
	echo "8. Quit"
	
	read a
	echo "Instructions -->"
	case $a in
		1) ./fern ;;
		2) ./sierpinski_triangle;;
		3) ./linear_fractal;;
		4) ./tetrahedral;;
		5) ./mandelbrot;;
		6) ./Julia/julia;;
		7) ./3dcube;;
	esac
	clear
done

