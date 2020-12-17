#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones_y_estructuras.h"

//**********************************FUNCIONES***********************************

void Iniciar_Sesion(Datos_Veterinarios &VeterinarioIngresado);
int MenuPrincipalConsultorio();
void Visualizar_Lista_Espera(Turno VecTurnos[100], Mascota VecMascotas[100], int CantTurno, int CantMascoas, Datos_Veterinarios VeterinarioIngresado , Fecha Hoy);
void Registrar_Evolucion(Turno VecTurnos[100], Mascota VecMascotas[100], int CantTurno, int CantMascoas, Datos_Veterinarios VeterinarioIngresado , Fecha Hoy);
void CargarVectores(Turno VecTurnos[100], Mascota VecMascotas[100], int &CantTurno, int &CantMascotas);
void Guardar_Datos_Turnos(Turno VecTurnos[100], int CantTurno);

//******************************************************************************


main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 3");
	
	int bandera1=1,bandera2=0,y=1,CantTurnos,CantMascotas;
	char Opcion;
	Datos_Veterinarios VeterinarioIngresado;
	Fecha Hoy;
	Turno VecTurnos[100];
	Mascota VecMascotas[100];
	
	Iniciar_Sesion(VeterinarioIngresado);
	LimpiarPantalla();
	CargarVectores(VecTurnos,VecMascotas,CantTurnos,CantMascotas);//Cargar los datos en vectores para facilitar su manipulacion
	gotoxy(15,y);y++;
	printf("Ingrese la fecha actual.");//fecha de referencia para el programa
	gotoxy(15,y);y++;
	printf("Mes:");
	scanf("%d",&Hoy.mes);
	gotoxy(15,y);y++;
	printf("Dia:");
	scanf("%d",&Hoy.dia);
	LimpiarPantalla();
	do
	{
		Opcion=MenuPrincipalConsultorio();
		switch(Opcion)
		{
			case'a':case'A':
				LimpiarPantalla();
				Visualizar_Lista_Espera(VecTurnos,VecMascotas,CantTurnos,CantMascotas,VeterinarioIngresado,Hoy);
				bandera2=1;
				break;
			case'b':case'B':
				if(bandera2==1)
				{
					LimpiarPantalla();
					Registrar_Evolucion(VecTurnos,VecMascotas,CantTurnos,CantMascotas,VeterinarioIngresado,Hoy);	
				}
				else
				{
					gotoxy(15,11);
					printf("==========================================");
					gotoxy(15,12);
					printf("DEBE INGRESAR PRIMERO AL LISTADO DE TURNOS");
					gotoxy(15,13);
					printf("==========================================");
				}
				break;
			case'c':case'C':
				bandera1=0;
				LimpiarPantalla();
				Guardar_Datos_Turnos(VecTurnos,CantTurnos);
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
		
	}while(bandera1==1);
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

void Visualizar_Lista_Espera(Turno VecTurnos[100], Mascota VecMascotas[100], int CantTurno, int CantMascotas, Datos_Veterinarios VeterinarioIngresado , Fecha Hoy)
{
	int i,j=0,k=0,bandera1=0,bandera2=0;
	int y=1;
	
	gotoxy(35,y);y++;
	printf("=================");
	gotoxy(35,y);y++;
	printf("LISTADA DE ESPERA");
	gotoxy(35,y);y++;y++;
	printf("=================");
	
	for(i=0;i<CantTurno;i++)
	{
		//comparar si la fecha es correcta, la matricula del veterinario es la del veterinario que incio sesión y el campo DetalleAtencion está vacio
		if(VecTurnos[i].fecha.dia==Hoy.dia && VecTurnos[i].fecha.mes==Hoy.mes && VeterinarioIngresado.matricula==VecTurnos[i].MatriculaVeterinario && strcmp(VecTurnos[i].DetalleAtencion,"")==0)
		{
			bandera1=0;
			bandera2=1;
			for(j=0;j<CantMascotas && bandera1==0;j++)//busca la mascota para mostrar el nombre
			{
				if(VecTurnos[i].DNI_Duenio==VecMascotas[j].DNI_Dueno)
				{
					bandera1=1;
					j--;
				}
			}
			gotoxy(15,y);y++;y++;
			printf("%d°.%s",k+1,VecMascotas[j].ApellidoyNombre);
			k++;
		}
	}
	if(bandera2==0)
	{
		gotoxy(35,y);y++;
		printf("NO HAY TURNOS DE PACIENTES");
		gotoxy(35,y);y++;
		printf("==========================");
		return ;
	}
	gotoxy(15,y);y++;
	printf("===================================================================================");
	gotoxy(15,y);y++;
	printf("ATENCIÓN! EL INGRESO DEL DETALLE DE LA CONSULTA SE REALIZARÁ EN EL RESPECTIVO ORDEN");
	gotoxy(15,y);
	printf("===================================================================================");
}

void Registrar_Evolucion(Turno VecTurnos[100], Mascota VecMascotas[100], int CantTurno, int CantMascotas, Datos_Veterinarios VeterinarioIngresado , Fecha Hoy)
{
	int i,j=0,bandera1=0,bandera2=0;
	int y=1;
	
	gotoxy(35,y);y++;
	printf("===========================");
	gotoxy(35,y);y++;
	printf("INGRESO DETALLE DE ATENCIÓN");
	gotoxy(35,y);y++;y++;
	printf("===========================");
	
	
	for(i=0;i<CantTurno && bandera2==0;i++)
	{
		//Verificar si el turno  corresponde al dia, ademas si la matricula del veterinario es la correspondiente, y además, si todavia no se escribio el detalle
		if(VecTurnos[i].fecha.dia==Hoy.dia && VecTurnos[i].fecha.mes==Hoy.mes && VeterinarioIngresado.matricula==VecTurnos[i].MatriculaVeterinario && strcmp(VecTurnos[i].DetalleAtencion,"")==0)
		{
			bandera1=0;
			bandera2=1;
			for(j=0;j<CantMascotas && bandera1==0;j++)
			{
				if(VecTurnos[i].DNI_Duenio==VecMascotas[j].DNI_Dueno)
				{
					bandera1=1;
					j--;
				}
			}
			gotoxy(15,y);y++;y++;
			printf("*%s",VecMascotas[j].ApellidoyNombre);
			gotoxy(15,y);y++;
			printf("Ingrese el detalle de la Atención:");
			_flushall();
			gets(VecTurnos[i].DetalleAtencion);
		}
	}
	if(bandera2==0)
	{
		gotoxy(35,y);y++;
		printf("NO HAY TURNOS DE PACIENTES");
		gotoxy(35,y);y++;
		printf("==========================");
	}
}

void CargarVectores(Turno VecTurnos[100], Mascota VecMascotas[100], int &CantTurno, int &CantMascotas)
{
	Turno Aux1;
	Mascota Aux2;
	int i=0;
	FILE *ArchTurnos,*ArchMascotas;
	
	ArchTurnos=fopen("Turnos.dat","r+b");
	ArchMascotas=fopen("Mascotas.dat","a+b");
	
	fread(&Aux1,sizeof(Turno),1,ArchTurnos);
	while(!feof(ArchTurnos))
	{
		VecTurnos[i]=Aux1;
		i++;
		fread(&Aux1,sizeof(Turno),1,ArchTurnos);
	}
	CantTurno=i;
	i=0;
	fread(&Aux2,sizeof(Mascota),1,ArchMascotas);
	while(!feof(ArchMascotas))
	{
		VecMascotas[i]=Aux2;
		i++;
		fread(&Aux2,sizeof(Mascota),1,ArchMascotas);
	}
	CantMascotas=i;
	fclose(ArchTurnos);
	fclose(ArchMascotas);
}

void Guardar_Datos_Turnos(Turno VecTurnos[100], int CantTurno)
{
	int i;
	Turno Aux1;
	
	FILE *ArchTurnos;
	ArchTurnos=fopen("Turnos.dat","w+b");
	
	for(i=0;i<CantTurno;i++)
	{
		Aux1=VecTurnos[i];
		fwrite(&Aux1,sizeof(Turno),1,ArchTurnos);
	}
	fclose(ArchTurnos);
}
