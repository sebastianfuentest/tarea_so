#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>


void CrearMazo(char *dir){//READY
  FILE* fp;
  char colores[9][27]={" Rojo.txt"," Azul.txt"," Verde.txt"," Amarillo.txt",
                        " Rojo 2.txt", " Azul 2.txt", " Verde 2.txt", " Amarillo 2.txt", " Negro "};
  int i,j;
  char n[20], p[20];
  chdir(dir);                                                         //Cambio al directorio Mazo
   //Crear colores 1 al 9
   for(i=0;i<8;i++){
     for(j=1; j<10;j++){
       sprintf(n, "%d", j);
       strcat(n, colores[i]);
       fp=fopen(n, "w");
       fclose(fp);
     }
   }
   //Crear 0's
   for(i=0;i<4;i++){
     j=0;
     sprintf(n,"%d",j);
     strcat(n, colores[i]);
     fp=fopen(n, "w");
     fclose(fp);
   }
   //Crear reversa, salto, +2
   for(i=0; i<8; i++){
     sprintf(n, "%s", "Reversa");
     strcat(n, colores[i]);
     fp=fopen(n, "w");
     fclose(fp);

     sprintf(n, "%s", "+2");
     strcat(n, colores[i]);
     fp=fopen(n, "w");
     fclose(fp);

     sprintf(n, "%s", "Salto");
     strcat(n, colores[i]);
     fp=fopen(n, "w");
     fclose(fp);
   }
   //Crear especiales
   for(i=1; i<5; i++){
     sprintf(p, "%d", i);
     sprintf(n, "%s", "+4");
     strcat(n, colores[8]);
     strcat(n, p);
     strcat(n, ".txt");
     fp=fopen(n, "w");
     fclose(fp);

     sprintf(p, "%d", i);
     sprintf(n, "%s", "CartaColor");
     strcat(n, colores[8]);
     strcat(n, p);
     strcat(n, ".txt");
     fp=fopen(n, "w");
     fclose(fp);
   }

   chdir("..");                                                       //Vuelvo a la carpeta Tarea1

}

void CrearCarpetas(){//READY
  mkdir("./Mazo", 0777);
  mkdir("./Jugador1", 0777);
  mkdir("./Jugador2", 0777);
  mkdir("./Jugador3", 0777);
  mkdir("./Jugador4", 0777);
}

char * ObtenerCarta(int n){ //READY
  DIR *directorio;
  int i = 0;
  static char carta[30];
  struct dirent *file;
  directorio = opendir("Mazo");                                     //Abro la carpeta Mazo
  if (directorio){                                                 //Verifico que exista Mazo
      while ((file = readdir(directorio)) != NULL){                //Recorro los archivos de la carpeta hasta que termine
        if (file->d_type == DT_REG){                               //Verifico el tipo del archivo
          if(i == n){
          strcpy(carta,file->d_name);                              //Copio el nombre del archivo en carta
          printf("%s\n", carta);
          chdir("Mazo");                                          //Voy a Mazo
          remove(carta);                                          //Borro la carta del mazo
          chdir("..");                                            //Vuelvo a Tarea1
          break;
        }
          i++;
      }
    }
      closedir(directorio);
    }
    else{
      printf("No se pudo abrir el directorio\n");
    }
  return carta;
  }

void Repartir(){ //READY
  int pos, repartidas=0,i;
  char* card;
  FILE *fp;
  srand(time(0));
  for(i=0;i<8;i++){
    //Jugador1
    printf("Jugador1 Obtuvo: ");
    pos=rand()%(110 - repartidas) + 1;
    card=ObtenerCarta(pos);
    chdir("Jugador1");
    fp=fopen(card,"w");
    fclose(fp);
    chdir("..");
    repartidas++;

    //Jugador2
    printf("Jugador2 Obtuvo: ");
    pos=rand()%(110 - repartidas) + 1;
    card=ObtenerCarta(pos);
    chdir("Jugador2");
    fp=fopen(card,"w");
    fclose(fp);
    chdir("..");
    repartidas++;

    //Jugador3
    printf("Jugador3 Obtuvo: ");
    pos=rand()%(110 - repartidas) + 1;
    card=ObtenerCarta(pos);
    chdir("Jugador3");
    fp=fopen(card,"w");
    fclose(fp);
    chdir("..");
    repartidas++;

    //Jugador4
    printf("Jugador4 Obtuvo: ");
    pos=rand()%(110 - repartidas) + 1;
    card=ObtenerCarta(pos);
    chdir("Jugador4");
    fp=fopen(card,"w");
    fclose(fp);
    chdir("..");
    repartidas++;

  }

}


int main(){
  CrearCarpetas();
  CrearMazo("./Mazo");
  Repartir();
}
