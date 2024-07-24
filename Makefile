.phony: test

test: 
	$(MAKE) -C bstr test	
	$(MAKE) -C flag test
	$(MAKE) -C vec test
	$(MAKE) -C binary_tree test
	
