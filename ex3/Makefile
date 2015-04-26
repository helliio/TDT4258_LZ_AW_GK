.PHONY: all flash root $(MODULES)
all: root flash

MODULES=game
ROOT=platform-energymicro-efm32gg-dk3750/images/root.romfs

root: $(ROOT)

$(MODULES): $(wildcard local_src/$@-*/**/*)
	ptxdist clean $@
	ptxdist compile $@
	ptxdist targetinstall $@

$(ROOT): $(MODULES)
	ptxdist image root.romfs

flash:
	ptxdist test flash-rootfs
