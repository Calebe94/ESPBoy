# ESPBoy

Under develompent... 

![ESPBoy](https://github.com/Calebe94/ESPBoy/blob/master/resources/media/ESPBoy.jpg?raw=true)

# Table of Contents

* [Description](#description)

* [Setup](#setup)

* [Team](#team)

* [License](#license)

# Description

This portable console is(or must be) capable to emulate games from the 4º generation of game consoles (the portable ones) such as Sega Game Gear and Nintendo Game Boy and the 3º generation such as Sega Master System and Nintendo Entertainment System.

# Basic BOM

| Quantity | Component | Image | Price |
|:---:|:---:|:---:|:---:|
| 1  | **ESP32 DevKit** | <img src="https://user-images.githubusercontent.com/9260214/28747595-19a41090-7471-11e7-826c-42c28ea7ae6e.jpeg" alt="drawing" width="50px"/> | [R$ 42](https://produto.mercadolivre.com.br/MLB-984073556-esp32-modulo-wifi-bluetooth-dual-core-_JM) |
| 1 | **Display 2,4" TFT 320x240** | <img src="https://cdn.instructables.com/F6K/HE7N/HV9FW89M/F6KHE7NHV9FW89M.MEDIUM.jpg" alt="drawing" width="50px"/> | [R$ 55](https://produto.mercadolivre.com.br/MLB-938123113-display-lcd-24-tft-320x240-true-color-com-sdcard-_JM) |
| 1 | **Módulo Amplificador PAM8403** | <img src="http://img.dxcdn.com/productimages/sku_347324_1.jpg" alt="drawing" width="50px"/> | [R$ 5](https://produto.mercadolivre.com.br/MLB-1043419825-modulo-amplificador-som-estereo-2ch-3w3w-pam8403-arduino-_JM) |
| 1 | **Módulo Carregador de Bateria de Lítio TP4056** | <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQA92OUxTKaQUOB_EKJUX6VIEH7u0vOoNI_9zUhEZbgWjft_AOv6A" alt="drawing" width="50px"/> | [R$ 5](https://produto.mercadolivre.com.br/MLB-891587521-tp4056-mini-usb-carregador-bateria-litio-1a-5v-lithium-_JM) |
| 1 | **Mini Alto Falante 2W 8 Ohms** | <img src="https://http2.mlstatic.com/D_NQ_NP_364815-MLB25313344771_012017-F.jpg" alt="drawing" width="50px"/> | [R$ 8](https://produto.mercadolivre.com.br/MLB-833938086-mini-alto-falante-28mm-2-wats-rms-8-ohms-eletrnicaarduino-_JM) |
| 1 | **Bateria de Litio >600mAh** | <img src="https://images-na.ssl-images-amazon.com/images/I/51MwOUWv5jL._SY355_.jpg" alt="drawing" width="50px"/> |  [R$ 35](https://produto.mercadolivre.com.br/MLB-1005574636-bateria-37v-400mah-litio-polimero-35038-_JM) |
| 10 | **Push Button** | <img src="https://uploads.filipeflop.com/2017/07/pushbutton3.jpg" alt="drawing" width="50px"/>| [R$3](https://www.filipeflop.com/produto/chave-tactil-push-button-x10-unidades/) |

# Setup

Clone the repo:

```
git clone https://github.com/Calebe94/ESPBoy

cd ESPBoy/software

git submodule update --init .

cp ../utils/makefiles/lvgl_component.mk components/Libs/lvgl/component.mk

make all

make flash
```


# Team

| <img src="https://github.com/Calebe94.png?size=200" alt="Edimar Calebe Castanho"> | 
|:---------------------------------------------------------------------------------:|
| [Edimar Calebe Castanho (Calebe94)](https://github.com/Calebe94)                  |

## Contributing

Comming soon...

# License

All software is covered under [MIT License](https://opensource.org/licenses/MIT).

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
