CONTIKI_PROJECT = node
all: $(CONTIKI_PROJECT)

# PLATFORMS_EXCLUDE = sky nrf52dk native
# BOARDS_EXCLUDE = srf06/cc13xx launchpad/cc1310 launchpad/cc1350 sensortag/cc2650 sensortag/cc1350

CONTIKI=../../../..

# force Security from command line
MAKE_WITH_SECURITY ?= 0


MAKE_MAC = MAKE_MAC_TSCH
# MODULES += os/services/TREE

ifeq ($(MAKE_WITH_SECURITY),1)
CFLAGS += -DWITH_SECURITY=1
endif

include $(CONTIKI)/Makefile.include
