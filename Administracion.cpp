#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<windows.h>
#include"funciones_y_estructuras.h"


//**********************************FUNCIONES***********************************

void Inicio_de_Sesion();
int MenuPrincipal_Administracion();

//******************************************************************************


main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 3");
	
	//*****************Datos a utilizar*************
	
	int bandera=1,contrasena;
	char Opcion;
	Datos_Veterianrios Datos;
	
	//**********************************************
	
	Inicio_de_Sesion();//inicio del módulo de administracion
	LimpiarPantalla();
	
	do
	{
		Opcion=MenuPrincipal_Administracion();
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
				break;
			case'f':case'F':
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

void Inicio_de_Sesion()
{
	palabra contrasena1,contrasena2;
	int Cont=0;
	
	FILE * Contrasena_Administracion;
	Contrasena_Administracion=fopen("Clave_Modulo_Administracion","r+b");
	fread(&contrasena1,sizeof(palabra),1,Contrasena_Administracion);
	
	if(Contrasena_Administracion==NULL || strlen(contrasena1)<6)
	{
		fclose(Contrasena_Administracion);
		Contrasena_Administracion=fopen("Clave_Modulo_Administracion","w+b");
		gotoxy(15,2);
		printf("BIENVINIDO AL MÓDULO DE ADMINISTRACIÓN");
		gotoxy(15,3);
		printf("--------------------------------------------------------------------------------------------");
		gotoxy(15,4);
		printf("COMO ES SU PRIMER INCIO LE PEDIMOS QUE INGRESE LA CONTRASEÑA DE INGRESO DE 6 A 36 CARACTERES");
		gotoxy(15,5);
		printf("--------------------------------------------------------------------------------------------");
		gotoxy(15,6);
		printf("CONTRASEÑA:");
		gets(contrasena1);
		while((strlen(contrasena1)<6 || strlen(contrasena1)>36) && Cont<3)
		{
			LimpiarPantalla();
			gotoxy(15,2);
			printf("LA CONTRSEÑA INGRESADA ES INCORRECTA");
			gotoxy(15,3);
			printf("-----------------------------------------");
			gotoxy(15,4);
			printf("POR FAVOR VUELVA A INGRESAR LA CONTRASEÑA");
			gotoxy(15,5);
			printf("-----------------------------------------");
			gotoxy(15,6);
			printf("CONTRASEÑA:");
			gets(contrasena1);
		}
		
		if(Cont==3)
		{
			LimpiarPantalla();
			gotoxy(15,2);
			printf("SE EXEDIÓ EL LÍMITE DE INTENTOS PERMITIDO!");
			gotoxy(35,4);
			printf("__________________");
			gotoxy(35,5);
			printf("*FIN DEL PROGRAMA*");
			gotoxy(35,6);
			printf("==================");
			exit(1);
		}
		
		fwrite(&contrasena1,sizeof(palabra),1,Contrasena_Administracion);
		gotoxy(15,8);
		printf("CONTRASEÑA GUARDADA CON ÉXITO!!!");
		gotoxy(15,9);
		printf("-------------------------------------------------------------------");
		gotoxy(15,10);
		printf("CADA QUE VEZ QUE INGRESE A ÉSTE MÓDULO SE LE PEDIRÁ ÉSTA CONTRASEÑA");
	}
	else
	{
		gotoxy(15,2);
		printf("BIENVENIDO DE NUEVO!");
		gotoxy(15,3);
		printf("--------------------------------");
		gotoxy(15,4);
		printf("POR FAVOR INGRESE LA CONTRASEÑA:");
		gets(contrasena2);
		while(strcmp(contrasena1,contrasena2)!=0 && Cont<3)
		{
			LimpiarPantalla();
			gotoxy(15,2);
			printf("SE INGRESÓ UNA CONTRASEÑA INCORRECTA!!");
			gotoxy(15,3);
			printf("------------------------------------------");
			gotoxy(15,4);
			printf("POR FAVOR,VUELVA A INGRESAR LA CONTRASEÑA:");
			gets(contrasena2);
			Cont++;
		}
		if(Cont==3)
		{
			LimpiarPantalla();
			gotoxy(15,2);
			printf("SE EXEDIÓ EL LÍMITE DE INTENTOS PERMITIDO!");
			gotoxy(35,4);
			printf("__________________");
			gotoxy(35,5);
			printf("*FIN DEL PROGRAMA*");
			gotoxy(35,6);
			printf("==================");
			exit(1);
		}
	}
	fclose(Contrasena_Administracion);
}

int MenuPrincipal_Administracion()
{
	char OP;
	
	gotoxy(25,1);
	printf("=========================================");
	gotoxy(37,2);
	printf("MENÚ ADMINISTRACION");
	gotoxy(25,3);
	printf("========================================="); 
	gotoxy(25,4);
	printf("a._Registrar Veterinario");
	gotoxy(25,5);
	printf("b._Registrar Asistente");
	gotoxy(25,6);
	printf("c._Atenciones por Veterinarios");
	gotoxy(25,7);
	printf("d._Ranking de Veterinarios por Atenciones");
	gotoxy(25,8);
	printf("e._Mostrar Asistentes");
	gotoxy(25,10);
	printf("f._Cerrar Aplicación");
	gotoxy(25,12);
	printf("Ingrese una opción:");
	_flushall();
	scanf("%c",&OP);
	return OP;
}
