# Trabalho-1-de-Comp-1-2020-PLE--Forca

[Vídeo de introdução](https://youtu.be/XN1NnVgN6_M)

## Objetivos 🎯
Na descrição da atividade pelos docentes ficaram claros 2 objetivos:
-	o prático (i.e. o dever em si): recriar digitalmente um jogo de tabuleiro popular, o Jogo da Forca.
-	o acadêmico: exercitar os conhecimentos de programação e da linguagem C, similarmente com promover o desenvolvimento soft skills de trabalho em equipe e desenvolvimento de soluções computacionais, como planejamento 

## Premissas do desenvolvimento do jogo 📚
Dando prosseguimento à tarefa de construção do simulador, tornou-se necessário o estabelecimento de um plano de trabalho detalhado.
A princípio, houve um foco na formação de uma noção conjunta que guiaria o trabalho, isto é, premissas. Foram estas: 
-	A definição do jogo
O jogo da forca é um jogo em que o jogador tem que acertar qual é a palavra proposta, tendo como dica o número de letras e o tema ligado à palavra.  _Wikipedia_

-	A condução e regras tradicionais do jogo
Ao jogador é apresentada uma série de caracteres em branco que representam as letras componentes de uma palavra-chave a ser acertada. 
O jogador possui um número limitado de chances de acertar as letras e formar a palavra-chave. 
O jogo acaba quando o jogador adivinhar corretamente a palavra ou quando perde todas as suas chances de erro e seu boneco “é enforcado” ou some.

Com base em tais princípios, pode-se planejar um jogo com experiência de uso muito similar à tradicional em tabuleiros.

## Rundown 📋
Veja um pseudocódigo desenvolvido com linguagem natural, que apresenta breve descrições das etapas que compõe uma jogada ou execução do jogo:
-	Questionar usuário e ler sua entrada sobre qual tema deseja que sua palavra seja.
-	Escolhe-se uma palavra aleatória dentro a lista de possibilidades de determinado tema. 
-	Pede-se que o usuário entre com uma única letra e há leitura de tal caractere previamente validado. 
  -	Verifica-se o pertencimento de tal letra à palavra-chave:
    -	Se a letra estiver na palavra: a letra é destacada na saída do programa nas posições em que poderia ser encontrada na palavra-chave. 
    -	Se a letra for inválida: o jogador perde uma de suas chances e seu boneco ganha um membro, tal processo deve estar claro na saída do programa.
  -	Verifica-se a existência de letras a ainda serem descobertas ou chances disponíveis.
    -	Se não houver letras a serem descobertas ou se o usuário não tem mais chances disponíveis:
          -	Se não houver letras a serem descobertas: imprimir mensagem de vitória.
          -	Se o usuário não tiver mais chances disponíveis: imprimir mensagem de perda. 
    -	Se houver, volta-se ao passo 3. 
  -	Questionar o usuário se deseja prosseguir para um novo jogo:
      -	Se sim: voltar ao passo 2.
      -	Se não: encerrar o programa.

## Regras de utilização do jogo e saídas 📝
É importante ressaltar as regras de utilização do jogo pelo usuário. Para isso, deve-se seguir a sequência de etapas em que é necessária alguma intervenção, entrada do usuário. 
- Escolha de tema: O usuário deve entrar com um número inteiro no intervalo [1,4]. 

- Entrada da letra adivinhada: O usuário deve entrar com uma letra do alfabeto (maiúscula ou minúscula).
   
- Entrada da opção de retorno ou prosseguimento: O usuário deve entrar ou com y ou n (minúsculos ou maiúsculos).
 
## Técnicas utilizadas no trabalho 🧠
⦁	Arrays
⦁	Modificadores de variáveis 
⦁	Limpeza de buffer
⦁	Passagem parâmetros à funções por referência e valor
⦁	Argc e Argv
⦁	Comandos de iteração, controle de fluxo
⦁	Funções de entrada e saída da biblioteca <stdio.h>
⦁	Multiarquivos com criação de bibliotecas próprias
⦁	Debugger
⦁	Impressão de mensagens de erro
⦁	Manipulação de strings
⦁	Alocação dinâmica de memória
⦁	Acesso aleatório a elementos (vantagens)
⦁	Geração de números aleatórios dentro de um escopo com biblioteca time.h, srand e rand.
⦁	Input handling
⦁	Criação de modos diferentes de jogo
