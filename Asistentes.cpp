#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include"funciones_y_estructuras.h"


void Inicio_de_Sesion();
int MenuPrincipalAsistente();
void registrarMascotas(FILE *Mascotas);
void registrarTurnos(FILE *Turnos,FILE *Mascotas);
void listarMascotas(FILE *Mascotas);
void ObtenerInforme(FILE *Turnos);

main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 4");
	
	Inicio_de_Sesion(); //Inicio del módulo de asistente
	LimpiarPantalla();

	FILE *ArchMascotas;
	ArchMascotas = fopen("Mascotas.dat","rb"); 
	fclose(ArchMascotas);
	if(ArchMascotas == NULL) // Evalua si hubo error.
	{
		ArchMascotas = fopen("Mascotas.dat","w+b");
	}
	ArchMascotas = fopen("Mascotas.dat","a+b");
	
	FILE *ArchTurnos; 
	ArchTurnos = fopen("Turnos.dat","rb"); 
	fclose(ArchTurnos);
	if(ArchTurnos == NULL) // Evalua si hubo error.
	{
		ArchTurnos = fopen("Turnos.dat","w+b");
	}
	ArchTurnos = fopen("Turnos.dat","a+b");
	
	int Opcion = MenuPrincipalAsistente(); //Llama la función que muestra el menú.

	do
	{
		switch(Opcion)
		{
			case 1:
				LimpiarPantalla();
				registrarMascotas(ArchMascotas);
				LimpiarPantalla();
				Opcion = MenuPrincipalAsistente();
				break;
			case 2:
				LimpiarPantalla();
				registrarTurnos(ArchTurnos,ArchMascotas);
				LimpiarPantalla();
				Opcion = MenuPrincipalAsistente();
				break;
			case 3:
				LimpiarPantalla();
				ObtenerInforme(ArchTurnos);
				LimpiarPantalla();
				Opcion = MenuPrincipalAsistente();
				break;
			case 4:
				LimpiarPantalla();
				listarMascotas(ArchMascotas);
				LimpiarPantalla();
				Opcion = MenuPrincipalAsistente();
				break;
			case 5:
				LimpiarPantalla();
				printf("Fin del Programa");
				fclose(ArchMascotas);
				fclose(ArchTurnos);
				break;
			default:
				printf("Ha ingresado una opcion no valida");
				LimpiarPantalla();
				Opcion = MenuPrincipalAsistente();
				break;
		}
	}while(Opcion != 5);
}
void Inicio_de_Sesion()
{
	char usuario[11],contrasena[32];
	int bandera;
	Datos_Usuarios_Asistentes reg;
	
	FILE *Usuario_Asistente;
	Usuario_Asistente=fopen("Usuarios_Asistentes.dat","rb");
	
	gotoxy(50,2);
	printf("INICIAR SESIÓN");
	gotoxy(45,3);
	printf("=========================");
	gotoxy(45,4);
	printf("Usuario: "); 
	gets(usuario);
	gotoxy(45,5);
	printf("Contraseña: "); 
	gets(contrasena);
	
	do
	{
		bandera=0;
		rewind(Usuario_Asistente);
		fread(&reg,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
		
		while(!feof(Usuario_Asistente) && bandera==0) //compara con usuario del archivo
		{
			if (strcmp(usuario,reg.Usuario)==0)
			{
				bandera=1; //si lo encuentra sale
			}
			if (bandera==0)
			{
				fread(&reg,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
			}
		}
		if (bandera==1) //si ingresa bien el usuario
		{
			if (strcmp(contrasena,reg.Contrasena)!=0) //si ingresa mal la contraseña
			{
				bandera=0;
			}
		}
		if (bandera==0)
		{
			gotoxy(45,7);
			printf("Usuario y contraseña incorrectos");
			LimpiarPantalla();
			gotoxy(50,2);
			printf("INICIAR SESIÓN");
			gotoxy(45,3);
			printf("=========================");
			gotoxy(45,4);
			printf("Usuario: "); 
			gets(usuario);
			gotoxy(45,5);
			printf("Contraseña: "); 
			gets(contrasena);
		}
	}while(bandera==0); //sale si se ingresa usuario y contraeña correctos
	
	fclose(Usuario_Asistente);
}
int MenuPrincipalAsistente()
{
	int Opcion;
	
	gotoxy(45,2);
	printf("BIENVENIDO AL MÓDULO DEL ASISTENTE");
	gotoxy(45,3);
	printf("==================================="); 
	gotoxy(45,4);
	printf("1.- Registrar Mascota");
	gotoxy(45,5);
	printf("2.- Registrar Turno");
	gotoxy(45,6);
	printf("3.- Listado de Atenciones por Veterinario y Fecha");
	gotoxy(45,7);
	printf("4.- Mostrar mascotas registradas");
	gotoxy(45,8);
	printf("5.- Cerrar la aplicación");
	gotoxy(45,10);
	printf("Ingrese una opción: ");
	_flushall();
	scanf("%d",&Opcion);
	return Opcion;
}
void registrarMascotas(FILE *Mascotas)
{
	Mascota reg; //crea la variable "reg" de tipo Mascota.
	int continua;

	do
	{
		gotoxy(52,2);
		printf("REGISTRO DE MASCOTA");
		gotoxy(45,3);
		printf("==================================="); 
		_flushall();
		gotoxy(45,4);
		printf("Apellido y Nombre: ");
		gets(reg.ApellidoyNombre);
		strupr(reg.ApellidoyNombre);
		gotoxy(45,5);
		printf("Domicilio: ");
		gets(reg.Domicilio);
		strupr(reg.Domicilio);
		gotoxy(45,6);
		printf("DNI del Dueño: ");
		scanf("%d",&reg.DNI_Dueno);
		_flushall();
		gotoxy(45,7);
		printf("Localidad: ");
		gets(reg.Localidad);
		strupr(reg.Localidad);
		gotoxy(45,8);
		printf("Fecha de Nacimiento: ");
		gotoxy(45,9);
		printf("Dia: ");
		scanf("%d",&reg.FechadeNacimiento.dia);
		gotoxy(45,10);
		printf("Mes: ");
		scanf("%d",&reg.FechadeNacimiento.mes);
		gotoxy(45,11);
		printf("Anio: ");
		scanf("%d",&reg.FechadeNacimiento.anio);
		gotoxy(45,12);
		printf("Peso(kg): ");
		scanf("%f",&reg.Peso);
		_flushall();
		gotoxy(45,13);
		printf("Telefono: ");
		gets(reg.Telefono);
		fwrite(&reg, sizeof(Mascota), 1, Mascotas); //Graba el registro lógico.
		_flushall();
		gotoxy(42,15);
		printf("¿Aun desea registrar mascotas SI(1) / NO(0): ");
		scanf("%d", &continua);
		LimpiarPantalla();
	}while(continua == 1);
}
void registrarTurnos(FILE *Turnos, FILE *Mascotas)
{
	int bandera,continua,y=11;
	
	Turno regi;
	FILE *ArchTurnos;
	ArchTurnos=fopen("Turnos.dat","a+b");
	
	Mascota reg;
	FILE *ArchMascotas;
	ArchMascotas=fopen("Mascotas.dat","a+b");
	
	Datos_Veterinarios vet;
	FILE *Veterinarios;
	Veterinarios=fopen("Veterinarios.dat","rb");
	
	do
	{
		gotoxy(55,2);
		printf("REGISTRO DE TURNO");
		gotoxy(45,3);
		printf("==================================="); 
		gotoxy(45,4);
		printf("Ingrese Nro de DNI del dueño: ");
		scanf("%d", &regi.DNI_Duenio);
		
		bandera=0;
		rewind(Mascotas);
		fread(&reg,sizeof(Mascota),1,Mascotas);
		
		while(!feof(Mascotas) && bandera==0) //compara con usuario del archivo
		{
			if (regi.DNI_Duenio==reg.DNI_Dueno)
			{
				bandera=1; //si lo encuentra sale
			}
			if (bandera==0)
			{
				fread(&reg,sizeof(Mascota),1,Mascotas);
			}
		}
		if (bandera==1) //si ingresa bien el dni, muestra la lista de veterinarios, y se pide asignar dia del turno
		{
			gotoxy(50,6);
			printf("Asignar Turno a: %s",reg.ApellidoyNombre);
			
			gotoxy(54,8);
			printf("LISTA DE VETERINARIOS");
			gotoxy(46,9);
			printf("*********************************");
			gotoxy(45,10);
			printf("Apellido y Nombre");
			gotoxy(75,10);
			printf("Matricula");
			rewind(Veterinarios); //Ubica el puntero en el primer registro del archivo.
			fread(&vet, sizeof(Datos_Veterinarios), 1, Veterinarios); //Leer el primer registro.
			
			if (feof(Veterinarios))
			{
				gotoxy(43,2);
				printf("El Archivo esta vacio no se Registró Información.");
			}
			else
			{
				while(!feof(Veterinarios)) //Repite hasta el último registro.
				{
					gotoxy(45,y);
					printf("%s ", vet.ApellidoNombre);
					gotoxy(75,y);
					printf("%d ", vet.matricula);
					fread(&vet, sizeof(Datos_Veterinarios), 1, Veterinarios); //Continua leyendo.
					y++;
				}
			}
			gotoxy(45,15);
			printf("Ingrese una matricula: ");//ELEGIR UN VETERINARIO
			scanf("%d", &regi.MatriculaVeterinario);
			gotoxy(45,16);
			printf("Ingrese Fecha del Turno: ");
			gotoxy(45,17);
			printf("Dia: ");
			scanf("%d",&regi.fecha.dia);
			gotoxy(45,18);
			printf("Mes: ");
			scanf("%d",&regi.fecha.mes);
			gotoxy(45,19);
			printf("Anio: ");
			scanf("%d",&regi.fecha.anio);
			fwrite(&regi,sizeof(Turno),1,ArchTurnos); //Graba el registro lógico.
		}
		if (bandera==0)
		{
			gotoxy(45,6);
			printf("El DNI ingresado no existe");
			LimpiarPantalla();
		}
		gotoxy(45,23);
		printf("¿Aun desea registrar turnos? SI(1) / NO(0): ");
		scanf("%d", &continua);
		LimpiarPantalla();
	}while(continua == 1 );

	fclose(Veterinarios);
}
void listarMascotas(FILE *Mascotas)
{
	Mascota reg;
	gotoxy(46,2);
	printf("LISTADO DE MASCOTAS REGISTRADAS");
	gotoxy(46,3);
	printf("==================================="); 
	gotoxy(0,4);
	printf("Apellido y Nombre");
	gotoxy(24,4);
	printf("Domicilio");
	gotoxy(39,4);
	printf("DNI del Dueño");
	gotoxy(59,4);
	printf("Localidad");
	gotoxy(74,4);
	printf("Fecha de Nacimiento");
	gotoxy(99,4);
	printf("Peso");
	gotoxy(109,4);
	printf("Telefono");
	rewind(Mascotas); //Ubica el puntero en el primer registro del archivo.
	fread(&reg, sizeof(Mascota), 1, Mascotas); //Leer el primer registro.
	
	int y=5;
	
	if (feof(Mascotas))
	{
		gotoxy(42,3);
		printf("El Archivo esta vacio No se Registro Informacion.");
	}
	else
	{
		while(!feof(Mascotas)) //Repite hasta el último registro.
		{
			gotoxy(0,y);
			printf("%s ", reg.ApellidoyNombre);
			gotoxy(24,y);
			printf("%s ", reg.Domicilio);
			gotoxy(39,y);
			printf("%d ", reg.DNI_Dueno);
			gotoxy(59,y);
			printf("%s ", reg.Localidad);
			gotoxy(74,y);
			printf("%d/%d/%d ", reg.FechadeNacimiento.dia, reg.FechadeNacimiento.mes, reg.FechadeNacimiento.anio);
			gotoxy(99,y);
			printf("%.1f Kg", reg.Peso);
			gotoxy(109,y);
			printf("%s ", reg.Telefono);
			fread(&reg, sizeof(Mascota), 1, Mascotas); //Continua leyendo.
			y++;
		}
	}
}
void ObtenerInforme(FILE *Turnos)
{
	int y=5;
	Turno regi;
	gotoxy(40,2);
	printf("INFORME DE ATENCIONES POR VETERINARIO Y FECHA");
	gotoxy(40,3);
	printf("============================================="); 
	gotoxy(20,4);
	printf("Matricula Veterinario");
	gotoxy(50,4);
	printf("Fecha de Atencion");
	gotoxy(75,4);
	printf("DNI del dueño del Paciente");

	rewind(Turnos); //Ubica el puntero en el primer registro del archivo.
	fread(&regi, sizeof(Turno), 1, Turnos); //Leer el primer registro.
	
	if (feof(Turnos))
	{
		gotoxy(42,3);
		printf("El Archivo esta vacio no se Registro Informacion.");
	}
	else
	{
		while(!feof(Turnos)) //Repite hasta el último registro.
		{
			gotoxy(20,y);
			printf("%d ",regi.MatriculaVeterinario);
			gotoxy(50,y);
			printf("%d/%d/%d ",regi.fecha.dia,regi.fecha.mes,regi.fecha.anio);
			gotoxy(75,y);
			printf("%d ",regi.DNI_Duenio);
			fread(&regi, sizeof(Turno), 1, Turnos); //Continua leyendo.
			y++;
		}
	}
}
