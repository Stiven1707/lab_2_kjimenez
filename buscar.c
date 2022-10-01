#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#ifndef MAX
#define MAX 100
#endif

int es_directorio(char * ruta);
//Busca recursivamente archivos/directorios cuyo nombre contenga patron
//Retorna el total de coincidencias
int buscar(char * directorio, char * patron);


char* DimCadena(int prmLongCadena);
char* DimCadena2(char* prmtempCadena,int prmLongCadena);


/**
 * @brief 
 * 
 * @param argc = 3
 * @param argv[0] = nombre del ejecutable
 * @param argv[1] = directorio
 * @param argv[2] = patron de busqueda
 * @return int 
 */
int main(int argc, char *argv[]){
    /*
    if (argc != 3)
    {
        fprintf(stderr,"Debe especificar el directorio y el patron\n");
        exit(EXIT_FAILURE);
    }
    
    if(es_directorio(argv[1])){
        printf("%s Es un directorio\n",argv[1]);
    }else{
        printf("%s No es un directorio\n",argv[1]);
    }*/
    printf("El patron de busqueda es:%s\n",argv[2]);
    //printf("# devuelto por buscar: %d\n",buscar(argv[1],argv[2]));
    printf("# devuelto por buscar: %d\n",buscar("/home/kjimenez/Documentos","prueba"));
    exit(EXIT_SUCCESS);
}
/**
 * @brief Valida si la ruta existe
 * 
 * @param ruta cadena que contiene la supuesta ruta
 * @return int Retorna 1 si la ruta dada es un directorio, 0 en caso contrario
 */
int es_directorio(char * ruta){
    struct stat s;
    int resultado;
    //Usar el servicio stat para obtener la información de la ruta dada
    resultado = stat(ruta,&s);
    if(resultado  <  0){// error
        perror("stat");
        printf("\n");
    }
    //Usar el macro S_ISDIR sobre el atributo st_mode de la estructura
    //para verificar si es un directorio
    if(S_ISDIR(s.st_mode)){
        return 1;//C no tiene tipo booleano, 1 = verdadero
    }else
    {
        return 0;//C no tiene tipo booleano, 0 = falso
    }
    
}
/**
 * @brief Busca recursivamente archivos/directorios cuyo nombre contenga patron
 * 
 * @param directorio = donde se encuentra
 * @param patron = patron de busqueda
 * @return int Retorna el total de coincidencias
 */
int buscar(char * directorio, char * patron){
    printf("Entrando a la funcion buscar\n");
    int total = 0;
    char *ruta;

    DIR *d;
    struct dirent *ent;
    
    //Abrir el directorio con opendir
    d = opendir(directorio);

    //Validar el resultado de la llamada al servicio opendir
    if(d  ==  NULL){// error
        perror("opendir");
        printf("\n");
        return total;
    }
    printf("entrando al while\n");
    //Leer el directorio con el servicio readdir
    while ((ent = readdir(d)) != NULL)
    {
        ruta = (char*)malloc(10*sizeof(char));
        //ruta = DimCadena(strlen(directorio)+strlen(ent->d_name)+2);
        //Construir la ruta completa directorio/ent->d_name
        //strcpy(ruta,strcpy(strcat(directorio,"/"),ent->d_name));
        printf("ruta:       %s\n",ruta);
        printf("directorio: %s\n",directorio);
        printf("dname:      %s\n",ent->d_name);
        strcpy(ruta,ent->d_name);
        //Verificar si la entrada (archivo o directorio) contiene 
        //el patrón de búsqueda
        if (strstr(ent->d_name,patron) != NULL)
        {
            //imprimir la ruta completa
            printf(ruta);
            printf("**********************\n");
            total = total + 1;
        }

        if (es_directorio(ruta) && strcmp(ent->d_name,".") !=0 && strcmp(ent->d_name,"..") !=0)
        {
            //Buscar recursivamente dentro del subdirectorio
            total = total + buscar(ruta,patron);
        }
        
        
    }
    //cerrar el directorio
    closedir(d);
    free(ruta);
    return total;
}
char* DimCadena(int prmLongCadena){
    char* cadena = (char*)malloc(prmLongCadena);
    return cadena;
}
/**
 * @brief 
 * 
 * @param prmLongCadena 
 * @return char* 
 */
char* DimCadena2(char* prmtempCadena,int prmLongCadena){
    char* cadena = (char*)malloc(prmLongCadena);
    strcpy(cadena,prmtempCadena);
    return cadena;
}
