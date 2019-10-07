#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

int repartidas=0;

int GetNumber (char* carta) { //READY
   char str[20];
   const char s[2] = " ";
   char *token;
   strcpy(str, carta);
   token = strtok(str, s);
   if (strcmp(token, "0")==0) return 0;
   if (strcmp(token, "1")==0) return 1;
   if (strcmp(token, "2")==0) return 2;
   if (strcmp(token, "3")==0) return 3;
   if (strcmp(token, "4")==0) return 4;
   if (strcmp(token, "5")==0) return 5;
   if (strcmp(token, "6")==0) return 6;
   if (strcmp(token, "7")==0) return 7;
   if (strcmp(token, "8")==0) return 8;
   if (strcmp(token, "9")==0) return 9;
   if (strcmp(token, "+2")==0) return 10;
   if (strcmp(token, "Reversa")==0) return 11;
   if (strcmp(token, "Salto")==0) return 12;
   if (strcmp(token, "+4")==0) return 13;
   if (strcmp(token, "CartaColor")==0) return 13;
   return 69;                                                        //Carta Invalida
}

int GetColor(char* carta){ //READY
  char str[20];
  const char s[2] = " ";
  char *token;
  strcpy(str, carta);
  token = strtok(str, s);
  token = strtok(NULL, s);
  if (strcmp(token, "Rojo.txt")==0) return 0;
  if (strcmp(token, "Azul.txt")==0) return 1;
  if (strcmp(token, "Verde.txt")==0) return 2;
  if (strcmp(token, "Amarillo.txt")==0) return 3;
  if (strcmp(token, "Negro.txt")==0) return 4;
  if (strcmp(token, "Rojo")==0) return 0;
  if (strcmp(token, "Azul")==0) return 1;
  if (strcmp(token, "Verde")==0) return 2;
  if (strcmp(token, "Amarillo")==0) return 3;
  if (strcmp(token, "Negro")==0) return 4;

  return 69;                                                   //Color invalido
}

int Jugable(char* carta, char* lastcard){//READy
  int numCarta, colorCarta;
  int numLast, colorLast;

  numCarta=GetNumber(carta);
  colorCarta=GetColor(carta);
  numLast=GetNumber(lastcard);
  colorLast=GetColor(lastcard);

  //printf("NumCarta %i y NumLast %i\n", numCarta, numLast);
  //printf("colorCarta %i y colorLast %i\n", colorCarta, colorLast);

  if(numCarta==numLast) return 0;
  if(colorCarta==colorLast) return 0;
  if(colorCarta==4) return 0;
  if(numCarta==13) return 0;
  if(colorLast==4) return 0;
  if(numLast==13) return 0;
  return 1;
}

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
  mkdir("./LastCard", 0777);
}

char * ObtenerCarta(int n, char* Carpeta){ //READY
  DIR *directorio;
  int i = 0;
  static char carta[30];
  struct dirent *file;
  directorio = opendir(Carpeta);                                     //Abro la carpeta Mazo
  if (directorio){                                                 //Verifico que exista Mazo
      while ((file = readdir(directorio)) != NULL){                //Recorro los archivos de la carpeta hasta que termine
        if (file->d_type == DT_REG){                               //Verifico el tipo del archivo
          if(i == n){
          strcpy(carta,file->d_name);                              //Copio el nombre del archivo en carta
          //printf("%s\n", carta);

          break;
        }
          i++;
      }
    }
      if (strcmp(Carpeta,"Mazo")==0){
        chdir(Carpeta);                                          //Voy a Mazo
        remove(carta);                                          //Borro la carta del mazo
        chdir("..");                                            //Vuelvo a Tarea1
      }
      closedir(directorio);
    }
    else{
      printf("No se pudo abrir el directorio\n");
    }
  return carta;
  }

