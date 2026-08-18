soda:
	nvcc --allow-unsupported-compiler coup.cu -std=c++20 -o soda

grind:
	valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes --main-stacksize=10737418240 ./h.f < tc

default:
	# Usage: make [executable, from matching .cc file]


%.:
	cp -n z/c.cc $(basename $@).cc
	vi $(basename $@).cc

# warnings = -Wall -Wextra -Wshadow -Wconversion -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-parentheses -Wno-unknown-pragmas

# wrote Wconversion twice and some of these r useless with c++20
warnings = -Wall -Wextra -Wshadow -Wconversion -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-parentheses
sanitize = -fsanitize=undefined -fsanitize=address -fno-sanitize-recover
definedebug = -ggdb3 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -DTAKOTIME -DTAKOSPACE
compile = g++ -std=c++20 -O0 -march=native -I . $(warnings) $(sanitize)
# 17 for usaco

%.c: %.cc
	$(compile) $(definedebug) $< -o $@

#ggdb3 already included

#%.7: %.cc
	#$(compile) $(definedebug) $< -o $@ -std=c++17

#%.f: %.cc
	##$(compile) $< -o $@ -Ofast

#formerly ff
%.f: %.cc
	g++ -std=c++20 $< -o $@ -Ofast $(warnings) -DTAKOSPACE

%.fwhat: %.cc
	g++ -std=c++20 $< -o $@ -Ofast $(warnings) -DTAKOSPACE -DTAKOTIME

# formerly f
# TEMP CHANGE FROM .2
#
%.2: %.cc
	g++ -std=c++20 $< -o $@ -O2 $(warnings) -DTAKOSPACE

%: %.cc
	g++ -std=c++20 $< -o $@ -O2 $(warnings) -DTAKOSPACE -ggdb3

.PRECIOUS: %.f  # ADD THIS LINE

%: %.cpp
	# Warning, you're using cpp instead of cc.
	$(compile) $< -o $@
