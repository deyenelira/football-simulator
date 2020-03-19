#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
#define PORT 8080 
#define direita 20
#define esquerda 21
#define cima 22
#define baixo 23
#define codigoRetorno 60
#define codigoAleatorio 61
#define codigoStop 62

int main(int argc, char const *argv[]){

	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	int envia[1]; 
	int recebo[1]; 

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 

    int log;
    while(1){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            log = 1;
            envia[0] = 1;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            log = 2;
            envia[0] = 2; 
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
            log = 3;
            envia[0] = 3;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
            log = 4;
            envia[0] = 4;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
            log = 5;
            envia[0] = 5;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
            log = 6;
            envia[0] = 6;
        }
		
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		envia[0]=direita;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		envia[0]=esquerda;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		envia[0]=cima;
	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		envia[0]=baixo;
	}else envia[0] = log;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) envia[0] = codigoRetorno;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) envia[0] = codigoAleatorio;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) envia[0] = codigoStop;

	send(sock , envia, 1, 0 ); 
    }

	return 0; 
} 
