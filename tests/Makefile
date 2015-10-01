all: clean tests
	./tests

tests: tests.c
	gcc tests.c -Icheck/src -Icheck check/src/.libs/libcheck.a -I../includes -o tests -L.. -llem_in -L../libft -lft

tests.c:
	./check/checkmk/checkmk tests.check > tests.c

clean:
	rm -f tests.c