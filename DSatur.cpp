#include<stdio.h>
#include<stdlib.h>
#include <time.h>
//Creamos la matriz que representa el grafo
int **graph=NULL;
int *colored=NULL;
int colors=1;
int num=0;

int getNodeGrade(int index);
int getMaxGradeNode();
bool isColored(int index);
void setColor(int index);
int getSaturation(int index);
int getMaxSaturation();

int main(int argc, char const *argv[])
{
	//Creamos un puntero de tipo FILE
	FILE *fp;
	//Abrimos el archivo a leer
 	if((fp = fopen ("graphs/tam.txt", "r" ))==NULL){
 		printf("No se pudo leer el archivo\n");
 		return 0;
 	}
	//leemos los datos
 	fscanf(fp, "%d" ,&num);
  colored= (int*)malloc(num*sizeof(int*));
 	graph = (int**)malloc(num*sizeof(int*));
	// Columnas
	for(int i=0;i<num;i++){
		graph[i] = (int*)malloc(num*sizeof(int));
		// Inicializar la matriz en ceros
		for(int j=0;j<num;j++){
			graph[i][j]=0;
		}
    colored[i]=0;
	}

  int a,b;
 	//Leemos las aristas de cada vertice
 	while(feof(fp)==0){
 		fscanf(fp,"%d %d",&a,&b);
 		graph[a-1][b-1]=1;
    graph[b-1][a-1]=1;
 	}

 	//Imprimimos el grafo
 	for(int i = 0; i < num; i++){
 		for (int j = 0; j < num; ++j)
 			printf("%d ",graph[i][j]);
    printf("\n");
 	}
	clock_t ti, tf;
  ti = clock();//Comienza a medir el tiempo
  //Algoritmo DSatur
  //1. Seleccionar el nodo inicial (nodo con mayor grado)
  int actNode=getMaxGradeNode();
  //2. Asignar el color de menor grado al nodo
  setColor(actNode);
  printf("Nodo Actual: %d Color: %d\n",actNode,colored[actNode]);
  int visited=1;
  //3. Iterar hasta colorearlos todos
  while (visited<num) {
  /*
  4. Seleccionar el nodo no coloreado con
     el mayor indice de saturacion, en caso
     de un empate, tomar el de mayor grado
  */
    actNode=getMaxSaturation();
    //5. Asignar color
    setColor(actNode);
    printf("Nodo Actual: %d Color: %d\n",actNode,colored[actNode]);
    //6. Marcarlo como visitado
    visited++;
  }
	tf = clock();//Termina de medir el tiempo
  printf("Numero minimo de colores: %d\n",colors);
	double segundos = (double)(tf - ti) / CLOCKS_PER_SEC;
	printf("\nTiempo de ejecucion: %lf Segundos\n",segundos);
	free(fp);
	free(graph);
	free(colored);
	return 0;
}
//obtiene el grado de un nodo
int getNodeGrade(int index){
  int grade=0;
  for(int i=0;i<num;i++){
    if(graph[index][i]!=0)
      grade++;
  }
  return grade;
}
//Verfica si un nodo esta coloreado
bool isColored(int index){
  if(colored[index]!=0)
    return true;
  else
    return false;
}
//obtiene el nodo no coloreado con mayor grado
int getMaxGradeNode(){
  int max=0; int index=0;
  for(int i=0;i<num;i++){
    int aux=getNodeGrade(i);
    if(!isColored(i)&&aux>max){
        max=aux;
        index=i;
    }
  }
  return index;
}
//Asiga el color a un nodo
void setColor(int index){
  bool flag=true;
  int colorIndex=1;
  while(flag){
    int count=0;
    for(int i=0;i<num;i++){
      if(graph[index][i]==1 && colored[i]==colorIndex)
        count++;
    }
    if(count==0){
      flag=false;
    }else{
      colorIndex++;
    }
  }
  colored[index]=colorIndex;
  if(colorIndex>colors)
    colors=colorIndex;
}
//Obtiene el grado de saturacion de un nodo
int getSaturation(int index){
  int count=0;
  for(int i=1;i<=colors;i++){
    for(int j=0;j<num;j++){
      if(graph[index][j]==1 && colored[j]==i){
        count++;
        j=num;
      }
    }
  }
  return count;
}
int getMaxSaturation(){
  int maxSat=0; int index=0;
  for(int i=0;i<num;i++){
    if(colored[i]==0){
      int aux=getSaturation(i);
      if(aux > maxSat){
        maxSat=aux;
        index=i;
      }else if(aux==maxSat){
        if(getNodeGrade(i)>getNodeGrade(index))
          index=i;
      }
    }
  }
  return index;
}
