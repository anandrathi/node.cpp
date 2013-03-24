.PHONY: clean All

All:
	@echo "----------Building project:[ jsppnodejs - Release ]----------"
	@$(MAKE) -f  "jsppnodejs.mk"
clean:
	@echo "----------Cleaning project:[ jsppnodejs - Release ]----------"
	@$(MAKE) -f  "jsppnodejs.mk" clean
