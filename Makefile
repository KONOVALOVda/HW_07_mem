obj-m += ex_kmalloc.o
obj-m += ex_vmalloc.o
obj-m += ex_kmem_cache.o
obj-m += ex_mempool.o
obj-m += ex_get_page.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: modules

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

load:
	sudo insmod ex_kmalloc.ko
	sudo insmod ex_vmalloc.ko
	sudo insmod ex_kmem_cache.ko
	sudo insmod ex_mempool.ko
	sudo insmod ex_get_page.ko

unload:
	sudo rmmod ex_kmalloc
	sudo rmmod ex_vmalloc
	sudo rmmod ex_kmem_cache
	sudo rmmod ex_mempool
	sudo rmmod ex_get_page

format:
	clang-format -i *.c *.h

check:
	@echo "Проверка проекта HW_07_mem"
	ls -l *.ko
