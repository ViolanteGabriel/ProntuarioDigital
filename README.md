# Prontuário Digital — Aula Prática 06

Sistema de prontuário médico eletrônico em C, desenvolvido no Trabalho
Trimestral 1 e utilizado como base para o exercício de GitHub Actions.

## Compilação e testes locais

É necessário CMake 3.21 ou superior e um compilador com suporte a C11/C17
(GCC, Clang ou MSVC). Execute na raiz do repositório:

```sh
cmake -S . -B build -DCMAKE_C_STANDARD=11 -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure --no-tests=error
```

Para testar C17, repita os comandos usando `build-c17` como diretório de
compilação e `-DCMAKE_C_STANDARD=17` na configuração.

Execute o programa com `./build/prontuario` no Linux/macOS ou
`.\build\Release\prontuario.exe` no Windows com o gerador Visual Studio.

## Testes de unidade

Os 16 testes em [tests/test_estruturas.c](tests/test_estruturas.c) são registrados
individualmente no CTest e verificam:

- Datas em meses de 30 e 31 dias, fevereiro e anos bissextos, incluindo séculos.
- Rejeição de dias, meses e anos inválidos; preserva-se a regra original de ano > 1900.
- Criação de lista vazia, primeira inserção e múltiplas inserções em ordem.
- Rejeição de lista nula e cópia independente dos dados de uma consulta.
- Criação de árvore vazia e de prontuário com nome e consulta inicial.
- Liberação de estruturas vazias e preenchidas, incluindo subárvores.

As verificações permanecem ativas em builds Release. Uma falha retorna código
diferente de zero e faz o CTest e o GitHub Actions falharem.

Foram corrigidos a inicialização do próximo elemento e o retorno da inserção
na lista, o tratamento de falhas de alocação e a validação de anos bissextos.
Também foram adicionadas funções de liberação de memória e removidos os comandos
`pause` e `cls`, específicos do Windows, do menu original.
A inserção pelo menu agora valida a data. As opções de busca por data e remoção
de prontuário continuam sem implementação no menu, como no trabalho original;
não fazem parte do exercício de CI.

## GitHub Actions

O workflow [.github/workflows/ci.yml](.github/workflows/ci.yml) compila o programa
e executa os testes a cada `push`, em pull requests e por acionamento manual.
Sua matriz contém seis combinações:

| Sistema operacional | Versões da linguagem |
| --- | --- |
| Ubuntu (`ubuntu-latest`) | C11 e C17 |
| macOS (`macos-latest`) | C11 e C17 |
| Windows (`windows-latest`) | C11 e C17 |

C11 e C17 são revisões do padrão da linguagem C, selecionadas pelo CMake com
`CMAKE_C_STANDARD`. O padrão é obrigatório e extensões do compilador são
desabilitadas. Cada combinação executa os 16 testes, totalizando 96 execuções
por workflow. O build inclui tanto a aplicação quanto o executável de testes.

Referências: [matrizes do GitHub Actions](https://docs.github.com/en/actions/how-tos/write-workflows/choose-what-workflows-do/run-job-variations)
e [padrão C no CMake](https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html).

## Submissão no Moodle

Após enviar as alterações ao GitHub, abra
[as execuções deste workflow](https://github.com/ViolanteGabriel/ProntuarioDigital/actions/workflows/ci.yml),
aguarde as seis combinações terminarem com sucesso e copie o endereço da
execução. O link a entregar deve ter o formato
`https://github.com/ViolanteGabriel/ProntuarioDigital/actions/runs/ID_DA_EXECUCAO`.
