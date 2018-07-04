#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>
using namespace std;
struct personagem{
	char nome[20];
	int id, vida_max, atk, xp, lv;
};
int selecionar();
void criar();
void luta(personagem heroi);
void salvar(personagem heroi);
int pegar_xp(int lv);
int conta_char();
main(){
	srand(time(NULL));
	personagem heroi_ativo;
	char get[200];
	int heroi=0, menu, cont=0;
	system("color 4d");
	setlocale(LC_ALL, "portuguese");
	cout<<"\n##################GAME###############\n";
	cout<<"1 - Selecionar personagem\n2 - Criar personagem\n3 - Sair\n";
	cin>> menu;
	fflush(stdin);
	if(menu == 1){
		heroi = selecionar();
		heroi -= 1;
		fstream hero;
		hero.open("chardata.txt", ios::in);
		for(cont=heroi; cont>0; cont--){
			hero.getline(get, 180);
		}
		hero.getline(get, 1, '#');
		//pegando o ID, nome, vida...
		hero.getline(get,15, '#');
		heroi_ativo.id = atoi(get);
		hero.getline(get,15, '#');
		strcpy(heroi_ativo.nome,get);
		hero.getline(get,15, '#');
		heroi_ativo.vida_max = atoi(get);
		hero.getline(get,15, '#');
		heroi_ativo.atk = atoi(get);
		hero.getline(get,15, '#');
		heroi_ativo.lv = atoi(get);
		hero.getline(get,15, '#');
		heroi_ativo.xp = atoi(get);
		hero.close();
		//mostrando os dados d heroi gravados no vetor
		system("cls");
		cout<<"\nHer�i selecionado = "<<heroi_ativo.nome;
		cout<<"\nAtque = "<<heroi_ativo.atk;
		cout<<"\nVida = "<<heroi_ativo.vida_max;
		cout<<"\nN�vel = "<<heroi_ativo.lv;
		cout<<"\nExperi�ncia = "<<heroi_ativo.xp;
		cout<<"\n";
		system("pause");
		luta(heroi_ativo);
	}
	else if(menu == 2){
		criar();
		main();
	}
	else{
	// teste GIT
	//	goto quit;
	}	
}
int selecionar(){
	char mostra[100];
	int cont, num_char;
	num_char = conta_char();
	fstream mostrar;
	mostrar.open("chardata.txt", ios::in);
	//posicionar o poteiro ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mostrar.getline(mostra, 3, '#');
	//la�o q mostra os boneco ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	for(cont=num_char; cont>0;cont--){
		mostrar.getline(mostra, 25, '#');
		cout<<"ID: "<<mostra;
		mostrar.getline(mostra, 25, '#');
		cout<<"\tNome: "<<mostra;
		mostrar.getline(mostra, 25, '#');
		cout<<"\tVida: "<<mostra;
		mostrar.getline(mostra, 25, '#');
		cout<<"\tAtk: "<<mostra;
		mostrar.getline(mostra, 25, '#');
		cout<<"\tLV: "<<mostra;
		mostrar.getline(mostra, 25, '#');
		cout<<"\tXP: "<<mostra;
	}
	mostrar.close();
	cout<<"\nSelecione o seu her�i: ";
	cin>>cont;
	fflush(stdin);
	system("cls");
	//cout<<"TESTE PRIMARIO DO VALOR: "<<cont;  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	return cont;

}
void criar(){
	system("cls");
	char nome[20], mostra[25];
	int num_char=-1;
	cout<<"\nInforme um nome de no m�ximo 20 caracteres para o seu personagem: ";
	gets (nome);
	//cout<<"\nTEste do NOME: "<<nome; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	fflush(stdin);
	fstream mostrar;
	mostrar.open("chardata.txt", ios::in);
	// parte q conta quantos personagesn h�: ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		while(!mostrar.fail()){
			mostrar.getline(mostra, 88);
			num_char++;
		}
	mostrar.close();
	fstream gravar;
	gravar.open("chardata.txt", ios::app | ios::out);
	gravar<<"#";
	gravar<<num_char+1;
	gravar<<"#";
	gravar<<nome;
	gravar<<"#10#1#1#0    \n";
	gravar.close();
	//cout<<"\nTEste do NOME: "<<nome; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
}
void luta(personagem heroi){
	int vida, vida_ini, menu, critico, max_xp, atributos=0;	
	vida = heroi.vida_max;
	personagem inimigo;
	inimigo.atk = 1;
	inimigo.vida_max = 5;
	vida_ini = inimigo.vida_max;
	inimigo.xp = 40;
	max_xp = pegar_xp(heroi.lv);
	//inicio da luta ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	luta:
	system("color 4d");
	system("cls");
	cout<<"###################BATALHAAAAAAAAAAAAAAAAAAAAA################\n\n\n";
	cout<<"Vida = "<<vida<<"\t\tVida = "<<vida_ini<<"\n";
	cout<<" O\t\t\t O\n/|\\\t\t\t/|\\\n/\\\t\t\t/\\\n";
	cout<<"Oque voc� far�?\n1 - Atacar!!!\t2 - Desistir como um medroso sem honra!!";
	cin>> menu;
	fflush(stdin);
	if(menu == 1){
		//-calculo do dano cr�tico e envio do dano ao inimigo ;;;;;;;;;;;;;;;;;;;;;;;
		critico = rand() % 50;
		if(critico>22){
			system("color 0a");
			cout<<"\n\n\nDANO Cr�TICO!!!\ndano recebido pelo inimigo: "<<(heroi.atk*3)<<"\n\n\n";
			vida_ini -= (heroi.atk*3);
			system("pause");
		}
		else{
			system("color 0f");
			cout<<"\n\n\nDano recebido pelo inimigo: "<<heroi.atk<<"\n\n";
			vida_ini -= heroi.atk;
			system("pause");			
		}
		//vit�ria ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		if(vida_ini<1){
			system("cls");
			cout<<"VOC� VENCEU!!!!!\n\n\nXP RECEBIDO = "<<inimigo.xp;
			system("pause");
			heroi.xp += inimigo.xp;
			//level UP ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			level_up:
			if(heroi.xp>max_xp){
				system("cls");
				heroi.xp -= max_xp;
				cout<<"\nVOC� PASSOU DE N�VEL!!!!";
				heroi.lv++;
				//adicionar atributos ao her�i
				if(heroi.lv%5 == 0){
					atributos = 3;
				}
				else{
					atributos =1;
				}
				cout<<"\nAtributos aumentados!!!\n";
				//CONTINUAR DAQUIIIIIIIII!!!!!!!!!!!!! ;;;;;;;;;;;;;;;;;;;;;;;;;
				max_xp = pegar_xp(heroi.lv);	
				cout<<"\nVOC� ALCAN�OU O N�VEL "<<heroi.lv<<"!!!";
				cout<<"\nATAQUE = "<<heroi.atk<<" + "<<atributos<<" = "<<heroi.atk+atributos;
				cout<<"\nATAQUE = "<<heroi.vida_max<<" + "<<atributos<<" = "<<heroi.vida_max+atributos;
				heroi.vida_max += atributos;
				heroi.atk += atributos;
				system("pause");
				goto level_up;
			}
			cout<<"\nSalvando o seu progresso...";
			//INSERIR O LV UP AQUI ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			salvar(heroi);
			system("pause");
			main();
		}
		system("color 0a");
		vida -= inimigo.atk;
		cout<<"\n\nDano do inimigo = "<<inimigo.atk<<"\n\n\n";
		system("pause");
		goto luta;
	}
	
	else if(menu == 2){
		
	}
	else{
		system("cls");
		cout<<"op��o inv�lida!\n\n\n\n\n";
		system("pause");
		goto luta;
	}
	system("pause");
	main();
}
int pegar_xp(int lv){
	int cont, max_xp;
	char pegar[100];
		fstream xp;
		xp.open("lv.txt", ios::in);
		//posicionar ponteiro
		for(cont=(lv-1); cont>0; cont--){
			xp.getline(pegar, 50);
			/*cout<<"\nTESTE DO LA�O "<<cont;
			cout<<"\n teste do txt!!!   "<<pegar;*/
		}
		xp.getline(pegar,50,'#');
		xp.getline(pegar,25,'#');
		xp.getline(pegar,25,'#');
		max_xp = atoi(pegar);
		xp.close();
		return max_xp;
}
void salvar(personagem heroi){
	char salvador[80];
	cout<<"\nTEste do SAVE...";
	int cont, quantos;
	quantos = conta_char();
	fstream backup1;
	backup1.open("chardata.txt", ios::out | ios::in);
	for(cont=0; cont<=heroi.id; cont++){
		backup1.getline(salvador, 80);
	}
	system("cls");
	cout<<salvador;
	system("pause");
	backup1.close();
	//CONTINUAR DAQUI ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	char pegar[100];
	cont = heroi.id-1;
	fstream salva;
	salva.open("chardata.txt", ios::out | ios::in);
	if(cont>0){
		for(cont=cont; cont>0; cont--){
			salva.getline(pegar, 100);
		}
	}
	salva<<"#";
	salva<<heroi.id;
	salva<<"#";
	salva<<heroi.nome;
	salva<<"#";
	salva<<heroi.vida_max;
	salva<<"#";
	salva<<heroi.atk;
	salva<<"#";
	salva<<heroi.lv;
	salva<<"#";
	salva<<heroi.xp;
	salva<<"   ";
	salva.close();
}
int conta_char(){
	char mostra[100];
	int num_char =-1;
	fstream mostrar;
	mostrar.open("chardata.txt", ios::in);
	// parte q conta quantos personagesn h�: ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	while(!mostrar.fail()){
		mostrar.getline(mostra, 88);
		num_char++;
	}
	cout<<"N�MERO DE PERSONAGENS: "<<num_char<<"\n";
	mostrar.close();
	//fim da contagem ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	return num_char;
}
//Projeto descontinuado :(

