Avanços:
- Tem algumas funções do ANSI/VT100;
- Geração do Tabuleiro, com as bombas;
- Defini as linhas como letras e as colunas como números (mas podemos mudar depois);

- O jogador pode escolher botar uma bandeira, interrogação, remover um deles ou abrir um bloco;
    -> Para botar uma bandeira: "@ [linha] [coluna]";
    -> Para botar uma interrogação: "? [linha] [coluna]";
    -> Para remover uma ? ou @: "R/r [linha] [coluna]"; 
    -> Para abrir um bloco: "A/a [linha] [coluna]";

- Quando abre um bloco o programa já realiza as aberturas necessárias;
- Se o usuário clicar numa bomba, ele perde o jogo;
- Se só sobrarem bombas no tabuleiro, ele ganha;

- Sobre os números no campo:
    -> -41: bomba que fez o jogador perder;
    -> -40: bomba que não tinha bandeira em cima;
    -> -30: tinha bandeira, mas não era bomba; 
    -> -20 ou -21: bandeira em cima do bloco;
    -> -10 ou -11: dúvida quanto ao bloco;
    -> -1: não foi aberto e tem bomba;
    -> 0: não foi aberto e não tem bomba;
    -> 1 a 8: já foi aberto e tem bombas em volta;
    -> 9: já foi aberto e não tem nada em volta;


- Simbologia dos números do campo:
    "*X@?0123456789"

    -> -41: '*' (em vermelho, em negrito e piscando)
    -> -40: '*' (em negrito e branco [mas acho que seria melhor botar preto, quando mudarmos o fundo])
    -> -30: 'X' (em vermelho, em negrito)
    -> -20 ou -21: '@' (amarelo e em negrito)
    -> -10 ou -11: '?' (amarelo e em negrito)
    -> -1: '0' (o usuário não sabe que tem bomba)
    -> 0: '0' (branco)
    -> 1 a 8: '1' a '8' (a cor depende do número)
    -> 9: '-' (branco mais fraco)


- Cor dos números:
    -> 1 e 5 -> azul
    -> 2 e 6 -> verde
    -> 3 e 7 -> vermelho 
    -> 4 e 8 -> magenta (mas pode ser que tenha uma opção melhor)





Detalhes importantes:

Em ANSI/VT100, você consegue alterar as informações do display.
ESC é representado por '^[' que para o printf (em octal) é \033 

Links uteis: 
    - http://www.termsys.demon.co.uk/vtansi.htm
    - https://espterm.github.io/docs/VT100%20escape%20codes.html
