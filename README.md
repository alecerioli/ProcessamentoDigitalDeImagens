# Processamento Digital de Imagens
Este repositorio sera utilizado para expor as atividades praticas desenvolvidas durante a disciplina DCA0445 - PROCESSAMENTO DIGITAL DE IMAGENS - UFRN.
## Primeira Unidade
Os codigos referenciados no decorrer desta unidade foram obtidos a partir da [pagina pessoal do Professor Agostinho Brito](https://agostinhobritojr.github.io/tutorial/pdi/). Para a compilacao dos codigos apresentados a seguir, sera necessario possuir o arquivo [Makefile](/Makefile) no mesmo diretorio dos programas, podendo ser compilados e executados usando os seguintes comandos:
```
$ make <nome_programa>
$ ./<nome_programa> <arquivo_de_entrada>
```
### 1. Regions
O programa [regions.cpp](/regions.cpp) desenvolvido permite alterar a regiao de uma foto de entrada para o negativo da mesma, sendo essa area definida por dois pontos P1 e P2 representando os vertices de um retangulos, sendo escolhidos pelo usuario. O codigo foi baseado no programa [pixels.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/pixels.cpp). Primeiramente, foi adicionado um trecho de codigo para habilitar a leitura dos pontos fornecidos pelo usuario. Em seguida, apos verificar que os pontos se encontram dentro dos limites da imagem, serao percorridos os pixels que se encontram naquela regiao (utilizando dois *for*) e valor de cada um sera substituido pela subtracao de 255 com o valor atual, gerando assim a imagem negativa. A saida do programa utilizando os pontos P1 = (100,50) e P2 = (200,300) e mostrada na figura abaixo:

![regionssaida.png](/regionssaida.png "Saida regions.cpp")
:--:
Saida regions.cpp

### 2. Troca regioes
O seguinte codigo tem como intuito trocar os quadrantes em diagonal de uma imagem. Ele tambem foi baseado no programa [pixels.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/pixels.cpp), sendo o funciamento do mesmo possivel gracas a um construtor da classe *Mat* tendo como parametros um objeto *Mat* e um objeto *Rect*, obtendo como resultando apenas a matriz contida naquele retangulo. Assim, foram inicializados quatro objetos *Rect* representando cada um dos quadrantes da imagem original (utizando metade da altura e da largura como divisores) e utilizando o construtor citado foram obtidos as quatro matrizes representando os quadrantes. Por fim, utilizou-se os metodos *vconcat()* e *hconcat()* para juntar os mesmos na ordem desejada. A saida do programa [trocaregioes.cpp](/trocaregioes.cpp) exibida abaixo:


