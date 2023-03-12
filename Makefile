MODULE_NAME = tinyCryptoModule
CONFIG_MODULE_SIG = n

PWD = $(shell pwd)
KERNEL_RELEASE = $(shell uname -r)

obj-m := $(MODULE_NAME).o
$(MODULE_NAME)-objs := mymodule.o crypto.o util.o

all:
	make -C /lib/modules/$(KERNEL_RELEASE)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KERNEL_RELEASE)/build M=$(PWD) clean

.PHONY: load
load:
	-sudo rmmod $(MODULE_NAME)
	sudo dmesg -C
	sudo insmod $(MODULE_NAME).ko
	sudo dmesg
testread:
	cat /proc/modulecrypto
	dmesg
testwrite:
	echo "base64 encode\nasdfadsfasfdas\n" > /proc/modulecrypto
	dmesg
unload:
	-sudo rmmod $(MODULE_NAME)