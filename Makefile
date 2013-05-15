CC = gcc
CFLAGS = -g
BISONFL = -d -v

tree: lex.yy.o tree.tab.o ast.o tree_main.o table.o typecheck.o symtab.o
	$(CC) -o $@ $(CFLAGS) lex.yy.o tree.tab.o ast.o tree_main.o table.o typecheck.o symtab.o

lex.yy.o: lex.yy.c
	$(CC) -c $(CFLAGS) $<

tree.tab.o: tree.tab.c
	$(CC) -c $(CFLAGS) $<

table.o: table.c table.h
	$(CC) -c $(CFLAGS) $<

lex.yy.c: tree.l tree.tab.h
	flex tree.l

tree.tab.h: tree.y
	bison $(BISONFL) $<

tree.tab.c: tree.y
	bison -v $(BISONFL) $<

#tree_main.o: tree_main.c
tree_main.o: buildSymTab.c
	$(CC) -c $(CFLAGS) -o tree_main.o buildSymTab.c

symtab.o: symtab.c
	$(CC) -c $(CFLAGS) $<

typecheck.o: typecheck.c typecheck.h symtab.h 
	$(CC) -c $(CFLAGS) $<

parser:
	make tree

clean: 
	rm -f tree lex.yy.o tree.tab.o tree_main.o ast_o tree.tab.h tree.tab.c\
	lex.yy.c *.o *~ tree.output
