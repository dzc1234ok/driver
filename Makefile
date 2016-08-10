KERNELDIR :=/lib/modules/$(shell uname -r)/build


test:
	make -C $(KERNELDIR) M=$(shell pwd) modules


clean:
	rm -rf *.ko *.o *.mod.* modules* Module* .*.cmd .tmp_*
	
	
obj-m = driver.o
