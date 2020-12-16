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
struct Turno
{
	int MatriculaVeterinario;
	Fecha fecha;
	int DNI_Duenio;
	char DetalleAtencion[380];
};

void Inicio_de_Sesion();
int MenuPrincipalAsistente();
void registrarMascotas(FILE *Mascotas);
void mensaje(char const *cadena);
void registrarTurnos(FILE *Turnos,FILE *Mascotas);
void listarMascotas(FILE *Mascotas);

main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 4");
	
	Inicio_de_Sesion(); //Inicio del módulo de asistente
	LimpiarPantalla();
	
	FILE *ArchMascotas; //Se abre de lectura para conservar
	ArchMascotas = fopen("Mascotas.dat","w+b"); //los anteriores registros.
	
	if(ArchMascotas == NULL) // Evalua, Si hubo error, muestra mensaje y termina.
	{
		system("CLS");
		printf("Ocurrio un error en la apertura del Archivo....");
		exit(1);
	}
	
	FILE *ArchTurnos; //Se abre de lectura para conservar
	ArchTurnos = fopen("Turnos.dat","w+b"); //los anteriores registros.
	
	if(ArchTurnos == NULL) // Evalua, Si hubo error, muestra mensaje y termina.
	{
		system("CLS");
		printf("Ocurrio un error en la apertura del Archivo....");
		exit(1);
	}
	
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
				
				break;
			case 4:
				LimpiarPantalla();
				listarMascotas(ArchMascotas);
				LimpiarPantalla();
				Opcion = MenuPrincipalAsistente();
			case 5:
				LimpiarPantalla();
				printf("Fin del Programa");
				break;
			default:
				printf("Ha ingresado una opcion no valida");
				LimpiarPantalla();
				Opcion = MenuPrincipalAsistente();
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
	
	printf("Usuario: "); gets(usuario);
	printf("Contraseña: "); gets(contrasena);
	
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
			printf("Usuario y contraseña incorrectos");
			LimpiarPantalla();
			Inicio_de_Sesion();
		}
	}while(bandera==0); //sale si se ingresa usuario y contraeña correctos
	
	fclose(Usuario_Asistente);
}
int MenuPrincipalAsistente()
{
	int Opcion;
	
	gotoxy(45,2);
	printf("Modulo del Asistente");
	gotoxy(45,3);
	printf("========================="); 
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

void mensaje(char const *cadena)
{
	printf("\n %50s ", cadena);
	system("PAUSE");
} //Fin de la función mensaje()

void registrarMascotas(FILE *Mascotas)
{
	Mascota reg; //crea la variable "reg" de tipo Mascota.
	int nroReg=0; //Variable contador del nro de registros almacenado.
	char continua='N';

	do
	{
		printf("\t** Registro Nro %3.0d **\n", ++nroReg);
		printf("\t****************************\n\n");
		_flushall();
		printf("\n\t Apellido y Nombre: ");
		gets(reg.ApellidoyNombre);
		strupr(reg.ApellidoyNombre);
		printf("\n\t Domicilio: ");
		gets(reg.Domicilio);
		strupr(reg.Domicilio);
		printf("\n\t DNI del Dueño: ");
		scanf("%d",&reg.DNI_Dueno);
		_flushall();
		printf("\n\t Localidad: ");
		gets(reg.Localidad);
		strupr(reg.Localidad);
		printf("\n\t Fecha de Nacimiento: \n");
		printf("\n\t Dia: ");
		scanf("%d",&reg.FechadeNacimiento.dia);
		printf("\n\t Mes: ");
		scanf("%d",&reg.FechadeNacimiento.mes);
		printf("\n\t Anio: ");
		scanf("%d",&reg.FechadeNacimiento.anio);
		printf("\n\t Peso(kg): ");
		scanf("%f",&reg.Peso);
		_flushall();
		printf("\n\t Telefono: ");
		gets(reg.Telefono);
		fwrite(&reg, sizeof(Mascota), 1, Mascotas); //Graba el registro lógico.
		_flushall();
		printf("\n\nContinuar Registrando Mascotas (S/N): ");
		scanf("%c", &continua);
	}while(continua == 'S' || continua == 's');
	system("CLS");
	mensaje("Fin de la carga");
}

void registrarTurnos(FILE *Turnos, FILE *Mascotas)
{
	int nroTur=0; //Variable contador del nro de turnos almacenados.
	char continua='N';
	int bandera;
	
	Turno regi;
	FILE *ArchTurnos;
	ArchTurnos=fopen("Turnos.dat","rb");
	
	Mascota reg;
	FILE *ArchMascotas;
	ArchMascotas=fopen("Mascotas.dat","rb");
	
	Datos_Veterianrios vet;
	FILE *Veterinarios;
	Veterinarios=fopen("Veterinarios.dat","rb");
	
	printf("\n\n\t Ingrese Nro de DNI del dueño: ");
	scanf("%d", &regi.DNI_Duenio);
	
	do
	{
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
			do{
			printf("Asignar Turno a %s",reg.ApellidoyNombre);
			
			//MOSTRAR LISTA DE VETERINARIOS
			printf("\tListado de Veterinarios\n");
			printf("\t*********************************************************\n\n");
			printf("\tApellido y Nombre \t Matricula **\n\n");
			rewind(Veterinarios); //Ubica el puntero en el primer registro del archivo.
			fread(&vet, sizeof(Datos_Veterianrios), 1, Veterinarios); //Leer el primer registro.
			
			if (feof(Veterinarios))
			{
				printf("El Archivo esta vacio\n No se Registro Informacion.");
			}
			else
			{
				while(!feof(Veterinarios)) //Repite hasta el último registro.
				{
					printf("\t %s ", vet.ApellidoNombre);
					printf("\t %d ", vet.matricula);
					printf("\n");
					fread(&vet, sizeof(Datos_Veterianrios), 1, Veterinarios); //Continua leyendo.
				}
			}
			printf("Ingrese una matricula: ");//ELEGIR UN VETERINARIO
			scanf("%d", &regi.MatriculaVeterinario);
			
			printf("\n\t Ingrese Fecha del Turno: \n");
			printf("\n\t Dia: ");
			scanf("%d",&regi.fecha.dia);
			printf("\n\t Mes: ");
			scanf("%d",&regi.fecha.mes);
			printf("\n\t Anio: ");
			scanf("%d",&regi.fecha.anio);
			fwrite(&regi, sizeof(Turno), 1, ArchTurnos); //Graba el registro lógico.
			_flushall();
			printf("\n\nContinuar Registrando Turnos (S/N): ");
			scanf("%c", &continua);
			
			}while(continua == 'S' || continua == 's');
			system("CLS");
			mensaje("Fin de la carga");
		}
		if (bandera==0)
		{
			printf("El DNI ingresado no existe");
			LimpiarPantalla();
			registrarTurnos(ArchTurnos,ArchMascotas);
		}
	}while(bandera==0); //sale si se ingresa dni correcto
	
	fclose(Turnos);
	fclose(Mascotas);
	fclose(Veterinarios);
}
void listarMascotas(FILE *Mascotas)
{
	Mascota reg; //Registro logico.
	/*----- Titulo del listado -----*/
	system("CLS");
	printf("\tL I S T A D O DE MASCOTAS\n");
	printf("\t*********************************************************\n\n");
	printf("\tApellido y Nombre \t Domicilio \t DNI del Dueño \t Localidad \t Fecha de Nacimiento \t Peso \t Telefono **\n\n");
	printf("\t*********************************************************\n\n");
	/*----- Listado de las Mascotas -----*/
	rewind(Mascotas); //Ubica el puntero en el primer registro del archivo.
	fread(&reg, sizeof(Mascota), 1, Mascotas); //Leer el primer registro.
	
	if (feof(Mascotas))
	{
		system("CLS");
		printf("El Archivo esta vacio\n No se Registro Informacion.");
	}
	else
	{
		while(!feof(Mascotas)) //Repite hasta el último registro.
		{
			printf("\t %s ", reg.ApellidoyNombre);
			printf("\t %s ", reg.Domicilio);
			printf("\t %d ", reg.DNI_Dueno);
			printf("\t %s ", reg.Localidad);
			printf("\t %d/%d/%d ", reg.FechadeNacimiento.dia, reg.FechadeNacimiento.mes, reg.FechadeNacimiento.anio);
			printf("\t %.2f ", reg.Peso);
			printf("\t %s ", reg.Telefono);
			printf("\n");
			fread(&reg, sizeof(Mascota), 1, Mascotas); //Continua leyendo.
		}
	}
	printf("F i n del L i s t a d o");
}
