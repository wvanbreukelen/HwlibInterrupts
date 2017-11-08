.PHONY: clean, doxygen

dirs := $(wildcard */)

clean:
	@$(foreach dir,$(dirs),cd $(dir); $(MAKE) clean; cd ..;)
	@rm -rf html/

doxygen:
	doxygen Doxyfile
