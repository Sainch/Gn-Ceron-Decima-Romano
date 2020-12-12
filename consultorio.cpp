#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones.h"


//**********************************FUNCIONES***********************************

int MenuPrincipalConsultorio();

//******************************************************************************


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
