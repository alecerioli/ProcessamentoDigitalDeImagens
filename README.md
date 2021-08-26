# Processamento Digital de Imagens
Este repositorio será utilizado para expor as atividades praticas desenvolvidas durante a disciplina DCA0445 - PROCESSAMENTO DIGITAL DE IMAGENS - UFRN.

## Primeira Unidade
Os codigos referenciados no decorrer desta unidade foram obtidos a partir da [pagina pessoal do Professor Agostinho Brito](https://agostinhobritojr.github.io/tutorial/pdi/). Para a compilação dos codigos apresentados a seguir, será necessario possuir o arquivo [Makefile](/Makefile) no mesmo diretorio dos programas, podendo ser compilados e executados usando os seguintes comandos:
```
$ make <nome_programa>
$ ./<nome_programa> <arquivo_de_entrada>
```
### 1. Regions
O programa [regions.cpp](/regions.cpp) desenvolvido permite alterar a região de uma foto de entrada para o negativo da mesma, sendo essa area definida por dois pontos P1 e P2 representando os vertices de um retângulo, sendo escolhidos pelo usuario. O codigo foi baseado no programa [pixels.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/pixels.cpp). Primeiramente, foi adicionado um trecho de codigo para habilitar a leitura dos pontos fornecidos pelo usuario. Em seguida, após verificar que os pontos se encontram dentro dos limites da imagem, serão percorridos os pixels que se encontram naquela região (utilizando dois *for*) e o valor de cada pixel será substituido pela subtração de 255 com o valor atual, gerando assim a imagem negativa. A saida do programa utilizando os pontos P1 = (100,50) e P2 = (200,300) é mostrada na figura abaixo:

![regionssaida.png](/regionssaida.png "Saida regions.cpp")
:--:
Saida regions.cpp

### 2. Troca regioes
O seguinte codigo tem como intuito trocar os quadrantes em diagonal de uma imagem. Ele tambem foi baseado no programa [pixels.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/pixels.cpp), sendo o funciamento do mesmo possivel graças a um construtor da classe *Mat* tendo como parametros um objeto *Mat* e um objeto *Rect*, obtendo como resultando apenas a matriz contida naquele retângulo. Assim, foram inicializados quatro objetos *Rect* representando cada um dos quadrantes da imagem original (utizando metade da altura e da largura como divisores) e através do construtor citado foram obtidas as quatro matrizes representando os quadrantes. Por fim, utilizou-se os metodos *vconcat()* e *hconcat()* para juntar os mesmos na ordem desejada. A saida do programa [trocaregioes.cpp](/trocaregioes.cpp) é exibida abaixo:

![trocaregioessaida.png](/trocarregioessaida.png "Saida trocaregioes.cpp")
:--:
Saida trocaregioes.cpp

### 3. Labeling
O proximo programa consiste em contar em uma imagem o numero de bolhas que possuem buracos e o numero de bolhas que não possuem buracos, eliminando aquelas que tocam as bordas por ser impossivel determinar se as mesmas possuem algum buraco. Primeiramente, é valido notar que é utlizado o tipo *uchar* para representar os tons de cinza, porém se tivessemos mais do que 255 objetos para serem rotulados teriamos um problema, pois não haveriam tons de cinza suficiente para rotular todos. Assim, diante deste cenario seria necessario alterar o tipo de dados, tendo que passar, por exemplo, para um tipo de dois bytes, passando a ter 65535 tons de cinza disponiveis. Passando para o algoritmo em si, o mesmo é baseado no programa [labeling.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/labeling.cpp) e consiste no seguinte algoritmo:
- Primeiramente, são varridas as bordas verticais da imagem carregada e, se for encontrado algum pixel com cor branca, aplica-se o *floodfill* no mesmo com a cor preta.
- Repete-se o mesmo procedimento para as bordas horizontais, resultando em uma imagem sem nenhuma bolha tocando as bordas.
- Após isso, realiza-se o *floodfill* no ponto (0,0) com alguma cor cinza (utilizou-se 120), visando deixar na cor preta apenas os supostos buracos de algumas bolhas.
- Em seguida, varre-se a imagem a procura de pixels de cor preta, incrementando o contador de buracos e apagando o mesmo aplicando-se *floodfill* na cor cinza quando encontrado um.
- Por fim, teremos apenas bolhas sem buracos nesta ultima etapa. Fazendo uma outra varredaura, podemos incrementar o contador de bolhas sem buracos e realizar o preenchimento naquele pixel usando a cor do contador (labeling classico) quando encontrado um de cor branca. 

As saidas do nosso [labeling.cpp](/labeling.cpp) obtidas a cada passo a passo são mostradas abaixo:

![labelingsembordas.png](/labelingsemborda.png "Saida labeling.cpp")
:--:
Saida labeling.cpp após retirar bolhas em todas as bordas

![labelingcinza.png](/labelingcinza.png "Saida labeling.cpp")
:--:
Saida labeling.cpp após aplicar *floodfill* no ponto (0,0)

![labelingsemburacos.png](/labelingsemburacos.png "Saida labeling.cpp")
:--:
Saida labeling.cpp após contar e retirar bolhas com buracos

![labelingfinal.png](/labelingfinal.png "Saida labeling.cpp")
:--:
Saida labeling.cpp após contar e rotular bolhas sem buracos

Como saida de texto, foi obtido:
```
$ ./labeling bolhas.png 
a figura tem 21 bolhas, sendo 14 sem buracos e 7 com buracos
```

### 4. Equalize
Utilizando como referência o programa [histogram.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/histogram.cpp), foi implementado o [equalize.cpp](/equalize.cpp), sendo responsavel por realizar a equalização do histograma para cada imagem capturada. O mesmo utiliza o a função *equalizeHist* do proprio *openCV*, além das funcoes *calcHist* (para calcular o histograma a partir da matriz de uma imagem) e *normalize* (para normalizar o mesmo). Apos isso, sao copiadas as imagens dos dois histogramas (normal e equalizado) nas imagens capturadas. A partir deles, é possivel ver com clareza as suas diferenças, tendo no histograma equalizado uma melhor distribuição das ocorrencias e portanto um melhor aproveitamento dos tons de cinza. As figuras abaixo foram obtidas a partir do [equalize.cpp](/equalize.cpp):

![equalizesaida.png](/equalizesaida.png "Saida equalize.cpp")
:--:
Saida equalize.cpp sem lanterna

![equalizeluzsaida.png](/equalizeluzsaida.png "Saida equalize.cpp")
:--:
Saida equalize.cpp com lanterna

### 5. Motion detector
O seguinte programa [motiondetector.cpp](/motiondetector.cpp) serve para detectar movimento atraves de uma câmera. Para o desenvolvimento do mesmo, utilizou-se a ideia de que, atraves de continuas comparações entre o histograma do frame atual e do frame passado, pode-se determinar se houve movimento a partir dessa diferença e considerando-se um limiar pré estabelecido. Passando para o codigo, primeiramente utilizamos a mesma estrategia do [histogram.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/histogram.cpp) para montar o histograma, sempre tendo dois armazenados (o atual e o anterior). Assim, utilizando a função *compareHist* do proprio *openCV*, é possivel obter a quantidade de variações entre os dois frames, que se for maior que um limite escolhido no valor 10 fará a tela piscar na cor branca (isso foi feito copiando para a tela principal um retângulo do tamanho da tela), evidenciando que foi detectado algum movimento.

### 6. Laplgauss
A partir do codigo [filtroespacial.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/filtroespacial.cpp) foi adicionada mais uma mascára, representando o filtro Laplaciano do Gaussiano para frames capturados por uma câmera. Assim, não houve grandes alterações na estrutura do codigo, apenas a adição da mascara do filtro em questão dada pela linha de codigo abaixo:

```c++
float laplaciangauss[] = {1, 1, 1, 1, -8, 1, 1, 1, 1};
```
Em seguida, foi criada uma nova opção de tecla (no caso, a tecla 's'), que irá corresponder a essa nova mascara criada. A partir disso, foi possivel ver diferenças claras entre esse filtro com a simples aplicação do filtro Laplaciano, tendo nesse ultimo uma marcação de bordas menos evidente se comparada com o Lapliaciano do Gaussiano, filtro que define muito mais as bordas. As imagens abaixo obtidas a partir do programa [laplgauss.cpp](/laplgauss.cpp) comprovam essa ideia:

![laplacian.png](/laplacian.png "Saida laplgaus.cpp")
:--:
Saida laplgaus.cpp usando filtro Laplaciano

![laplaciangauss.png](/laplaciangauss.png "Saida laplgaus.cpp")
:--:
Saida laplgaus.cpp usando filtro Laplaciano do Gaussiano

### 7. Tiltshift
Utilizando como base o programa [addweighted.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/addweighted.cpp), foi criado o programa [tiltshift.cpp](/tiltshift.cpp), visando a implementação de uma interface que permite a criação e configuração do efeito *tilt-shift* em imagens, sendo uma tecnica muito interessante que possibilita criar a ilusão de miniaturas. O principio utilizado para simular uma lente *tilt-shift* é combinar a imagem original com sua versão borrada, produzindo nas proximidades da borda o efeito do borramento enquanto se mantem na região central a imagem sem borramento. Assim, foi definida uma funcao α(x), representando a região de defoque ao longo do eixo vertical, utilizando valores de altura da região variaveis definidos pelo usuario através de sliders, podendo ser escolhida tambem a posição vertical e a força de decaimento dessa função de ponderamento. Atraves da funcao *multiply* ,do *openCV*, é possivel multiplicar a imagem original por α(x) e a imagem borrada (utilizou-se 10 filtros da media) por 1 - α(x), obtendo atraves da combinação linear dessas duas imagens o efeito simulado de *tilt-shift*. As imagens a seguir mostram o antes e depois de uma imagem modificada pelo [tiltshift.cpp](/tiltshift.cp).

![paisagem.jpg](/paisagem.jpg "Entrada tiltshift.cpp")
:--:
Entrada tiltshift.cpp

![tiltshiftsaida.jpg](/tiltshiftsaida.jpg "Saida tiltshift.cpp")
:--:
Saida tiltshift.cpp após ajuste nos sliders

### 8. Tiltshiftvideo
O programa comentado a seguir tem como proposito a aplicação do efeito *tilt-shift* em videos. O mesmo tambem se baseia no programa [addweighted.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/addweighted.cpp) e seu funcionamento é bem parecido com o do codigo [tiltshift.cpp](/tiltshift.cpp) tendo sua maior diferença justamente no tipo de objeto que será processado, sendo um video neste caso. Assim, para podermos gravar o resultado do *tlit-shift* em outro arquivo, as seguintes linhas de codigo foram adicionadas:
```c++
cv::VideoWriter captured;
captured.open("tiltshiftvideo.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(width,height));
```
Além disso, um em cada dois frames será descartado, evidenciando o efeito *stop motion* comum neste tipo de videos. Por fim, utilizamos a função *release()*, liberando o objeto processado.

## Segunda Unidade
Os codigos utilizados como base no decorrer desta unidade tambem foram obtidos a partir da [pagina pessoal do Professor Agostinho Brito](https://agostinhobritojr.github.io/tutorial/pdi/). Para a compilação dos codigos apresentados a seguir, será necessario possuir o arquivo [Makefile](/Makefile) no mesmo diretorio dos programas, podendo ser compilados e executados usando os seguintes comandos:
```
$ make <nome_programa>
$ ./<nome_programa> <arquivo_de_entrada>
```
### 9. Homomorfico
O codigo [homomorfico.cpp](/homomorfico.cpp) permite melhorar imagens em tons de cinza com iluminacao irregular atraves do ajuste de alguns parametros. Ele foi desenvolvido a partir do programa [dft.cpp](https://agostinhobritojr.github.io/tutorial/pdi/exemplos/dft.cpp), sendo utilizada a mesma funcao *deslocaDFT*. O programa primeiramente ira realizar um padding na imagem de entrada, calculando a resulacao adequada a partir da funcao *getOptimalDFTSize()*. Apos isso, a partir de qualquer alteracao de um dos sliders representando os 4 parametros (Gamma Low, Gamma High, C e Frequencia de corte), o metodo *applyFilter()* sera chamado para os novos valores dos parametros. Nele, vai haver o calculo da DFT (apos somar mais um a todos os pixels para caluclo do logaritmo), o deslocamento da mesma, a normalizacao do espectro e a chamada da funcao *homomorphico*. Nela vai haver o calculo do filtro em si, utilizando a respectiva equacao, e o mesmo sera multiplicado com a DFT da imagem, obtendo o resultado aplicando a DFT inversa. O melhoramento de uma imagem com iluminacao pessima utilizando o programa [homomorfico.cpp](/homomorfico.cpp) e mostrado nas imagens abaixo, apos ajuste manual dos parametros:

![semiluminacao.png](/semiluminacao.png "Entrada homomorfico.cpp")
:--:
Entrada homomorfico.cpp

![homomorficosaida.png](/homomorficosaida.png "Saida homomorfico.cpp")
:--:
Saida homomorfico.cpp
