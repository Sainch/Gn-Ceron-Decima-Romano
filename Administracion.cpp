#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<windows.h>
#include<iostream>
#include"funciones_y_estructuras.h"


//**********************************FUNCIONES***********************************

void Inicio_de_Sesion();
int MenuPrincipal_Administracion();
void Registrar_Veterinario(FILE *Veterinarios);
void Registrar_Usuario_Asistente(FILE *Usuario_Asistente);
void Rankin_Veterinarios_Atenciones(FILE *Veterinarios);
void Listar_Asistentes(FILE *Usuario_Asistente);
void Listar_Veterinarios(FILE *Veterinarios);

//**********************************AUXILIARES**********************************

int Verificar_Usuario_Valido(char Usuario[11]);
void Condiciones_Contrasena(int &y);
int Verificar_Contrasena_Valida(char Contrasena[33]);
void Condiciones_Usuario(int &y);

//******************************************************************************


main()
{
	setlocale(LC_CTYPE,"spanish");
	system("color 3");
	
	//*****************Datos a utilizar*************
	
	int bandera=1;
	char Opcion;
	Datos_Veterinarios DatosVet[50];
	FILE *Veterinarios,*Usuario_Asistente;
	
	//**********************************************
	
	Inicio_de_Sesion();//inicio del módulo de administracion
	LimpiarPantalla();
	
	do
	{
		Opcion=MenuPrincipal_Administracion();
		switch(Opcion)
		{
			case'a':case'A':
				LimpiarPantalla();
				Registrar_Veterinario(Veterinarios);
				break;
			case'b':case'B':
				LimpiarPantalla();
				Registrar_Usuario_Asistente(Usuario_Asistente);
				break;
			case'c':case'C':
				LimpiarPantalla();
				Rankin_Veterinarios_Atenciones(Veterinarios);
				break;
			case'd':case'D':
				LimpiarPantalla();
				Listar_Asistentes(Usuario_Asistente);
				break;
			case'e':case'E':
				LimpiarPantalla();
				Listar_Veterinarios(Veterinarios);
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
	int Cont=0,bandera=0;
	
	FILE * Contrasena_Administracion;
	Contrasena_Administracion=fopen("Clave_Modulo_Administracion.dat","r+b");
	fread(&contrasena1,sizeof(palabra),1,Contrasena_Administracion);
	
	if(Contrasena_Administracion==NULL || strlen(contrasena1)<6)
	{
		fclose(Contrasena_Administracion);
		Contrasena_Administracion=fopen("Clave_Modulo_Administracion.dat","w+b");
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
		if(strcmp(contrasena1,contrasena2)==0)
		{
			bandera=1;
		}
		while(strcmp(contrasena1,contrasena2)!=0 && Cont<2)
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
			if(strcmp(contrasena1,contrasena2)==0)
			{
				bandera=1;
			}
		}
		if(bandera==0)
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
	printf("a._Registrar Veterinario.");
	gotoxy(25,5);
	printf("b._Registrar Usuario Asistente.");
	gotoxy(25,6);
	printf("c._Ranking de Veterinarios por Atenciones del Mes.");
	gotoxy(25,7);
	printf("d._Mostrar Asistentes.");
	gotoxy(25,8);
	printf("e._Mostrar Veterianarios.");
	gotoxy(25,10);
	printf("f._Cerrar Aplicación.");
	gotoxy(25,12);
	printf("Ingrese una opción:");
	_flushall();
	scanf("%c",&OP);
	return OP;
}

void Registrar_Veterinario(FILE *Veterinarios)
{
	int y=1;
	int bandera1=0,bandera2,bandera3;
	Datos_Veterinarios Aux1,Aux2;
	
	Veterinarios=fopen("Veterinarios.dat","rb");
	if(Veterinarios==NULL)
	{
		bandera1=1;//significa que no hay veterianrios registrados
	}
	fclose(Veterinarios);
	
	Veterinarios=fopen("Veterinarios.dat","a+b");
	gotoxy(25,y);y++;
	printf("======================");
	gotoxy(25,y);y++;
	printf("INGRESO DE VETERINARIO");
	gotoxy(25,y);y++;
	printf("======================");
	gotoxy(15,y);y++;
	printf("Ingrese el nombre de usuario o \"MOSTRAR\" para ver las condiciones:");
	_flushall();
	gets(Aux1.Usuario);
	if(strcmp(Aux1.Usuario,"MOSTRAR")==0 ||strcmp(Aux1.Usuario,"mostrar")==0)
	{
		Condiciones_Usuario(y);
		printf("Ingrese el nombre de usuario:");
		gets(Aux1.Usuario);
	}
	
	//Verificar Usuario Válido***************************************
	do
	{
		bandera2=0;
		bandera2=Verificar_Usuario_Valido(Aux1.Usuario);
		if(bandera2==1)
		{
			gotoxy(25,y);y++;
			printf("USUARIO INVÁLIDO! POR FAVOR INGRESE NUEVAMENTE EL NOMBRE DE USUARIO");
			gotoxy(15,y);y++;
			printf("Ingrese el nombre de usuario o \"MOSTRAR\" para ver elas condiciones:");
			_flushall();
			gets(Aux1.Usuario);
			if(strcmp(Aux1.Usuario,"MOSTRAR")==0 ||strcmp(Aux1.Usuario,"mostrar")==0)
			{
				Condiciones_Usuario(y);
				printf("Ingrese el nombre de usuario:");
				gets(Aux1.Usuario);
			}
		}
		
		//Comparación***********************************************************************
		if(bandera1==0 && bandera2==0)//si no hay veterinarios no compara, si se ingreso un usuario invalido no compara
		{
			rewind(Veterinarios);
			fread(&Aux2,sizeof(Datos_Veterinarios),1,Veterinarios);
			while(!feof(Veterinarios) && bandera2==0)
			{
				if(strcmp(Aux2.Usuario,Aux1.Usuario)==0)//Usuario existente
				{
					bandera2=1;
				}
				fread(&Aux2,sizeof(Datos_Veterinarios),1,Veterinarios);
			}
			if(bandera2==1)
			{
				gotoxy(25,y);y++;
				printf("USUARIO EXISTENTE! POR FAVOR INGRESE NUEVAMENTE EL NOMBRE DE USUARIO");
				gotoxy(15,y);y++;
				printf("Ingrese el nombre de usuario:");
				gets(Aux1.Usuario);
			}
		}
	}while(bandera2==1);
	
	//**************************************************************
	
	gotoxy(15,y);y++;
	printf("Ingrese el nombre y apellido:");
	gets(Aux1.ApellidoNombre);
	gotoxy(15,y);y++;
	printf("Ingrese la contraseña o \"MOSTRAR\" para ver las condiciones:");
	gets(Aux1.Contrasena);
	if(strcmp(Aux1.Contrasena,"MOSTRAR")==0 || strcmp(Aux1.Contrasena,"mostrar")==0)
	{
		Condiciones_Contrasena(y);
		printf("Ingrese la contraseña:");
		gets(Aux1.Contrasena);
	}
	
	//Verificar Contraseña válida**************************************
	
	do
	{
		bandera1=0;
		bandera1=Verificar_Contrasena_Valida(Aux1.Contrasena);
		if(bandera1==1)
		{
			gotoxy(25,y);y++;
			printf("CONTRASEÑA INVÁLIDA!POR FAVOR INGRESE NUEVAMENTE LA CONTRASEÑA");
			gotoxy(15,y);y++;
			printf("Ingrese la contraseña o \"MOSTRAR\" para ver las condiciones:");
			gets(Aux1.Contrasena);
			if(strcmp(Aux1.Contrasena,"MOSTRAR")==0 || strcmp(Aux1.Contrasena,"mostrar")==0)
			{
				Condiciones_Contrasena(y);
				printf("Ingrese la contraseña:");
				gets(Aux1.Contrasena);
			}
		}
	}while(bandera1==1);
	
	//*****************************************************************
	
	gotoxy(15,y);y++;
	printf("Ingrese la matrícula:");
	scanf("%d",&Aux1.matricula);
	gotoxy(15,y);y++;
	printf("Ingrese el DNI:");
	scanf("%d",&Aux1.DNI);
	gotoxy(15,y);y++;
	_flushall();
	printf("Ingrese el telefono:");
	gets(Aux1.telefono);
	
	fwrite(&Aux1,sizeof(Datos_Veterinarios),1,Veterinarios);
	
	fclose(Veterinarios);
}

void Registrar_Usuario_Asistente(FILE *Usuario_Asistente)
{
	int y=1;
	int bandera1=0,bandera2,bandera3;
	Datos_Usuarios_Asistentes Aux1,Aux2;
	
	Usuario_Asistente=fopen("Usuarios_Asistentes.dat","rb");
	if(Usuario_Asistente==NULL)
	{
		bandera1=1;//significa que no hay asistentes registrados
	}
	fclose(Usuario_Asistente);
	
	Usuario_Asistente=fopen("Usuarios_Asistentes.dat","a+b");
	gotoxy(25,y);y++;
	printf("====================");
	gotoxy(25,y);y++;
	printf("INGRESO DE ASISTENTE");
	gotoxy(25,y);y++;
	printf("====================");
	gotoxy(15,y);y++;
	printf("Ingrese el nombre de usuario o \"MOSTRAR\" para ver las condiciones:");
	_flushall();
	gets(Aux1.Usuario);
	if(strcmp(Aux1.Usuario,"MOSTRAR")==0 ||strcmp(Aux1.Usuario,"mostrar")==0)
	{
		Condiciones_Usuario(y);
		printf("Ingrese el nombre de usuario:");
		gets(Aux1.Usuario);
	}
	
	//Verificar Usuario Válido**************************************************
		
	do
	{
		bandera2=0;
		bandera2=Verificar_Usuario_Valido(Aux1.Usuario);
		if(bandera2==1)
		{
			gotoxy(25,y);y++;
			printf("USUARIO INVÁLIDO! POR FAVOR INGRESE NUEVAMENTE EL NOMBRE DE USUARIO");
			gotoxy(15,y);y++;
			printf("Ingrese el nombre de usuario o \"MOSTRAR\" para ver elas condiciones:");
			_flushall();
			gets(Aux1.Usuario);
			if(strcmp(Aux1.Usuario,"MOSTRAR")==0 ||strcmp(Aux1.Usuario,"mostrar")==0)
			{
				Condiciones_Usuario(y);
				printf("Ingrese el nombre de usuario:");
				gets(Aux1.Usuario);
			}
		}
		
		//Comparación***********************************************************************
		if(bandera1==0 && bandera2==0)//si no hay veterinarios no compara, si se ingreso un usuario invalido no compara
		{
			rewind(Usuario_Asistente);
			fread(&Aux2,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
			while(!feof(Usuario_Asistente) && bandera2==0)
			{
				if(strcmp(Aux2.Usuario,Aux1.Usuario)==0)//Usuario existente
				{
					bandera2=1;
				}
				fread(&Aux2,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
			}
			if(bandera2==1)
			{
				gotoxy(25,y);y++;
				printf("USUARIO EXISTENTE! POR FAVOR INGRESE NUEVAMENTE EL NOMBRE DE USUARIO");
				gotoxy(15,y);y++;
				printf("Ingrese el nombre de usuario:");
				gets(Aux1.Usuario);
			}
		}
	}while(bandera2==1);
	
	//**************************************************************
	
	gotoxy(15,y);y++;
	printf("Ingrese el Apellido y Nombre:");
	gets(Aux1.ApellidoNombre);
	gotoxy(15,y);y++;
	printf("Ingrese la contraseña o \"MOSTRAR\" para ver las condiciones:");
	gets(Aux1.Contrasena);
	if(strcmp(Aux1.Contrasena,"MOSTRAR")==0 || strcmp(Aux1.Contrasena,"mostrar")==0)
	{
		Condiciones_Contrasena(y);
		printf("Ingrese la contraseña:");
		gets(Aux1.Contrasena);
	}
	do
	{
		bandera1=0;
		bandera1=Verificar_Contrasena_Valida(Aux1.Contrasena);
		if(bandera1==1)
		{
			gotoxy(25,y);y++;
			printf("CONTRASEÑA INVÁLIDA!POR FAVOR INGRESE NUEVAMENTE LA CONTRASEÑA");
			gotoxy(15,y);y++;
			printf("Ingrese la contraseña o \"MOSTRAR\" para ver las condiciones:");
			gets(Aux1.Contrasena);
			if(strcmp(Aux1.Contrasena,"MOSTRAR")==0 || strcmp(Aux1.Contrasena,"mostrar")==0)
			{
				Condiciones_Contrasena(y);
				printf("Ingrese la contraseña:");
				gets(Aux1.Contrasena);
			}
		}
	}while(bandera1==1);
	
	fwrite(&Aux1,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
	fclose(Usuario_Asistente);
}

void Rankin_Veterinarios_Atenciones(FILE *Veterinarios)
{
	Turno Aux1,VecTurnos[100];
	Mascota Aux2,VecMascotas[100];
	Datos_Veterinarios Aux3,VecVeterinarios[20];
	FILE *ArchTurnos,*ArchMascotas;
	int CantTurnos,CantVeterinarios,i,j,k,y=1,mes,bandera;
	int VecCantTurnosVet[20],Aux4;
	
	//Cargar los datos en un archivo
	
	Veterinarios=fopen("Veterinarios.dat","rb");
	ArchTurnos=fopen("Turnos.dat","rb");
	
	fread(&Aux1,sizeof(Turno),1,ArchTurnos);
	while(!feof(ArchTurnos))
	{
		VecTurnos[i]=Aux1;
		i++;
		fread(&Aux1,sizeof(Turno),1,ArchTurnos);
	}
	CantTurnos=i;
	i=0;
	fread(&Aux3,sizeof(Datos_Veterinarios),1,Veterinarios);
	while(!feof(Veterinarios))
	{
		VecVeterinarios[i]=Aux3;
		i++;
		fread(&Aux3,sizeof(Datos_Veterinarios),1,Veterinarios);
	}
	CantVeterinarios=i;
	fclose(Veterinarios);
	fclose(ArchTurnos);
	
	gotoxy(35,y);y++;
	printf("===========================================");
	gotoxy(35,y);y++;
	printf("RANKING DE TURNOS ATENDIDOS DE VETERINARIOS");
	gotoxy(35,y);y++;y++;
	printf("===========================================");	
	if(CantVeterinarios==0)
	{
		gotoxy(35,y);y++;
		printf("NO HAY VETERINARIOS INGRESADOS");
		gotoxy(35,y);
		return;
	}
	gotoxy(15,y);y++;
	printf("Ingrese el mes:");
	scanf("%d",&mes);
	LimpiarPantalla();y=1;
	gotoxy(35,y);y++;
	printf("===========================================");
	gotoxy(35,y);y++;
	printf("RANKING DE TURNOS ATENDIDOS DE VETERINARIOS");
	gotoxy(35,y);y++;y++;
	printf("===========================================");
	
	
	for(i=0;i<CantVeterinarios;i++)//Contar cantidad de turnos registrado por cada veterinario
	{
		VecCantTurnosVet[i]=0;
		for(j=0;j<CantTurnos;j++)
		{
			if(VecTurnos[j].fecha.mes==mes && VecTurnos[j].MatriculaVeterinario==VecVeterinarios[i].matricula && strcmp(VecTurnos[j].DetalleAtencion,"")!=0)
			{
				VecCantTurnosVet[i]=VecCantTurnosVet[i]+1;
			}
		}
	}
	
	do//Ordenar según la cantidad de pacientes atendidos
	{
		bandera=0;
		for(i=0;i<CantVeterinarios-1;i++)
		{
			if(VecCantTurnosVet[i]<VecCantTurnosVet[i+1])
			{
				bandera=1;
				Aux4=VecCantTurnosVet[i+1];
				VecCantTurnosVet[i+1]=VecCantTurnosVet[i];
				VecCantTurnosVet[i]=Aux4;
				Aux3=VecVeterinarios[i+1];
				VecVeterinarios[i+1]=VecVeterinarios[i];
				VecVeterinarios[i]=Aux3;
			}
		}
	}while(bandera==1);
	
	for(i=0;i<CantVeterinarios;i++)
	{
		gotoxy(15,y);y++;y++;
		printf("Veterinario %s: %d turnos",VecVeterinarios[i].ApellidoNombre,VecCantTurnosVet[i]);
	}
	gotoxy(15,y);
	printf("======================================================================");
}

void Listar_Asistentes(FILE *Usuario_Asistente)
{
	Datos_Usuarios_Asistentes Aux1;
	int y=1;
	
	Usuario_Asistente=fopen("Usuarios_Asistentes.dat","rb");
	if(Usuario_Asistente!=NULL)
	{
		gotoxy(25,y);y++;
		printf("=====================");
		gotoxy(25,y);y++;
		printf("LISTADO DE ASISTENTES");
		gotoxy(25,y);y++;y++;
		printf("=====================");
		fread(&Aux1,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
		while(!feof(Usuario_Asistente))
		{
			gotoxy(15,y);y++;
			printf("Nombre:%s",Aux1.ApellidoNombre);
			gotoxy(15,y);y++;
			printf("Usuario:%s",Aux1.Usuario);
			gotoxy(15,y);y++;y++;
			printf("Contraseña:%s",Aux1.Contrasena);
			fread(&Aux1,sizeof(Datos_Usuarios_Asistentes),1,Usuario_Asistente);
		}
	}
	else
	{
		gotoxy(35,y);y++;
		printf("=============================");
		gotoxy(35,y);y++;
		printf("NO HAY ASISTENTES REGISTRADOS");
		gotoxy(35,y);
		printf("=============================");
	}
	fclose(Usuario_Asistente);
}

void Listar_Veterinarios(FILE *Veterinarios)
{
	Datos_Veterinarios Aux1;
	int y=1;
	
	Veterinarios=fopen("Veterinarios.dat","rb");
	if(Veterinarios!=NULL)
	{
		gotoxy(25,y);y++;
		printf("=======================");
		gotoxy(25,y);y++;
		printf("LISTADO DE VETERINARIOS");
		gotoxy(25,y);y++;y++;
		printf("=======================");
		fread(&Aux1,sizeof(Datos_Veterinarios),1,Veterinarios);
		while(!feof(Veterinarios))
		{
			gotoxy(15,y);y++;
			printf("Nombre:%s",Aux1.ApellidoNombre);
			gotoxy(15,y);y++;
			printf("Usuario:%s",Aux1.Usuario);
			gotoxy(15,y);y++;
			printf("Contraseña:%s",Aux1.Contrasena);
			gotoxy(15,y);y++;
			printf("Matricula:%d",Aux1.matricula);
			gotoxy(15,y);y++;
			printf("DNI:%d",Aux1.DNI);
			gotoxy(15,y);y++;y++;
			printf("Telefono:%s",Aux1.telefono);
			fread(&Aux1,sizeof(Datos_Veterinarios),1,Veterinarios);
		}
	}
	else
	{
		gotoxy(35,y);y++;
		printf("===============================");
		gotoxy(35,y);y++;
		printf("NO HAY VETERINARIOS REGISTRADOS");
		gotoxy(35,y);
		printf("===============================");
	}
	fclose(Veterinarios);
}

//*****************************OTRAS FUNCIONES AUXILIARES***********************

int Verificar_Usuario_Valido(char Usuario[11])
{
	int bandera=0,i,ContMayus=0,ContDigit=0;
	
	if(strlen(Usuario)<6 || strlen(Usuario)>10)//entre 6 y 10 caracteres
		bandera=1;
	if((Usuario[0]<'a' || Usuario[0]>'z') && bandera==0)//primera letra minúscula
		bandera=1;
	if(bandera==0)
	{
		for(i=0;i<strlen(Usuario);i++)
		{
			if(isupper(Usuario[i]))
				ContMayus++;
			if(isdigit(Usuario[i]))
				ContDigit++;
		}
		if(ContMayus<2)
			bandera=1;
		if(ContDigit>3)
			bandera=1;
	}
	return bandera;
}

int Verificar_Contrasena_Valida(char Contrasena[33])
{
	int bandera=0,i,ValorAscci1,ValorAscci2,ValorAscci3;
	int bandMinus=0,bandMayus=0,bandDigit=0;
	char Aux[33];
	
	if(strlen(Contrasena)<6 || strlen(Contrasena)>32)//entre 6 y 32 caracteres
		bandera=1;
	if(bandera==0)
	{
		//Comprobar si hay al menos 1 caracter en minuscula, 1 mayuscula y 1 digito
		for(i=0;i<strlen(Contrasena) && bandera==0;i++)
		{
			if(isalnum(Contrasena[i]))
			{
				if(islower(Contrasena[i]) && bandMinus==0)
					bandMinus=1;
				if(isupper(Contrasena[i]) && bandMayus==0)
					bandMayus=1;
				if(isdigit(Contrasena[i]) && bandDigit==0)
					bandDigit=1;
			}
			else//Algun caracter no es alfabético o númerico
				bandera=1;
		}
		
		if((bandMinus==0 || bandMayus==0 || bandDigit==0) && bandera==0)//hay al menos un caracteres en mayuscula, minuscula o dígito
			bandera=1;
	}
	
	if(bandera==0)
	{
		strcpy(Aux,Contrasena);
		strlwr(Aux);//Como puede haber caracteres en minusculas y mayúsculas sucesivos, pasamos todos a minúsculas en un Auxiliar
		for(i=0;i<(strlen(Contrasena)-1) && bandera==0;i++)//Verificar 3 numeros sucesivos o 
		{
			ValorAscci1=Aux[i];
			ValorAscci2=Aux[i+1];
			if((ValorAscci1+1)==ValorAscci2)
			{
				if(isdigit(Contrasena[i]) && i<(strlen(Contrasena)-2))//son digitos, y deben ser 3 sucesivos
				{
					ValorAscci3=Aux[i+2];
					if((ValorAscci2+1)==ValorAscci3)
						bandera=1;
				}
				else//Como solo hay digitos y alfabéticos no es necesario saber si es alfabético
				{
					bandera=1;
				}
			}
		}
	}
	
	return bandera;
}

void Condiciones_Usuario(int &y)
{
	gotoxy(25,y);y++;
	printf("=================================");
	gotoxy(25,y);y++;
	printf("CONDICIONES DEL NOMBRE DE USUARIO");
	gotoxy(25,y);y++;
	printf("=================================");
	gotoxy(25,y);y++;
	printf("1.-Tener entre 6 y 10 caracteres.");
	gotoxy(25,y);y++;
	printf("2.-Ser único.");
	gotoxy(25,y);y++;
	printf("3.-Comenzar con una letra minúscula.");
	gotoxy(25,y);y++;
	printf("4.-Tener al menos 2 letras mayúsculas.");
	gotoxy(25,y);y++;y++;
	printf("5.-Máximo de 3 dígitos.");
	gotoxy(15,y);y++;y++;
}

void Condiciones_Contrasena(int &y)
{
	gotoxy(25,y);y++;
	printf("============================");
	gotoxy(25,y);y++;
	printf("CONDICIONES DE LA CONTRASENA");
	gotoxy(25,y);y++;
	printf("============================");
	gotoxy(25,y);y++;
	printf("1.-Tener entre 6 y 32 caracteres.");
	gotoxy(25,y);y++;
	printf("2.-Sólo puede contener cacracteres alfanuméricos.");
	gotoxy(25,y);y++;
	printf("3.-Debe tener una letra mayúscula, una letra minúscula y un dígito.");
	gotoxy(25,y);y++;
	printf("4.-NO debe tener más de tres caracteres númericos consecutivos.");
	gotoxy(25,y);y++;y++;
	printf("5.-NO debe tener dos caracteres alfabéticos consecutivos.");
	gotoxy(15,y);y++;y++;
}
