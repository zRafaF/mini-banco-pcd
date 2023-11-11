# Mini Banco PCD

Um mini banco de dados que implementa a estrutura de dados **trie**. 

**Funcionalidades**:
* Indexa elementos do tipo `PersonRecord` através de seu `id` na **trie**.
* Salva/Carrega os dados no disco.
* Remove, Adiciona e Busca índices na **trie**. 

## Compilando binários

Compile os binários com make através do seguinte comando

```sh
make
```

Ou utilize o comando a seguir para **compilar** e **executar** o programa.

```sh
make run
```

Mesmo não sendo o ideal sempre que o comando `make` for executado a pipeline removerá todas as dependências e as recompilará, para garantir que tudo esteja em sua versão mais recente.

## Testes
Para testes o [Unity](https://www.throwtheswitch.org/unity) está sendo utilizado. 

Você pode criar o executável dos testes com:
```sh
make test
```
ou criar os binários e executar:
```sh
make test_run
```
## Verificar vazamentos de memória

Os vazamentos de memória foram verificados utilizando a ferramenta [Valgrind](https://valgrind.org/).

Você pode executa-la nos testes ou em produção com o comando:

```sh
valgrind --leak-check=full ./mini_banco_pcd

# Ou

valgrind --leak-check=full ./mini_banco_pcd_test
```

> Na aplicação não encontrei nenhum vazamento de memória.