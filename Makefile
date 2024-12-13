.PHONY: install
install:
ifeq ($(OS), Windows_NT)
	@if exist build ( \
		echo Removing existing build directory... && \
		rmdir /S /Q build \
	)
else
	@if [ -d "build" ]; then \
		echo Removing existing build directory...; \
		rm -rf build; \
	fi
endif
	@echo Creating build directory...
	@cmake -E make_directory build
	@cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cd build && cmake --build .
ifeq ($(OS), Windows_NT)
	@cd build && cmake --install .
else
	@cd build && sudo cmake --install .
endif

.PHONY: clean
clean:
ifeq ($(OS), Windows_NT)
	@if exist build ( \
		echo Cleaning up... && \
		rmdir /S /Q build \
	)
else
	@if [ -d "build" ]; then \
		echo Cleaning up...; \
		rm -rf build; \
	fi
endif