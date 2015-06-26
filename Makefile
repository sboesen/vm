all: vm

vm: vm.c
	clang -g -o vm vm.c
