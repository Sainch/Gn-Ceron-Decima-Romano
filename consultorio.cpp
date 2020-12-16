#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones_y_estructuras.h"

struct Fecha
{
	int dia;
	int mes;
	int anio;
};

struct Turno
{
	int MatriculaVeterinario;
	Fecha fecha;
	int DNI_Duenio;
	char DetalleAtencion[380];
};

struct Mascota
{
	char ApellidoyNombre[60];
	char Domicilio[60];
	int DNI_Dueno;
	char Localidad[60];
	Fecha FechadeNacimiento;
	float Peso;
	char Telefono[25];
};


//**********************************FUNCIONES***********************************

void Iniciar_Sesion(Datos_Veterinarios &VeterinarioIngresado);
int MenuPrincipalConsultorio();
void Visualizar_Lista_Espera(Datos_Veterinarios VeterinarioIngresado);

//******************************************************************************


main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 3");
	
	int bandera=1;
	char Opcion;
	Datos_Veterinarios VeterinarioIngresado;
	
	Iniciar_Sesion(VeterinarioIngresado);
	LimpiarPantalla();	
	do
	{
		Opcion=MenuPrincipalConsultorio();
		switch(Opcion)
		{
			case'a':case'A':
				LimpiarPantalla();
				Visualizar_Lista_Espera(VeterinarioIngresado);
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
				printf("SE INGREÓ UNA OPCIÓN INVÁLIDA");
				break;
		}
		
		LimpiarPantalla();
		
	}while(bandera==1);
}

void Iniciar_Sesion(Datos_Veterinarios &VeterinarioIngresado)
{
	FILE *Veterinarios;
	Datos_Veterinarios Aux;
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
	
	fread(&Aux,sizeof(Datos_Veterinarios),1,Veterinarios);
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
		fread(&Aux,sizeof(Datos_Veterinarios),1,Veterinarios);
		while(!feof(Veterinarios) && bandera==0)
		{
			if(strcmp(Usuario,Aux.Usuario)==0)//compara con los usarios del archivo
				bandera=1;
			if(bandera==0)
				fread(&Aux,sizeof(Datos_Veterinarios),1,Veterinarios);
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
			gotoxy(35,y);y++;y++;
			printf("================");
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
		VeterinarioIngresado=Aux;//Guardar datos de veterinario que está en el sistema
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

void Visualizar_Lista_Espera(Datos_Veterinarios VeterinarioIngresado)
{
	Turno Aux1;
	Mascota Aux2;
	Datos_Veterinarios Aux3;
	
	Fecha Hoy;
	Hoy.anio=2020;//Cambiar al año
	int y=1,ContTurn=0,bandera1,bandera2=0,i=0;
	
	FILE *ArchTurnos,*ArchMascotas;
	ArchTurnos=fopen("Turnos.dat","rb");
	ArchMascotas=fopen("Mascotas.dat","rb");
	
	gotoxy(15,y);y++;
	printf("Ingrese la fecha actual.");
	gotoxy(15,y);y++;
	printf("Mes:");
	scanf("%d",&Hoy.mes);
	gotoxy(15,y);y++;
	printf("Dia:");
	scanf("%d",&Hoy.dia);
	
	LimpiarPantalla();
	y=1;gotoxy(35,y);y++;
	printf("=================");
	gotoxy(35,y);y++;
	printf("LISTADO DE TURNOS");
	gotoxy(35,y);y++;y++;
	printf("=================");
	
	rewind(ArchTurnos);
	fread(&Aux1,sizeof(Turno),1,ArchTurnos);
	while(!feof(ArchTurnos))
	{
		if(Aux1.fecha.mes==Hoy.mes && Aux1.fecha.dia==Hoy.dia && VeterinarioIngresado.matricula==Aux1.MatriculaVeterinario)//dia y veterinario correspondiente
		{
			bandera2=1;//hay algun para el día?
			bandera1=0;
			fread(&Aux2,sizeof(Mascota),1,ArchMascotas);
			while(!feof(ArchMascotas) && bandera1==0)
			{
				if(Aux1.DNI_Duenio==Aux2.DNI_Dueno)
					bandera1=1;
				if(bandera1==0)
					fread(&Aux2,sizeof(Mascota),1,ArchMascotas);
			}
			gotoxy(15,y);y++;y++;
			printf("%d°:%s",i+1,Aux2.ApellidoyNombre);
			i++;
		}
		fread(&Aux1,sizeof(Turno),1,ArchTurnos);
	}
	if(bandera2==0)
	{
		gotoxy(35,y);y++;
		printf("NO TIENE TURNOS PARA EL DÍA");
		gotoxy(35,y);y++;
		printf("===========================");
	}
	
	fclose(ArchTurnos);
	fclose(ArchMascotas);
}
