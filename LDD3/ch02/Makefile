KERNELDIR=/lib/modules/`uname -r`/build/
PWD:=$(shell pwd)

obj-m += hello_world.o

all:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD) clean
