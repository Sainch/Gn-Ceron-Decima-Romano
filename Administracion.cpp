#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones.h"


//**********************************FUNCIONES***********************************

int MenuPrincipalAdministracion();

//******************************************************************************


main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 3");
	
	int bandera=1;
	char Opcion;
	
	do
	{
		Opcion=MenuPrincipalAdministracion();
		switch(Opcion)
		{
			case'a':case'A':
				break;
			case'b':case'B':
				break;
			case'c':case'C':
				break;
			case'd':case'D':
				break;
			case'e':case'E':
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
				printf("=========================================");
				gotoxy(25,15);
				printf("ERROR!!");
				gotoxy(25,16);
				printf("NO SE INGRESÓ UN OPCIÓN VÁLIDA");
				break;
		}
		LimpiarPantalla();
		
	}while(bandera==1);
}

int MenuPrincipalAdministracion()
{
	char OP;
	
	gotoxy(25,1);
	printf("=========================================");
	gotoxy(36,2);
	printf("MENÚ ADMINISTRACION");
	gotoxy(25,3);
	printf("========================================="); 
	gotoxy(25,4);
	printf("a._Registrar Veterinario");
	gotoxy(25,5);
	printf("b._Registrar Mascota");
	gotoxy(25,6);
	printf("c._Atenciones por Veterinarios");
	gotoxy(25,7);
	printf("d._Ranking de Veterinarios por Atenciones");
	gotoxy(25,9);
	printf("e._Cerrar Aplicación");
	gotoxy(25,11);
	printf("Ingrese una opción:");
	_flushall();
	scanf("%c",&OP);
	return OP;
}
