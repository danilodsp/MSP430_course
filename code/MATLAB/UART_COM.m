% Ap�s identificar qual a porta virtual a que seu dispositivo est�
% associado, crie um objeto para aquela porta
s = serial('COM7')

fopen(s)

% Set todos os par�metros que precisar.
set(s, 'Timeout', 2)


% Para testar se tudo deu certo, curtocircuite os pinos P1.1 e P1.2 de
% seu Launchpad e envie alguma coisa

fprintf(s, '%s', 'Deu certo?')

% Agora, se voc� tiver feito os �ltimos passos corretamente, tente ler
% a mensagem enviada
fscanf(s)

% Se quiser fechar a porta aberta, use a fun��o abaixo
% fclose(s)
