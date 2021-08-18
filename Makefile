.pHONY : all
all :
	cd /C/Users/Administrator/Desktop/myboot/uart && make
	cd /C/Users/Administrator/Desktop/myboot/82 && make
	cd /C/Users/Administrator/Desktop/myboot/systick_handler && make
	
.pHONY : cleanall
cleanall :
	cd /C/Users/Administrator/Desktop/myboot/uart && make clean
	cd /C/Users/Administrator/Desktop/myboot/82 && make clean
	cd /C/Users/Administrator/Desktop/myboot/systick_handler && make clean