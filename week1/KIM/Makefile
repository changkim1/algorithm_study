PP = g++
SRC = $(shell ls -t | grep .cpp | head -1)

DATE = $(shell date "+%y%m%d")


all : 
		$(PP) $(SRC)
		@echo -e "\033[32mINPUT: "
		@./a.exe

file :
		@echo $(SRC)

git :
		git add *
		git commit -m $(DATE)
		git push

.PHONY: all git file