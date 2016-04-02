#include <stdio.h>
#include "bibfis.h"
#include "nave.h"
#include "planeta.h"
#include "projetil.h"
#define TAM 255

int main() {
	
	char url[]="exemplo.txt"; // leitura do arquivo
	double tp, mp, t_simul; //tamanho_planeta massa_planeta tempo_simulação
	double m1, posx1, posy1, velx1, vely1; // massa1 pos_x1 pos_y1 vel_x1 vel_y1
	char nome1[TAM], nome2[TAM]; //Nome dos planetas
	double m2, posx2, posy2, velx2, vely2; // massa2 pos_x2 pos_y2 vel_x2 vel_y2
	double num_proj, temp_vida; // num_proj tempo_vida
	double m_proj, posx_proj, posy_proj, velx_proj, vely_proj;	// Pros projeteis (tem que ser generico)
	int tam_nome1 = 0,tam_nome2 = 0; //Tamanho dos nomes
	int i, j, k; // i e j contadores
	double aux; //Auxiliar em laços
	char ch; // Auxiliar com caracteres
	planeta plan; //planeta
	nave n1,n2; //naves
	projetil lista_projeteis[TAM]; // lista de projeteis

	//Leitura do arquivo .txt
	FILE *arq;
	
	arq = fopen(url, "r");
	if(arq == NULL) {
			printf("Erro, nao foi possivel abrir o arquivo\n");
			return 0;
	}
	
	fscanf(arq,"%lf %lf %lf\n", &tp, &mp, &t_simul);

	// Aqui vou verificando o que é inserido no nome e contabilizando, pra ter o tamanho do nome.
	while((ch =fgetc(arq))!= ' '){
		tam_nome1++;
	}		
		
	fseek(arq,tam_nome1*(-1) - 1,SEEK_CUR); // Mas como nao armazenei o nome, faço o cursor retornar pra 1 posição antes do nome

	fscanf(arq,"%s %lf %lf %lf %lf %lf\n", &nome1[0], &m1, &posx1, &posy1, &velx1, &vely1);

	// O mesmo pro nome2
	while((ch =fgetc(arq))!= ' '){
		tam_nome2++;
	}		
	
	fseek(arq,tam_nome2*(-1) - 1,SEEK_CUR);
	fscanf(arq,"%s %lf %lf %lf %lf %lf\n", &nome2[0], &m2, &posx2, &posy2, &velx2, &vely2);
		
	// Lendo informaçoes dos projéteis. Irei ter que já criá-los.	
	fscanf(arq,"%lf %lf\n", &num_proj, &temp_vida);

	//Criação de todos os num_proj projeteis.
	i=0;		
	aux = num_proj;
	while (aux > 0) {
		fscanf(arq,"%lf %lf %lf %lf %lf\n", &m_proj, &posx_proj, &posy_proj, &velx_proj, &vely_proj);		
		lista_projeteis[i] = novo_projetil(m_proj,posx_proj,posy_proj,velx_proj,vely_proj);
		i++;
		aux--;
	}

	fclose(arq);

	//---------------------------------------Termino da leitura do aquivo ---------------------------------------

	//Criação planeta
	plan = novo_planeta(mp,tp);

	//Criação das naves
	n1 = nova_nave(nome1, m1,posx1,posy1,velx1,vely1);
	n2 = nova_nave(nome2, m2,posx2,posy2,velx2,vely2);

	forca fan,fan1_plan,fan2_plan,fan1_res,fan2_res,fap,fap_res; //fan(força de atração naves); _res (resultante); 1(nave1)
	
	// Imprimir estado inicial
	printf("\n Estado incial");
	printf("\n Nave 1:	");
	printf("(%s)",n1->nome);
	printf(" Massa: %2.4f Pos_x1: %2.4f Pos_y1: %2.4f Vel_x1: %2.4f Vel_y1: %2.4f \n", n1->massa,n1->x,n1->y,n1->velx,n1->vely);

	printf("\n Nave 2:	");
	printf("(%s)",n2->nome);
	printf(" Massa: %2.4f Pos_x2: %2.4f Pos_y2: %2.4f Vel_x2: %2.4f Vel_y2: %2.4f \n\n", n2->massa,n2->x,n2->y,n2->velx,n2->vely);

	aux = num_proj;
	j=0;
	while (aux > 0){
		printf(" Projetil %d: ",j);
		printf(" Massa: %2.4f Pos_x2: %2.4f Pos_y2: %2.4f Vel_x2: %2.4f Vel_y2: %2.4f \n", lista_projeteis[j]->massa, lista_projeteis[j]->x, 	lista_projeteis[j]->y, lista_projeteis[j]->velx, lista_projeteis[j]->vely);
		aux--;
		j++;
	}

	//Faremos 10 iterações
	i=10;
	k=0;
	while(i>0) {

		//Atração entre as naves
		fan = atracao_nave(n1,n2->x,n2->y,n2->massa); 

		//Resultante de cada em relação ao planeta
		fan1_plan = atracao_planeta(plan,n1->x,n1->y,n1->massa);
		fan2_plan = atracao_planeta(plan,n2->x,n2->y,n2->massa);

		//Resultantes
		fan1_res = resultante(fan1_plan,fan);
		fan2_res = resultante(fan2_plan,fan);

		//Mover as naves
		empurra_nave(n1,fan1_res,t_simul);
		empurra_nave(n2,fan2_res,t_simul);
	
		//Atualizar naves
		atualiza_nave(n1,t_simul);
		atualiza_nave(n2,t_simul);
		
		printf("\n Iteracao numero: %d \n",k);
		printf("\n Nave 1:	");
		printf("(%s)",n1->nome);
		printf(" Massa: %2.4f Pos_x1: %2.4f Pos_y1: %2.4f Vel_x1: %2.4f Vel_y1: %2.4f \n", n1->massa,n1->x,n1->y,n1->velx,n1->vely);

		printf("\n Nave 2:	");
		printf("(%s)",n2->nome);
		printf(" Massa: %2.4f Pos_x2: %2.4f Pos_y2: %2.4f Vel_x2: %2.4f Vel_y2: %2.4f \n\n", n2->massa,n2->x,n2->y,n2->velx,n2->vely);

		//Atracao dos projeteis
		aux = num_proj;
		j=0;
		while (aux > 0){
			// Atracao entre projetil i e planeta
			fap = atracao_planeta(plan,lista_projeteis[j]->x,lista_projeteis[j]->y,lista_projeteis[j]->massa);			
			
			//Resultante é a própria atracao_planeta pois só ela está agindo.
		
			//empurra_projetil
			empurra_projetil(lista_projeteis[j],fap,t_simul);
			//atualiza projetil
			atualiza_projetil(lista_projeteis[j],t_simul);

			printf(" Projetil %d: ",j);
			printf(" Massa: %2.4f Pos_x2: %2.4f Pos_y2: %2.4f Vel_x2: %2.4f Vel_y2: %2.4f \n", lista_projeteis[j]->massa, lista_projeteis[j]->x, 	lista_projeteis[j]->y, lista_projeteis[j]->velx, lista_projeteis[j]->vely);
			aux--;
			j++;
		}
	
		i--;
		k++;	
	
	}


	return 0;

}
