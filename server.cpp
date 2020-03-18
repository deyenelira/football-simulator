#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
#define desl 1
#define codigoRetorno 60
#define codigoAleatorio 61
#define codigoStop 62
using namespace std;

int main(int argc, char const *argv[]){
	//coisas do servidor *---*
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	int recebo[1]={}; 
	int envio[1]={}; 
	
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	}

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	 
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	if (listen(server_fd, 3) < 0){ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 

	//interface grafica *-*


	sf::RenderWindow window(sf::VideoMode(600, 701), "Samiquinho");

	window.clear(sf::Color::White);
	sf::RectangleShape rectangle(sf::Vector2f(600,700));
	rectangle.setFillColor(sf::Color(0,100,0));

	sf::Vertex direita[] = {
		sf::Vertex(sf::Vector2f(25,25)),
		sf::Vertex(sf::Vector2f(25,675))
	};
	sf::Vertex esquerda[] = {
		sf::Vertex(sf::Vector2f(575,25)),
		sf::Vertex(sf::Vector2f(575,675))
	};
	sf::Vertex cima[] = {
		sf::Vertex(sf::Vector2f(25,25)),
		sf::Vertex(sf::Vector2f(575,25))
	};
	sf::Vertex baixo[] = {
		sf::Vertex(sf::Vector2f(25,675)),
		sf::Vertex(sf::Vector2f(575,675))
	};
	sf::Vertex meio[] = {
		sf::Vertex(sf::Vector2f(25,351)),
		sf::Vertex(sf::Vector2f(575, 351))
	};

	sf::CircleShape Cmeio(40);
	Cmeio.setFillColor(sf::Color::Transparent);
	Cmeio.setOutlineThickness(1);
	Cmeio.setOutlineColor(sf::Color(255,255,255));
	Cmeio.setOrigin(-260,-310);

	sf::CircleShape bola(5);
	bola.setFillColor(sf::Color::Red);
	bola.setOutlineThickness(1);
	bola.setOutlineColor(sf::Color::Black);
	bola.setOrigin(-296,-345);

	sf::CircleShape jogadorAa(20);
	jogadorAa.setFillColor(sf::Color::Yellow);
	jogadorAa.setOutlineThickness(1);
	jogadorAa.setOutlineColor(sf::Color::Black);
	jogadorAa.setPosition(280,395);
	int xAa=280, yAa=395;

	sf::CircleShape jogadorAb(20);
	jogadorAb.setFillColor(sf::Color::Yellow);
	jogadorAb.setOutlineThickness(1);
	jogadorAb.setOutlineColor(sf::Color::Black);
	jogadorAb.setPosition(200,500);
	int xAb=200, yAb=500;

	sf::CircleShape jogadorAc(20);
	jogadorAc.setFillColor(sf::Color::Yellow);
	jogadorAc.setOutlineThickness(1);
	jogadorAc.setOutlineColor(sf::Color::Black);
	jogadorAc.setPosition(362,500);
	int xAc=362, yAc=500;

	sf::CircleShape jogadorBa(20);
	jogadorBa.setFillColor(sf::Color::Blue);
	jogadorBa.setOutlineThickness(1);
	jogadorBa.setOutlineColor(sf::Color::Black);
	jogadorBa.setPosition(280,265);
	int xBa=280, yBa=265;

	sf::CircleShape jogadorBb(20);
	jogadorBb.setFillColor(sf::Color::Blue);
	jogadorBb.setOutlineThickness(1);
	jogadorBb.setOutlineColor(sf::Color::Black);
	jogadorBb.setPosition(200,160);
	int xBb=200, yBb=160;

	sf::CircleShape jogadorBc(20);
	jogadorBc.setFillColor(sf::Color::Blue);
	jogadorBc.setOutlineThickness(1);
	jogadorBc.setOutlineColor(sf::Color::Black);
	jogadorBc.setPosition(362,160);
	int xBc=362, yBc=160;

	sf::Vertex golA[] = {
		sf::Vertex(sf::Vector2f(200,100)),
		sf::Vertex(sf::Vector2f(400,100))
	};
	sf::Vertex golB[] = {
		sf::Vertex(sf::Vector2f(200,25)),
		sf::Vertex(sf::Vector2f(200,100))
	};
	sf::Vertex golC[] = {
		sf::Vertex(sf::Vector2f(400,25)),
		sf::Vertex(sf::Vector2f(400,100))
	};
	sf::Vertex golD[] = {
		sf::Vertex(sf::Vector2f(200,601)),
		sf::Vertex(sf::Vector2f(400,601))
	};
	sf::Vertex golE[] = {
		sf::Vertex(sf::Vector2f(200,676)),
		sf::Vertex(sf::Vector2f(200,601))
	};
	sf::Vertex golF[] = {
		sf::Vertex(sf::Vector2f(400,676)),
		sf::Vertex(sf::Vector2f(400,601))
	};

	int flag = 0, extra=0, vet[10] = {};
	/*
		Flag é uma variável para que eu sete qual jogador deve ser movido :) Ela assume valores de 0 a 6, onde 0 é o estado
		em que nenhum jogador é movido, e os estados de 1 a 6 são os estados em que os respectivos jogadores podem ser movidos

		Extra é a variável que me diz se o usuário quer ativar comandos especiais, ela assume valores de 0 a 2, onde 0 é o estado
		em que não há comandos. 

		vet é o vetor que me auxiliou na programação do comando extra==2!
	*/
	while(window.isOpen()){

		sf::Event evento;
		while(window.pollEvent(evento)){
			if(evento.type == sf::Event::Closed){
				window.close();
			}
		}
		valread = read(new_socket , recebo, 1);

		if(recebo[0]==1) flag = 1;
		else if(recebo[0]==2) flag = 2;
		else if(recebo[0]==3) flag = 3;
		else if(recebo[0]==4) flag = 4;
		else if(recebo[0]==5) flag = 5;
		else if(recebo[0]==6) flag = 6;

		if(recebo[0] == codigoRetorno) extra = 1;
		if(recebo[0] == codigoAleatorio) extra = 2;
		if(recebo[0] == codigoStop) extra = 0;
		
		if(extra==1){
			if(xAa<280){
				xAa++;
				jogadorAa.setPosition(xAa,yAa);
			}else if(xAa>280){
				xAa--;
				jogadorAa.setPosition(xAa,yAa);
			}
			if(yAa>395){
				yAa--;
				jogadorAa.setPosition(xAa,yAa);
			}else if(yAa<395){
				yAa++;
				jogadorAa.setPosition(xAa,yAa);
			}
			//Ab
			if(xAb<200){
				xAb++;
				jogadorAb.setPosition(xAb, yAb);
			}else if(xAb>200){
				xAb--;
				jogadorAb.setPosition(xAb, yAb);
			}
			if(yAb>500){
				yAb--;
				jogadorAb.setPosition(xAb, yAb);
			}else if(yAb<500){
				yAb++;
				jogadorAb.setPosition(xAb, yAb);
			}
			//Ac
			if(xAc<362){
				xAc++;
				jogadorAc.setPosition(xAc, yAc);
			}else if(xAc>362){
				xAc--;
				jogadorAc.setPosition(xAc, yAc);
			}
			if(yAc>500){
				yAc--;
				jogadorAc.setPosition(xAc, yAc);
			}else if(yAc<500){
				yAc++;
				jogadorAc.setPosition(xAc, yAc);
			}
			//Ba
			if(xBa>280){
				xBa--;
				jogadorBa.setPosition(xBa, yBa);
			}else if(xBa<280){
				xBa++;
				jogadorBa.setPosition(xBa, yBa);
			}
			if(yBa>265){
				yBa--;
				jogadorBa.setPosition(xBa, yBa);
			}else if(yBa<265){
				yBa++;
				jogadorBa.setPosition(xBa, yBa);
			}
			//Bb
			if(xBb>200){
				xBb--;
				jogadorBb.setPosition(xBb, yBb);
			}else if(xBb<200){
				xBb++;
				jogadorBb.setPosition(xBb, yBb);
			}
			if(yBb>160){
				yBb--;
				jogadorBb.setPosition(xBb, yBb);
			}else if(yBb<160){
				yBb++;
				jogadorBb.setPosition(xBb, yBb);
			}
			//Bc
			if(xBc>362){
				xBc--;
				jogadorBc.setPosition(xBc, yBc);
			}else if(xBc<362){
				xBc++;
				jogadorBc.setPosition(xBc, yBc);
			}
			if(yBc>160){
				yBc--;
				jogadorBc.setPosition(xBc, yBc);
			}else if(yBc<160){
				yBc++;
				jogadorBc.setPosition(xBc, yBc);
			}
			if(xAa==280 && yAa==395){
				if(xAb==200 && yAb==500){
					if(xAc==362 && yAc==500){
						if(xBa==280 && yBa==265){
							if(xBb==200 && yBb==160){
								if(xBc==362 && yBc==160){
									extra = 0;
								}
							}
						}
					}
				}
			}
		}
		if(extra==2){
			//Aa
			if(xAa>25 && vet[0]==0 && flag!=1){
				xAa--;
				jogadorAa.setPosition(xAa, yAa);
			}
			if(yAa>140 && vet[0]==0 && flag!=1){
				yAa--;
				jogadorAa.setPosition(xAa, yAa);
			}
			if(xAa==25 && yAa==140 && vet[0]==0 && flag!=1){
				vet[0]=2;
			} 
			if(xAa<280 && vet[0]==2 && flag!=1){
				xAa++;
				jogadorAa.setPosition(xAa, yAa);
			}
			if(yAa<395 && vet[0]==2 && flag!=1){
				yAa++;
				jogadorAa.setPosition(xAa, yAa);
			}
			if(xAa==280 && yAa==395 && vet[0]==2 && flag!=1){
				vet[0] = 0;
			} 
			//Ab
			if(xAb<500 && vet[1]==0 && flag!=2){
				xAb++;
				jogadorAb.setPosition(xAb, yAb);
			}
			if(yAb>135 && vet[1]==0 && flag!=2){
				yAb--;
				jogadorAb.setPosition(xAb, yAb);
			}
			if(xAb==500 && yAb==135 && vet[1]==0 && flag!=2){
				vet[1]=2;
			} 
			if(xAb>200 && vet[1]==2 && flag!=2){
				xAb--;
				jogadorAb.setPosition(xAb, yAb);
			}
			if(yAb<500 && vet[1]==2 && flag!=2){
				yAb++;
				jogadorAb.setPosition(xAb, yAb);
			}
			if(xAb==200 && yAb==500 &&vet[1]==2 && flag!=2){
				vet[1]=0;
			} 
			//Ac
			if(xAc>100 && vet[2]==0 && flag!=3){
				xAc--;
				jogadorAc.setPosition(xAc, yAc);
			}
			if(yAc>140 && vet[2]==0 && flag!=3){
				yAc--;
				jogadorAc.setPosition(xAc, yAc);
			}
			if(xAc==100 && yAc==140 && vet[2]==0 && flag!=3){
				vet[2]=2;
			} 
			if(xAc<362 && vet[2]==2 && flag!=3){
				xAc++;
				jogadorAc.setPosition(xAc, yAc);
			}
			if(yAc<500 && vet[2]==2 && flag!=3){
				yAc++;
				jogadorAc.setPosition(xAc, yAc);
			}
			if(xAc==362 && yAc==500 && vet[2]==2 && flag!=3){
				vet[2]=0;
			} 
			//Ba 
			if(xBa>100 && vet[3]==0 && flag!=4){
				xBa--;
				jogadorBa.setPosition(xBa, yBa);
			}
			if(yBa<500 && vet[3]==0 && flag!=4){
				yBa++;
				jogadorBa.setPosition(xBa, yBa);
			}
			if(xBa==100 && yBa==500 && vet[3]==0 && flag!=4){
				vet[3]=2;
			} 
			if(xBa<280 && vet[3]==2 && flag!=4){
				xBa++;
				jogadorBa.setPosition(xBa, yBa);
			}
			if(yBa>265 && vet[3]==2 && flag!=4){
				yBa--;
				jogadorBa.setPosition(xBa, yBa);
			}
			if(xBa==280 && yBa==265 && vet[3]==2 && flag!=4){
				vet[3]=0;
			} 
			//Bb 
			if(xBb<500 && vet[4]==0 && flag!=5){
				xBb++;
				jogadorBb.setPosition(xBb, yBb);
			}
			if(yBb<600 && vet[4]==0 && flag!=5){
				yBb++;
				jogadorBb.setPosition(xBb, yBb);
			}
			if(xBb== 500 && yBb== 600 && vet[4]==0 && flag!=5){
				vet[4]=2;
			} 
			if(xBb>200 && vet[4]==2 && flag!=5){
				xBb--;
				jogadorBb.setPosition(xBb, yBb);
			}
			if(yBb>160 && vet[4]==2 && flag!=5){
				yBb--;
				jogadorBb.setPosition(xBb, yBb);
			}
			if(xBb==200 && yBb==160 && vet[4]==2 && flag!=5){
				vet[4]=0;
			} 
			//Bc 
			if(xBc>25 && vet[5]==0 && flag!=6){
				xBc--;
				jogadorBc.setPosition(xBc, yBc);
			}
			if(yBc<600 && vet[5]==0 && flag!=6){
				yBc++;
				jogadorBc.setPosition(xBc, yBc);
			}
			if(xBc== 25 && yBc== 600 && vet[5]==0 && flag!=6){
				vet[5]=2;
			} 
			if(xBc<362 && vet[5]==2 && flag!=6){
				xBc++;
				jogadorBc.setPosition(xBc, yBc);
			}
			if(yBc>160 && vet[5]==2 && flag!=6){
				yBc--;
				jogadorBc.setPosition(xBc, yBc);
			}
			if(xBc==362 && yBb==160 && vet[5]==2 && flag!=6){
				vet[5]=0;
			} 	
		}
		if(flag==1){
			if(recebo[0]==20){
				xAa+=desl;
				jogadorAa.setPosition(xAa,yAa);
			}else if(recebo[0]==21){
				xAa-=desl;
				jogadorAa.setPosition(xAa,yAa);
			}else if(recebo[0]==22){
				yAa-=desl;
				jogadorAa.setPosition(xAa,yAa);
			}else if(recebo[0]==23){
				yAa+=desl;
				jogadorAa.setPosition(xAa,yAa);
			}
		}else if(flag==2){
			if(recebo[0]==20){
				xAb+=desl;
				jogadorAb.setPosition(xAb,yAb);
			}else if(recebo[0]==21){
				xAb-=desl;
				jogadorAb.setPosition(xAb,yAb);
			}else if(recebo[0]==22){
				yAb-=desl;
				jogadorAb.setPosition(xAb,yAb);
			}else if(recebo[0]==23){
				yAb+=desl;
				jogadorAb.setPosition(xAb,yAb);
			}
		}else if(flag==3){
			if(recebo[0]==20){
				xAc+=desl;
				jogadorAc.setPosition(xAc,yAc);
			}else if(recebo[0]==21){
				xAc-=desl;
				jogadorAc.setPosition(xAc,yAc);
			}else if(recebo[0]==22){
				yAc-=desl;
				jogadorAc.setPosition(xAc,yAc);
			}else if(recebo[0]==23){
				yAc+=desl;
				jogadorAc.setPosition(xAc,yAc);
			}
		}else if(flag==4){
			if(recebo[0]==20){
				xBa+=desl;
				jogadorBa.setPosition(xBa,yBa);
			}else if(recebo[0]==21){
				xBa-=desl;
				jogadorBa.setPosition(xBa,yBa);
			}else if(recebo[0]==22){
				yBa-=desl;
				jogadorBa.setPosition(xBa,yBa);
			}else if(recebo[0]==23){
				yBa+=desl;
				jogadorBa.setPosition(xBa,yBa);
			}
		}else if(flag==5){
			if(recebo[0]==20){
				xBb+=desl;
				jogadorBb.setPosition(xBb,yBb);
			}else if(recebo[0]==21){
				xBb-=desl;
				jogadorBb.setPosition(xBb,yBb);
			}else if(recebo[0]==22){
				yBb-=desl;
				jogadorBb.setPosition(xBb,yBb);
			}else if(recebo[0]==23){
				yBb+=desl;
				jogadorBb.setPosition(xBb,yBb);
			}
		}else if(flag==6){
			if(recebo[0]==20){
				xBc+=desl;
				jogadorBc.setPosition(xBc,yBc);
			}else if(recebo[0]==21){
				xBc-=desl;
				jogadorBc.setPosition(xBc,yBc);
			}else if(recebo[0]==22){
				yBc-=desl;
				jogadorBc.setPosition(xBc,yBc);
			}else if(recebo[0]==23){
				yBc+=desl;
				jogadorBc.setPosition(xBc,yBc);
			}
		}
		recebo[0]=0;

		window.clear(sf::Color::White);
		window.draw(rectangle);
		window.draw(direita, 2, sf::Lines);
		window.draw(esquerda, 2, sf::Lines);
		window.draw(cima, 2, sf::Lines);
		window.draw(baixo, 2, sf::Lines);
		window.draw(Cmeio);
		window.draw(meio, 2, sf::Lines);
		window.draw(golA, 2, sf::Lines);
		window.draw(golB, 2, sf::Lines);
		window.draw(golC, 2, sf::Lines);
		window.draw(golD, 2, sf::Lines);
		window.draw(golE, 2, sf::Lines);
		window.draw(golF, 2, sf::Lines);
		window.draw(bola);
		window.draw(jogadorAa);
		window.draw(jogadorAb);
		window.draw(jogadorAc);
		window.draw(jogadorBa);
		window.draw(jogadorBb);
		window.draw(jogadorBc);

		window.display();
	}
	return 0;
}
