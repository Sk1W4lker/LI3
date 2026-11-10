CFLAGS = -Wall -Iinclude -fno-stack-protector -g -Werror=discarded-qualifiers

# Regra principal para compilar os executáveis
inicio: programa-principal programa-testes

# Compilação do programa-principal
programa-principal: src/valida_dados.o src/ficheiros.o src/arraydin.o src/hashtable.o src/users.o src/programa-principal.o src/artists.o  src/queries.o src/musics.o src/albuns.o src/history.o src/process.o
	@gcc $(CFLAGS) $^ -o programa-principal

# Compilação do programa-testes
programa-testes: src/valida_dados.o src/ficheiros.o src/arraydin.o src/hashtable.o src/users.o src/programa-testes.o src/artists.o src/queries.o src/musics.o src/albuns.o src/history.o src/process.o
	@gcc $(CFLAGS) $^ -o programa-testes

# Regras para os arquivos objeto
hashtable.o: src/hashtable.c
	@gcc $(CFLAGS) -c $< -o $@

queries.o: src/queries.c
	@gcc $(CFLAGS) -c $< -o $@

process.o: src/process.c
	@gcc $(CFLAGS) -c $< -o $@

users.o: src/users.c
	@gcc $(CFLAGS) -c $< -o $@

valida_dados.o: src/valida_dados.c 
	@gcc $(CFLAGS) -c $< -o $@

musics.o: src/musics.c 
	@gcc $(CFLAGS) -c $< -o $@	

ficheiros.o: src/ficheiros.c 
	@gcc $(CFLAGS) -c $< -o $@

arraydin.o: src/arraydin.c 
	@gcc $(CFLAGS) -c $< -o $@

artists.o: src/artists.c 
	@gcc $(CFLAGS) -c $< -o $@

history.o: src/history.c 
	@gcc $(CFLAGS) -c $< -o $@

albuns.o: src/albuns.c 
	@gcc $(CFLAGS) -c $< -o $@

programa-principal.o: src/programa-principal.c
	@gcc $(CFLAGS) -c $< -o $@

programa-testes.o: src/programa-testes.c
	@gcc $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos objeto e executáveis
clean:
	rm -f programa-principal programa-testes src/*.o include/*.o resultados/*.txt resultados/users_errors.csv resultados/artists_errors.csv resultados/musics_errors.csv resultados/albums_errors.csv resultados/history_errors.csv 