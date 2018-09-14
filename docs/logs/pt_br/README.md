# LOGS:

Este arquivo contém os logs de todos os dias do desenvolvimento da primeira versão do ESPBoy.

## DIA 1:

Clonei os Seguintes repositórios:

* [ESP32 Game Playes with NES](https://github.com/nickfox-taterli/nes-game-with-sound-esp32);
* [esp32-nesemu](https://github.com/espressif/esp32-nesemu)

Fiz o teste do **ESP32 Game Playes with NES** porém, nos primeiros testes o ESP32 informava no log que havia pouca RAM disponível, e portanto o ESP32 reiniciava a todo momento. Assistindo ao [vídeo](https://www.youtube.com/watch?v=6oSsaTSyXGw) e vi que é recomendado desativar a o módulo WIFI no **menuconfig**.

Resolvi testar o porte "oficial" realizado pela empresa **espressif** o **esp32-nesemu**. Ao iniciar o programa(make flash monitor), o log não informava nenhum erro. Então resolvi gravar a ROM na memória Flash do ESP32 utilizando o script que veio junto com o projeto chamado **flashrom.sh** (é... o nome é sujestivo). Para tal, eu tive que editar o script para informar a porta serial e o arquivo **.nes** para gravar no endereço 0x100000 da FLASH. Ao terminar a gravação eu reiniciei o programa, dando o comando **make monitor**, e voilá! O ESP32 **"piscava"** com a imagem de abertura do Super Mário. E o LOG informava que estava tudo correto. Porém a imagem não ficava fixa no jogo, ele desligava a todo momento como se estivesse reiniciando. 

Depois de muito ler e estudar o projeto eu percebi que há a opção de inverter o backlight. E esse foi o grand finalle do 1º dia de execução do projeto. O resultado foi esse:

![ESPBoy](https://i.imgur.com/Mp6zmX2.jpg)

[ESPBoy-GIF](https://i.imgur.com/GFvoeQj.mp4)

## DIA 2:

Realizei alguns testes com o emulador, gravei ROM's diferentes na memória e modifiquei o script para permitir a passagem da porta serial como argumento.

![ESPBoy-Teste2](https://i.imgur.com/73btcPw.jpg)

Em seguida montei o circuito em uma protoboard para realizar alguns testes com o circuito. Montei o **Joypad** também, e para fazer-lo funcionar eu tive que modificar  as funções **psxcontrollerInit()** e **psxReadInput()** no arquivo **psxcontroller.c**.  Precisei fazer a função **psxcontrollerInit()** retornar um inteiro com os bits com os status dos botões da seguinte forma:

* BIT 0: SELECT;
* BIT 1: 1;
* BIT 2: 1;
* BIT 3: START;
* BIT 4: UP;
* BIT 5: RIGHT;
* BIT 6: DOWN;
* BIT 7: LEFT;
* BIT 8: 1;
* BIT 9: 1;
* BIT 10: 1;
* BIT 11: 1;
* BIT 12: SOFT_RESET;
* BIT 13: A;
* BIT 14: B;
* BIT 15: HARD_RESET;

Eu não encontrei referências para o uso dos bits 1, 2, 8, 9, 10, 11, 12 e 15. Mas a emulação funcionou muito bem apenas com os demais bits.

## DIA 3:

Fiz uma pequena modificação no joypad para fins de liberar algumas GPIOs para inserir botões de volume(aumentar e diminuir) e um botão de menu/reset. A modificação foi simples, ao invés de eu utilizar 1 GPIO para cada botão direcional, eu usei 2 linhas analógicas. Cada linha analógica é responsável por ler dois botões através de um divisor de tensão. O conceito pode ser visualizado na imagem abaixo:

![Reading Keys by Analog lines](https://i.stack.imgur.com/Cq9kc.jpg) 

Na sequência inseri um buzzer no terminal D26 do ESP32 para experimentar a saída de áudio. A qualidade de som não é das melhores e falta um amplificador de áudio para a saída do som, e também o buzzer não foi feito para reproduzir tons polifônicos. O resultado pode ser observado no vídeo abaixo.

[ESPBoy - Teste 2](https://youtu.be/8dRg0GTs4dQ)

## DIA 4:

Teste com o VOLUME... sem sucesso.

## DIA 5:

Teste com o Volume, um pouco de sucesso, agora consigo pelo menos alterar de leve o volume, nada considerável. A qualidade do som ainda é um problema. Mas só de conseguir alterar o volume já está ótimo.

## DIA 6:

Alterar os terminais e criar o diagrama esquemático para ser confeccionado a placa de circuito impresso.

Tentatei inserir um circuito para a detecção automática do fone de ouvido e assim desligar o alto falante. 

### Terminais Utilizados no projeto.

* Display

| TFT | ESP32 |
|:---------:|:------:|
| DC | 21 |
| CS | 5 |
| BKL | 4 |
| MOSI | 23 |
| MISO | 19 |
| SCLK | 18 |
| RST | EN |

* SD Card

| SD | ESP32 |
|:---:|:-------:|
| MISO | 19 |
| MOSI | 23 |
| CLK | 18 |
| CS | 22 | 

## Dia 6:

Nesse dia foi iniciado o desenho do diagrama esquemático e da placa de circuito impresso. Para isso, foi utilizado a plataforma de desenvolvimento online do [EasyEDA](www.easyeda.com).

## Dia 7:

Para o desenvolvimento da placa de circuito impresso irei levar em consideração as dimensões do GameBoy/GameBoy Color e GameBoy Advance. Como será confeccionado o modelo 3D do gabinete eu pretendo utilizar como base o layout dos GameBoys, e portanto a placa deverá ter as dimensões e o layout do Gameboy. Os layouts e dimensões podem ser encontrados abaixo:

### GameBoy/GameBoy Color

![](https://www.the-blueprints.com/modules/vectordrawings/preview-wm/nintendo_gameboy_classic.jpg)

### GameBoy Advance

![](https://vignette.wikia.nocookie.net/mario/images/7/78/Game_Boy_Advance_-_Transparent_Purple_Model.png/revision/latest?cb=20120513192900)

## Dia 8:

Foi utilizado o software de desenvolvimento de circuitos e placas de circuito impresso online [EasyEDA](https://easyeda.com) para o desenvolvimento do diagrama esquemático  e da placa de circuito impresso do [ESPBoy](https://easyeda.com/Calebe94/ESPBoy). E para a confecção da mesma foi utilizada uma máquina CNC. 

![cnc](https://i.imgur.com/iY13WMf.jpg)

O resultado pode ser verificado na imagem abaixo:

![ESPBoy-PCB](https://i.imgur.com/mkLqXRc.jpg)
-------

# Circuitos e esquemáticos de Referência:

## Áudio:

* Jack P2 Fêmea: ![](https://www.avrfreaks.net/sites/default/files/microphone%20jack.jpg)
* Jack P2 Macho: ![](http://cdn3.howtogeek.com/wp-content/uploads/2014/01/iphone-3.5mm-headset-connector-pinout.jpg)
* PreAmp: ![](http://hackaweek.com/hacks/wp-content/uploads/2011/08/transistor-preamp-schematic.jpg)
* Jack-Sensing Circuit: ![](https://www.maximintegrated.com/en/images/appnotes/4607/4607Fig01.gif)

-------

# Custom Games:

* [PwnAdventureZ](https://github.com/Vector35/PwnAdventureZ)

-------
# Referências:

* [Add a Discrete Jack-Sensing Circuit to the MAX13330/MAX13331 Automotive Headphone Amplifier](https://www.maximintegrated.com/en/app-notes/index.mvp/id/4607)