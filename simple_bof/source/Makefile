obj-m += simple_bof.o

all:
	make -C $(KERNEL) M=$(PWD) modules
 
clean:
	make -C $(KERNEL) M=$(PWD) clean
