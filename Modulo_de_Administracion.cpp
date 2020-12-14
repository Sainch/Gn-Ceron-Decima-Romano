#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#define ENTER 13 
#define BACKSPACE 8

struct datos{
	char apellidonombre[60];
	int dni;
	int matricula;
	char telefono[25];
};
typedef struct datos DATO;


char menu();
void insertarveterinario();
void mostrarveterinario();

using namespace std;

int main(void){
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
		printf ( "\t\t\tLOGIN DE USUARIO" );
		printf ( "\n\t\t\t----------------" );
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
	
	
	
	
	char op;                     //inicio del sistema
	do{
		op = menu();
		switch(op){
			case '1':
				system("cls");
				insertarveterinario();
			break;
			case '2':
				system("cls");
				
			break;
			case '3':
				system("cls");
				
			break;
			case '4':
				system("cls");
				mostrarveterinario();
			break;
			case '5':
				system("cls");
				
			break;
		}
	}while(op!='6');
	return 0;
}
char menu(){
	char op;
	system("cls");
		printf("\n MOFULO DE ADMINISTRACION");
		printf("\n (1) Registrar Veterinario: ");
		printf("\n (2) Registrar Usuario Asistente: ");
		printf("\n (3) Atencion por Veterinario: ");
		printf("\n (4) Mostrar registros de veterinarios: ");
		printf("\n (5) Ranking de Veterinario por Atenciones: ");
		printf("\n (6) cerrar la aplicacion.");
		printf("\n Opcion --->"); fflush(stdin);
		op = getch();
		return op;
}

void insertarveterinario(){	
	FILE *fich;
	DATO e;
	
	if((fich = fopen("Registro","ab"))==NULL){
		printf("\nNo se cargo ningun registro! ");
	}else{
		
		printf("\n Ingrese Apelldio y Nombre: "); fflush(stdin);
		gets(e.apellidonombre);
		printf(" Ingrese DNI: "); fflush(stdin);
		scanf("%i",&e.dni);
		printf(" Ingrese Matricula: "); fflush(stdin);
		scanf("%i",&e.matricula);
		printf(" Ingrese Telefono: "); fflush(stdin);
		gets(e.telefono);
		
		fwrite(&e,sizeof(e),1,fich);	// Escribe todo lo que tenemos en la estructura en el fichero . . . .. . 
		fclose(fich);	//Cierra el fichero para que no quede abierto . . . . .
	}
}

void mostrarveterinario(){
	FILE *fich;
	DATO e;
	
	if((fich = fopen("Registro","rb")) == NULL){
		printf("\n No se cargo ningun registro ");
	}else{
		
		fread(&e,sizeof(e),1,fich);	// Lee los registros del Fichero Posicion por posicion . . . .
		while(! feof(fich)){	// Recorriendo el Fichero . . . .
			printf("\n ____________________________");
			printf("\n Apellido y Nombre......: %s",e.apellidonombre);
			printf("\n Dni........: %i",e.dni);
			printf("\n Matricula........: %i",e.matricula);
			printf("\n Telefono......: %s",e.telefono);
			printf("\n ____________________________");
			fread(&e,sizeof(e),1,fich);
		}
	}
	fclose(fich);
	getch();
}
