.PHONY: all
all:
	ant -e -v -lib ./lib -Ddebug=true all
	
.PHONY: clean
clean:
	ant -e -v -lib ./lib -Ddebug=true clean
	
.PHONY: test
test:
	ant -e -v -lib ./lib -Ddebug=true test
	
	