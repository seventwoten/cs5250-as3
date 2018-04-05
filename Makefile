TARGET_MODULE = oneb
BUILDSYSTEM_DIR = /lib/modules/$(shell uname -r)/build

obj-m = $(TARGET_MODULE).o

all:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean
