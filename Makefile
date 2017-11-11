.DEFAULT_GOAL:=basic

basic: backup debug release

SENV = echo "skipping setting LIB and INCLUDE" &&


RUNFILE =./Clear

DEND =-debug

REND =-release

DF = $(RUNFILE)$(DEND)

RF = $(RUNFILE)$(REND)

CDD =cd ./Debug &&

CDR =cd ./Release &&

CLND =rm -rf ./Debug

CLNR =rm -rf ./Release

CLNDF =rm -f $(DF)

CLNRF =rm -f $(RF)


all: backup crd crr

rd: rundebug

rr: runrelease

crd: debug rd

crr: release rr

debug: cleandebug
	mkdir -p ./Debug
	$(SENV) $(CDD) cmake ..
	$(CDD) make
	$(CDD) mv $(RUNFILE) .$(DF)
	$(CLND)

release: cleanrelease
	mkdir -p ./Release
	$(SENV) $(CDR) cmake ..
	$(CDR) make
	$(CDR) mv $(RUNFILE) .$(RF)
	$(CLNR)

rundebug:
	$(DF) &

runrelease:
	$(RF) &


clean: cleandebug cleanrelease

cleandebug:
	$(CLND)
	$(CLNDF)

cleanrelease:
	$(CLNR)
	$(CLNRF)

backup: compress

compress:
	mkdir -p ./Backups
	tar --exclude='./Backups' --exclude='./cmake' --exclude='./Debug' --exclude='./Release' --exclude='$(DF)' --exclude='$(RF)' -zcf ./Backups/Backup-`date +%s`.tgz .

