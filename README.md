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

![trocaregioessaida.png](/trocarregioessaida.png "Saida trocaregioes.cpp")
:--:
Saida trocaregioes.cpp

### 3. Labeling
O proximo programa consiste em contar em uma imagem o numero de bolhas que possuem buracos e o numero de bolhas que nao possuem buracos, eliminando aquelas que tocam as bordas por ser impossivel determinar se as mesmas possuem algum buraco. Primeiramente, e valido notar que e utlizado o tipo *uchar* para representar os tons de cinza, porem se tivessemos mais do que 255 objetos para serem rotulados teriamos um problema, pois nao haveriam tons de cinza suficiente para rotular todos. Assim, diante deste cenario seria necessario alterar o tipo de dados, tendo que passar para algum de dois bytes, por exemplo, passando a ter 65535 tons de cinza disponiveis. Passando para o algoritmo em si, o mesmo e baseado no programa [labeling.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/labeling.cpp) e consiste no seguinte algoritmo:
- Primeiramente, sao varridas as bordas verticais da imagem carregada e, se for encontrado algum pixel com cor branca, aplica-se o *floodfill* no mesmo com a cor preta.
- Repete-se o mesmo procedimento para as bordas horizontais, resultando em uma imagem sem nenhuma bolha tocando as bordas.
- Apos isso, realiza-se o *floodfill* no ponto (0,0) com alguma cor cinza (utilizou-se 120), visando deixar na cor preta apenas os supostos buracos de algumas bolhas.
- Em seguida, varre-se a imagem a procura de pixels de cor preta, incrementando o contador de buracos e apagando o mesmo aplicando-se *floodfill* na cor cinza quando encontrado um.
- Por fim, teremos apenas bolhas sem buracos nesta utlima etapa. Fazendo uma varredura pesquisando a cor branca, podemos incrementar o contador de bolhas sem buracos e realizar o preenchimento naquele pixel usando a cor do contador (labeling classico) quando encontrada esta cor. 

As saidas do [labeling.cpp](/labeling.cpp) obtidas a cada passo a passo sao mostradas abaixo:

![labelingsembordas.png](/labelingsemborda.png "Saida labeling.cpp")
:--:
Saida labeling.cpp apos retirar bolhas em todas as bordas

![labelingcinza.png](/labelingcinza.png "Saida labeling.cpp")
:--:
Saida labeling.cpp apos aplicar *floodfill* no ponto (0,0)

![labelingsemburacos.png](/labelingsemburacos.png "Saida labeling.cpp")
:--:
Saida labeling.cpp apos contar e retirar bolhas com buracos

![labelingfinal.png](/labelingfinal.png "Saida labeling.cpp")
:--:
Saida labeling.cpp apos contar e rotular bolhas sem buracos

Como saida de texto, foi obtido:
```
$ ./labeling bolhas.png 
a figura tem 21 bolhas, sendo 14 sem buracos e 7 com buracos
```

### 4. Equalize
Utilizando como referencia o programa [histogram.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/histogram.cpp), foi implementado o [equalize.cpp](/equalize.cpp), sendo responsavel por realizar a equalização do histogram para cada imagem capturada. O mesmo utiliza o a propria funcao *equalizeHist* do proprio *openCV*, alem das funcoes *calcHist* (para calcular o histograma a partir da matriz de uma imagem) e *normalize* (para normalizar o mesmo). Apos isso, sao copiadas as imagens dos dois histogramas (normal e equalizado) nas imagens capturadas. A partir deles, e possivel ver com clareza as suas diferencas, tendo no histograma equalizado uma melhor distribuicao das ocorrencias e portanto um melhor aproveitamento dos tons de cinza. As figuras abaixo foram obtidas a partir do [equalize.cpp](/equalize.cpp):




