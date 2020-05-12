CFLAGS_CRY+=-D_XOPEN_SOURCE
LDFLAGS_CRY+=-lcrypt

mypasswd:pass.c
	gcc -o $@ $^ $(CFLAGS_CRY) $(LDFLAGS_CRY)
