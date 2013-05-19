CC = gcc
CFLAGS = -g
BISONFL = -d -v

tree: lex.yy.o tree.tab.o table.o typecheck.o symtab.o ast.o intermediate.o tree_main.o
	$(CC) -o $@ $(CFLAGS) lex.yy.o tree.tab.o table.o typecheck.o symtab.o ast.o intermediate.o  tree_main.o

generate: lex.yy.o tree.tab.o table.o typecheck.o symtab.o ast.o intermediate.o generate.o
	$(CC) -o $@ $(CFLAGS) lex.yy.o tree.tab.o table.c typecheck.o symtab.o ast.o intermediate.o generate.o

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

generate.o: generate_code.c
	$(CC) -c $(CFLAGS) -o generate.o generate_code.c

tree_main.o: tree_main.c
#tree_main.o: buildSymTab.c
#tree_main.o: generate_code.c
	$(CC) -c $(CFLAGS) -o tree_main.o tree_main.c

symtab.o: symtab.c
	$(CC) -c $(CFLAGS) $<

typecheck.o: typecheck.c typecheck.h symtab.h 
	$(CC) -c $(CFLAGS) $<

intermediate.o: intermediate.c intermediate.h
	$(CC) -c $(CFLAGS) $<

parser:
	make tree

clean: 
	rm -f tree lex.yy.o tree.tab.o tree_main.o ast_o tree.tab.h tree.tab.c\
	lex.yy.c *.o *~ tree.output vgcore.* core* generate
