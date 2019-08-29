#****************************************************************************
#
# Makefile for all
# Henry
# 2019-08-29
#
#****************************************************************************

.PHONY: all
all:
	make -C ./ds
	make -C ./lib
	make -C ./db


.PHONY: clean
clean:
	make -C ./ds cleanall
	make -C ./lib cleanall
	make -C ./db cleanall

