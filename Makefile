.phony: test

test: 
	$(MAKE) -C bstr test 1> /dev/null
	$(MAKE) -C flag test 1> /dev/null
	$(MAKE) -C vec test 1> /dev/null
	@echo "All tests passed"
	
