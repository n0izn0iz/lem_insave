CHECK_MK=./check/checkmk/checkmk
CHECK_LIB=./check/src/.libs/libcheck.a

all: clean tests
	./tests

$(CHECK_MK): $(CHECK_LIB)
	
$(CHECK_LIB):
	make -C check

tests: tests.c $(CHECK_LIB)
	gcc tests.c -Icheck/src -Icheck -I../includes -o tests -L.. -llem_in -L../libft -lft $(CHECK_LIB) -lpthread -lm

tests.c: $(CHECK_MK)
	$(CHECK_MK) tests.check > tests.c

clean:
	rm -f tests.c