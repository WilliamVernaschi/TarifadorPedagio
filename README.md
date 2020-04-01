# Tarifador Automático

O tarifador de pedágio automático foi um projeto realizado como TCC na instituição SENAI "A. Jacob Lafer".
O principal objetivo foi demonstrar a possibilidade de automatização de pagamentos em lugares como teatros, cinemas, museus, etc usando o microcontrolador PIC18F4550. Para isso, utilizamos como exemplo o pedágio, no GIF abaixo, está uma exemplificação de como seria feita sua aplicação.

![First_gif](https://media.giphy.com/media/S9JuOtzOiBnwzRuYRh/giphy.gif)

E logo abaixo está o resultado final do projeto:

![Second_gif](https://media.giphy.com/media/Q5XGqpC02qVaraq94r/giphy.gif)

No início do processo, o LCD mostra o valor total que deve ser pago. A cada moeda inserida no moedeiro, é mostrado o valor total das moedas inseridas, quando o valor atinge o total que deve ser pago, a cancela controlada por um servo motor é levantada e um LED verde é aceso. Quando o carro passa pela cancela e atravessa um feixe de sensor infravermelho, a cancela é abaixada, o LED volta ao vermelha e o LCD mostra o valor para que o motorista seguinte pague.

Abaixo, estão circuitos utilizados para criar a PCB que controla o os periféricos.

![schematic0](https://i.imgur.com/woCxi3x.png)
![schematic1](https://i.imgur.com/BmZMK1s.png)
![schematic2](https://i.imgur.com/DhWWAsJ.png)
![schematic3](https://i.imgur.com/XYF3ggE.png)
![schematic4](https://i.imgur.com/9jjj24O.png)
![schematic5](https://i.imgur.com/BiSDkpq.png)
![schematic6](https://i.imgur.com/U2rXYYF.png)
![schematic7](https://i.imgur.com/FxL7pWm.png)
![schematic8](https://i.imgur.com/E7pcZ34.png)