void Repartir(){ //READY
  int pos,i;
  char* card;
  FILE *fp;
  srand(time(0));
  for(i=0;i<7;i++){
    //Jugador1
    pos=rand()%(110 - repartidas) + 1;
    card=ObtenerCarta(pos, "Mazo");
    //printf("Jugador1 Obtuvo: %s\n", card);
    chdir("Jugador1");
    fp=fopen(card ,"w");
    fclose(fp);
    chdir("..");
    repartidas++;

    //Jugador2
    pos=rand()%(110 - repartidas) + 1;
    card=ObtenerCarta(pos, "Mazo");
    //printf("Jugador2 Obtuvo: %s\n", card);
    chdir("Jugador2");
    fp=fopen(card,"w");
    fclose(fp);
    chdir("..");
    repartidas++;

    //Jugador3

    pos=rand()%(110 - repartidas) + 1;
    card=ObtenerCarta(pos, "Mazo");
    //printf("Jugador3 Obtuvo: %s\n", card);
    chdir("Jugador3");
    fp=fopen(card,"w");
    fclose(fp);
    chdir("..");
    repartidas++;

    //Jugador4
    pos=rand()%(110 - repartidas) + 1;
    card=ObtenerCarta(pos, "Mazo");
    //printf("Jugador4 Obtuvo: %s\n", card);
    chdir("Jugador4");
    fp=fopen(card,"w");
    fclose(fp);
    chdir("..");
    repartidas++;

  }


  pos=rand()%(110 - repartidas) + 1;
  card=ObtenerCarta(pos, "Mazo");
  //printf("La Carta en la Pila es: %s\n", card);
  chdir("LastCard");
  fp=fopen(card,"w");
  fclose(fp);
  chdir("..");
  repartidas++;

}

void RobarCarta( char* Player, char* ultimaCard, int why){ //READY
  int pos;
  char* card;
  FILE* fp;
  pos=rand()%(110 - repartidas) + 1;
  card=ObtenerCarta(pos, "Mazo");
  printf("Has robado %s.\n", card);
  if (why==0){
    int flag=Jugable(card, ultimaCard);
    if(flag==0){
      printf("Has robado %s que es jugable.\n", card);
      chdir("LastCard");
      remove(ultimaCard);
      fp=fopen(card,"w");
      fclose(fp);
      chdir("..");

    }
    else{
      chdir(Player);
      fp=fopen(card,"w");
      fclose(fp);
      chdir("..");
    }
  }
  else{
    printf("Has tenido que robar %s\n", card);
    chdir(Player);
    fp=fopen(card,"w");
    fclose(fp);
    chdir("..");
  }
}

void JugarCarta( char* Player, char* card, char* ultimaCard){//READY
  FILE *fp;
  chdir(Player);
  remove(card);
  chdir("..");
  chdir("LastCard");
  remove(ultimaCard);
  fp=fopen(card, "w");
  fclose(fp);
  chdir("..");
}

int Turno(char* Jugador){ //READY
  int i=0, jugables=0, decision=0, flag=0;
  char *aux, *aux1, *aux2;
  char lastcard[100], mano[100], lastmano[100];
  aux=ObtenerCarta(0,"LastCard");
  strcpy(lastcard,aux);
  printf("LastCard es: %s\n", lastcard);
  while (i<108){
    aux1=ObtenerCarta(i,Jugador);
    strcpy(mano,aux1);
    if(strcmp(mano,lastmano)==0) break;
    aux2=ObtenerCarta(i,Jugador);
    strcpy(lastmano,aux2);
    i++;
    if (Jugable(mano, lastcard) == 0){
       jugables++;
    }
    printf("%d. %s\n", i, mano);
  }
  if(jugables==0){
    printf("No posees cartas jugables\n");
    RobarCarta(Jugador, lastcard,0);
    repartidas++;
    aux=ObtenerCarta(0,"LastCard");
    printf("El tope es: %s\n", aux);
    return 1;
  }
  else {
    printf("Posees %d cartas jugables\n", jugables);
    while(flag==0){
      printf("Elija una carta: ");
      scanf("%i", &decision);
      aux1=ObtenerCarta(decision-1,Jugador);
      if(Jugable(aux1,lastcard)==0){
        printf("Carta valida\n");
        flag=1;
        JugarCarta(Jugador, aux1, lastcard);
        if((i-1)==1){
          printf("UNO!!\n");
        }
        if((i-1)==0) return 0;
        aux=ObtenerCarta(0,"LastCard");
        printf("El tope es: %s\n", aux);
      }
      else{
        printf("Carta invalida elegir otra\n");
      }
    }
    return 1;
  }
}




int main(){
  int turn=1;
  CrearCarpetas();
  CrearMazo("./Mazo");
  Repartir();
  while(turn==1){
    printf("Turno Jugador1: \n");
    turn=Turno("Jugador1");
    printf("Turno Jugador2: \n");
    turn=Turno("Jugador2");
    printf("Turno Jugador3: \n");
    turn=Turno("Jugador3");
    printf("Turno Jugador4: \n");
    turn=Turno("Jugador4");
}

}
