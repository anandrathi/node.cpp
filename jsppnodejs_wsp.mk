.PHONY: clean All

All:
	@echo "----------Building project:[ jsppnodejs - Debug ]----------"
	@$(MAKE) -f  "jsppnodejs.mk"
clean:
	@echo "----------Cleaning project:[ jsppnodejs - Debug ]----------"
	@$(MAKE) -f  "jsppnodejs.mk" clean
