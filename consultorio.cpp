#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones_y_estructuras.h"


//**********************************FUNCIONES***********************************

void Iniciar_Sesion();
int MenuPrincipalConsultorio();

//******************************************************************************


main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 3");
	
	int bandera=1;
	char Opcion;
	
	Iniciar_Sesion();
	LimpiarPantalla();	
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

void Iniciar_Sesion()
{
	FILE *Veterinarios;
	Datos_Veterianrios Aux;
	int y=1;
	char Usuario[11],Contrasena[33],bandera,ContInt=0;
	
	gotoxy(35,y);y++;
	printf("================");
	gotoxy(35,y);y++;
	printf("INICIO DE SESIÓN");
	gotoxy(35,y);y++;
	printf("================");
	y++;
	
	Veterinarios=fopen("Veterinarios.dat","rb");
	
	fread(&Aux,sizeof(Datos_Veterianrios),1,Veterinarios);
	if(Veterinarios==NULL || strcmp(Aux.ApellidoNombre,"")==0)
	{
		gotoxy(35,y);y++;
		printf("===========================");
		gotoxy(35,y);y++;
		printf("ERROR!!");
		gotoxy(35,y);y++;
		printf("NO HAY USUARIOS REGISTRADOS");
		gotoxy(35,y);
		printf("===========================");
		exit(1);
	}
	gotoxy(25,y);y++;
	printf("Ingrese el usuario:");
	gets(Usuario);
	gotoxy(25,y);y++;
	printf("Ingrese la contraseña:");
	gets(Contrasena);
	
	do
	{
		bandera=0;ContInt++;
		rewind(Veterinarios);
		fread(&Aux,sizeof(Datos_Veterianrios),1,Veterinarios);
		while(!feof(Veterinarios) && bandera==0)
		{
			if(strcmp(Usuario,Aux.Usuario)==0)//compara con los usarios del archivo
				bandera=1;
			if(bandera==0)
				fread(&Aux,sizeof(Datos_Veterianrios),1,Veterinarios);
		}
		if(bandera==1)//si encontró el usuario
		{
			if(strcmp(Contrasena,Aux.Contrasena)!=0)
				bandera=0;
		}
		if(bandera==0 && ContInt!=3)//se ingresó mal la contraseña o  usuario
		{
			LimpiarPantalla();
			y=1;gotoxy(35,y);y++;
			printf("================");
			gotoxy(35,y);y++;
			printf("INICIO DE SESIÓN");
			gotoxy(35,y);y++;
			printf("================");
			y++;
			gotoxy(25,y);y++;
			printf("ERROR! Se ingresó usuario o contraseña incorrecta.");
			gotoxy(25,y);y++;
			printf("--------------------------------------------------");
			gotoxy(25,y);y++;
			printf("Por favor ingrese nuevamente usuario y contraseña.");
			gotoxy(25,y);y++;
			printf("--------------------------------------------------");
			gotoxy(25,y);y++;
			printf("Ingrese el usuario:");
			gets(Usuario);
			gotoxy(25,y);y++;
			printf("Ingrese la contraseña:");
			gets(Contrasena);
		}
	}while(bandera==0 && ContInt!=3);
	if(ContInt==3 && bandera==0)
	{
		LimpiarPantalla();
		y=1;gotoxy(35,y);y++;
		printf("===========================================");
		gotoxy(35,y);y++;
		printf("SE EXEDIÓ DEL NÚMERO DE INTENTOS PERMITIDOS");
		gotoxy(35,y);y++;
		printf("===========================================");
		exit(1);
	}
	else
	{
		LimpiarPantalla();
		strupr(Aux.ApellidoNombre);
		y=1;gotoxy(35,y);y++;
		printf("========================================");
		gotoxy(35,y);y++;
		printf("BIENVENIDO %s!!",Aux.ApellidoNombre);
		gotoxy(35,y);y++;
		printf("========================================");
	}
	fclose(Veterinarios);
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
	printf("a._Visualizar Lista de Espera de Turnos.");
	gotoxy(25,5);
	printf("b._Registrar Evolución de la Mascotas.");
	gotoxy(25,7);
	printf("c._Cerrar Aplicación.");
	gotoxy(25,9);
	printf("Ingrese una opción:");
	_flushall();
	scanf("%c",&OP);
	return OP;
}
