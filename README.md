# lista4-ed-ana-julia-lisania-fgv
Repositório destinado a entrega da lista 4 da disciplina de Estrutura de Dados.

# Descrição do Sistema
 
O repositório implementa um sistema simples de autocomplete de jogos utilizando uma estrutura de dados chamada **Trie**. Cada jogo possui um título, uma descrição curta e uma popularidade. Os jogos são armazenados na Trie a partir de um catálogo fornecido diretamente no código-fonte.
 
O sistema permite buscar jogos a partir de um prefixo do título. Dado um prefixo e um número `k`, o sistema retorna até `k` jogos cujo título começa com esse prefixo, ordenados por popularidade em ordem decrescente. Em caso de empate na popularidade, o critério de desempate é a ordem alfabética pela chave de busca do título.
 
A busca é **case-insensitive** e **ignora espaços em branco**, ou seja, os prefixos `"ha"`, `"HA"` e `"H A"` são tratados de forma equivalente.

Existem três classes principais no sistema:
 
1. **Game**: classe que modela os jogos e seus atributos.
```cpp
Game(std::string title, std::string shortDescription, int popularity)
```
 
2. **TrieNode**: classe que representa um nó da Trie. Cada nó armazena ponteiros para seus filhos, uma indicação de fim de título e um ponteiro para o jogo associado, caso aquele nó represente o final de um título.
```cpp
TrieNode()
```
 
3. **Trie**: classe responsável por armazenar os jogos e realizar as buscas por título e por prefixo. Implementa todas as operações do sistema, tais como: inserir um jogo, verificar se um título existe, buscar jogos por prefixo, ordenar os resultados e converter títulos e prefixos para a chave de busca utilizada internamente.
```cpp
Trie()
```

# Instruções de Compilação
 
O repositório foi inteiramente programado em **C++**, portanto, é necessário compilar os arquivos antes de executar o programa. As instruções abaixo compilam todos os arquivos `.cpp` de uma vez:
 
1. Certifique-se de que todos os arquivos `.hpp` e `.cpp` estejam na mesma pasta.
2. Certifique-se de ter o `g++` instalado na sua máquina.
3. Em seu terminal, dentro da pasta onde estão os arquivos, execute:
```bash
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```
 
Após o comando, um arquivo executável será criado na mesma pasta.
 
# Instruções de Execução
 
O programa é executado pela linha de comando no seguinte formato:
 
```bash
./app k prefixo
```
 
Onde:
- `k` é a quantidade máxima de sugestões desejadas;
- `prefixo` é o prefixo usado na busca.
Exemplos:
 
- **Windows**
```bash
.\app.exe 3 ha
```
 
- **Linux / macOS**
```bash
./app 3 ha
```
 
Caso o prefixo contenha espaços, ele deve ser passado entre aspas:
 
```bash
./app 3 "half l"
```
 
Caso nenhum resultado seja encontrado, o programa exibirá:
 
```
No results found
```

# Organização dos Arquivos
 
```text
main.cpp          — Arquivo principal, carrega os jogos e executa a busca
Game.hpp          — Declaração da classe Game
Game.cpp          — Implementação da classe Game
Trie.hpp          — Declaração das classes Trie e TrieNode
Trie.cpp          — Implementação das classes Trie e TrieNode
GamesDatabase.hpp — Declaração do array de jogos e da quantidade de jogos
GamesDatabase.cpp — Definição da lista inicial de jogos
README.md         — Descrição e instruções do projeto
```

# Exemplos de Uso
 
```bash
./app 3 ha
```
```
Hades | Defy the god of the dead as you hack...| 213542
Halo The Master Chief Collection | The Master Chief... | 192219
Halo Infinite | The legendary Halo series returns with...| 160647
```
 
```bash
./app 1 res
```
```
Resident Evil 2 | A deadly virus engulfs the residents of Raccoon... | 93404
```
 
```bash
./app 3 zelda
```
```
No results found
```