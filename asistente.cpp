#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones.h"

//**********************************FUNCIONES***********************************

int MenuPrincipalAsistente();

//******************************************************************************


main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 2");
	
	int bandera=1;
	char Opcion;
	
	do
	{
		Opcion=MenuPrincipalAsistente();
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
				printf("================================================"); 
				gotoxy(25,15);
				printf("ERROR!!");
				gotoxy(25,16);
				printf("NO SE INGRESÓ UN OPCIÓN VÁLIDA");
				break;
		}
		
		LimpiarPantalla();
		
	}while(bandera==1);
}

int MenuPrincipalAsistente()
{
	char OP;
	
	gotoxy(25,1);
	printf("================================================"); 
	gotoxy(43,2);
	printf("MENÚ ASISTENTE");
	gotoxy(25,3);
	printf("================================================"); 
	gotoxy(25,4);
	printf("a._Iniciar Sesión");
	gotoxy(25,5);
	printf("b._Registrar mascota");
	gotoxy(25,6);
	printf("c._Registrar Turno");
	gotoxy(25,7);
	printf("d._Listado de Atenciones por Veterinario y Fecha");
	gotoxy(25,9);
	printf("e._Cerrar Aplicación");
	gotoxy(25,11);
	printf("Ingrese una opción:");
	_flushall();
	scanf("%c",&OP);
	return OP;
}
