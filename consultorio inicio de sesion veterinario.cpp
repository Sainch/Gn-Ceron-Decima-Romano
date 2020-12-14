#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones_y_estructuras.h"
#include <conio.h> 
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#define ENTER 13 
#define BACKSPACE 8


//**********************************FUNCIONES***********************************

int MenuPrincipalConsultorio();

//******************************************************************************
using namespace std;
void inicioveterinario();

 main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 3");
	
	int bandera=1;
	char Opcion;
	
	do
	{
		Opcion=MenuPrincipalConsultorio();
		switch(Opcion)
		{
			case'a':case'A':
				system("cls");
				inicioveterinario();
				break;
			case'b':case'B':
				break;
			case'c':case'C':
				break;
			case'd':case'D':
				bandera=0;
				LimpiarPantalla();
				gotoxy(35,2);
				printf("__________________");
				gotoxy(35,3);
				printf("*FIN DEL PROGRAMA*");
				gotoxy(35,4);
				printf("==================");
				break;
			default:
				gotoxy(25,14);
				printf("=======================================");
				gotoxy(25,15);
				printf("ERROR!!");
				gotoxy(25,16);
				printf("NO SE INGRESÓ UN OPCIÓN VÁLIDA");
				break;
		}
		
		LimpiarPantalla();
		
	}while(bandera==1);
}

int MenuPrincipalConsultorio()
{
	char OP;
	
	gotoxy(25,1);
	printf("=======================================");
	gotoxy(37,2);
	printf("MENÚ CONSULTORIO");
	gotoxy(25,3);
	printf("======================================="); 
	gotoxy(25,4);
	printf("a._Iniciar Sesión");
	gotoxy(25,5);
	printf("b._Visualizar Lista de Espera de Turnos");
	gotoxy(25,6);
	printf("c._Registrar Evolución de la Mascotas");
	gotoxy(25,8);
	printf("d._Cerrar Aplicación");
	gotoxy(25,10);
	printf("Ingrese una opción:");
	_flushall();
	scanf("%c",&OP);
	return OP;
}
void inicioveterinario(){
 vector<string> usuarios;		//ingreso de usuario y contraseña 
	vector<string> claves;
	
	// Se añaden usuarios al vector
	usuarios.push_back("admin");

	// Se añaden claves al vector
	claves.push_back("admin");
	
	string usuario, password;
	
	int contador = 0;
	bool ingresa = false;
	
	do {
		system("cls");
		printf ( "\n ----------------------------" );
		printf ( "\t\t\tLOGIN DE VETERINARIO" );
		printf ( "\n ----------------------------" );
		printf ( "\n\tUsuario: ");
		getline(cin, usuario);
		
		char caracter;
		
		cout << "\tPassword: ";
		caracter = getch();
		
		password = "";
		
		while (caracter != ENTER) {
		
			if (caracter != BACKSPACE) {
				password.push_back(caracter);
				printf ( "*");
				
			} else {
				if (password.length() > 0) {
					printf ( "\b \b");
					password = password.substr(0, password.length() - 1);
				}
			}
			
			caracter = getch();
		}
		
		for (int i = 0; i < usuarios.size(); i++) {
			if (usuarios[i] == usuario && claves[i] == password) {
				ingresa = true;
				break;
			}
		}
		
		if (!ingresa) {
			printf ("\n\n\tEl usuario y/o password son incorrectos" );
			cin.get();
			contador++;
		}
		
	} while (ingresa == false && contador < 3);
	
	if (ingresa == false) {
		printf ("\n\tUsted no pudo ingresar al sistema. ADIOS" );
		exit(1);
	} else {
		printf( "\n\n\tBienvenido al sistema" );
	}

	cin.get();



}
