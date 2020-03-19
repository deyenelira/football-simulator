# Projeto_maracatronics
Simulador de futebol desenvolvido para o processo seletivo do Maracatronics-UFPE

-> Compilação: 

compilando a server.cpp: 
g++ -c server.cp 
g++ server.o -o server -lsfml-graphics -lsfml-window -lsfml-system
./server

compilando o client.cpp:
g++ -c client.cpp 
g++ client.o -o client -lsfml-graphics -lsfml-window -lsfml-system 
./client

 -> Comandos:
 
 'Z' = ativa a movimentação do jogador Aa (time amarelo)
 
 'X' = ativa a movimentação do jogador Ab (time amarelo)
 
 'C' = ativa a movimentação do jogador Ac (time amarelo)
 
 'V' = ativa a movimentação do jogador Ba (time azul)
 
 'B' = ativa a movimentação do jogador Bb (time azul)
 
 'N' = ativa a movimentação do jogador Bc (time azul)
 
 'Q' = retorna todos os jogadores para a posição inicial
 
 'W' = movimenta todos os jogadores pelo campo, exceto o jogador que está ativado pelo usurário, caso nenhum jogador tenha sido
  ativado ainda, todos eles se movem
  
  Esc = cancela os comandos 'Q' e 'W'
  
  Up = move o jogador ativado para cima
  
  Down = move o jogador ativado para baixo
  
  Right = move o jogador ativado para a direita
  
  Left = move o jogador ativado para a esquerda
  
