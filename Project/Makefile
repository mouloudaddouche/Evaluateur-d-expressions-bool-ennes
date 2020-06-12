
test: 
	rm -f eval
	gcc -Wall -c eval.c
	gcc -o eval eval.o
	./eval "((1+0)"
	./eval "(((1.0)=>(0+1))<=>1)"
	./eval "NON(((1.0)=>(0+1))<=>1)"
	./eval "0+0+0+0+0+0+1"
	./eval "(((1+0)=>(0<=>0))+((1+0)=>1))"
	./eval "(((1+0)=>(1<=>0))+(NON0))"
	
	
clean : 
		rm -f *.o
		rm -f eval
