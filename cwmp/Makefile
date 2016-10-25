

#====================================================================
#  Set GCC Flag
# -L : for target app
# -B : for gcc tools
#====================================================================
#export CC=$(TOOLPATH)/bin/$(CROSS_COMPILE)gcc $(LDLIBS) $(AP_FLAG)

#CFLAGS  = -I$(UTIL_INCLUDE) -I$(PAL_INCLUDE) -I$(OMA_INCLUDE) $(AP_FLAG) 
#LDLIBS  = -L$(AC_LIB_DIR) -Xlinker "-(" -lutil -loma -lpal -lpthread -Xlinker "-)" 
#LDFLAGS = -Wl -static

cwmpdir=$(shell pwd)
Conffile=$(cwmpdir)/cwmp-m/configure
TARGETS=tr69c

build: 
	@echo "BUILD         $(TARGETS)"
	@echo "BUILD    CC  >>>>>  $(CC)"
	@cd $(cwmpdir)/cwmp-m/ && make CC="$(CC)"
	@echo "BUILD      >>>  0"
	@echo "cp cwmp --> $(TARGETS)"
	@cp -rf ./cwmp-m/cwmpd/src/cwmpd $(cwmpdir)/$(TARGETS)
	@echo "BUILD      >>>  OK"

     
install:
	@echo $(shell pwd)
	@echo "INSTALL       $(TARGETS)"
	@cp -f $(cwmpdir)/$(TARGETS)  $(BIN_PATH)/app/bin/
	#@cd ${L2TP_DIR}/doc && cp -f  ${L2TP_CONFS} $(ROOTFS_PATH)/etc/xl2tpd && cd ../..
	
clean:
	@echo "CLEAN        tr069"
	@cd $(cwmpdir)/cwmp-m/ && make clean
	@rm -rf $(cwmpdir)/$(TARGETS)
