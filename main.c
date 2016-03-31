#include <stdio.h>
#include "bibfis.h"
#include "nave.h"
#include "planeta.h"
#include "projetil.h"
#define TAM 255

int main() {
	double tp, mp, t_simul; //tamanho_planeta massa_planeta tempo_simulação
	double m1, posx1, posy1, velx1, vely1; // massa1 pos_x1 pos_y1 vel_x1 vel_y1
	char nome1[TAM], nome2[TAM];
	double m2, posx2, posy2, velx2, vely2; // massa2 pos_x2 pos_y2 vel_x2 vel_y2
	double num_proj, temp_vida; // num_proj tempo_vida
	double m_proj1, posx_proj1, posy_proj1, velx_proj1, vely_proj1; // massa_proj1 posx_proj1 posy_proj1 velx_proj1 vely_proj1
	planeta plan;
	nave n1,n2;
	projetil proj1;
	int i = 10;
	
	printf("\n Primeira linha: Global \n");
	scanf("%lf %lf %lf",&tp, &mp, &t_simul);

	printf("\n Segunda linha: Nave 1 \n");
	scanf("%s %lf %lf %lf %lf %lf",&nome1[0], &m1, &posx1, &posy1, &velx1, &vely1);

	printf("\n Terceira linha: Nave 2 \n");
	scanf("%s %lf %lf %lf %lf %lf",&nome2[0], &m2, &posx2, &posy2, &velx2, &vely2);

	printf("\n Quarta linha: Projéteis \n");
	scanf("%lf %lf",&num_proj, &temp_vida);
	
	printf("\n Quinta linha: Projetil \n");
	scanf("%lf %lf %lf %lf %lf", &m_proj1, &posx_proj1, &posy_proj1, &velx_proj1, &vely_proj1);

/* Usei pra testes
	tp = 10;
	mp = 20000000;
	t_simul = 30;
	
	nome1 = "andrei";
	m1 = 7000000;
	posx1 = 1;
	posy1 = 2;
	velx1 = 0;
	vely1 = 0;

	nome2 = "b";
	m2 = 8000000;
	posx2 = 5;
	posy2 = 5;
	velx2 = 0;
	vely2 = 0;

	num_proj = 1;
	temp_vida = 20;
	
	m_proj1 = 500;
	posx_proj1 = 1;
	posy_proj1 = 3;
	velx_proj1 = 0;
	vely_proj1 = 0;
*/

	//Criação planeta
	plan = novo_planeta(mp,tp);

	//Criação das naves
	n1 = nova_nave(nome1, m1,posx1,posy1,velx1,vely1);
	n2 = nova_nave(nome2, m2,posx2,posy2,velx2,vely2);

	//Criação dos projéteis
	proj1 = novo_projetil(m_proj1,posx_proj1,posy_proj1,velx_proj1,vely_proj1);

	//Faremos 10 iterações
	while(i>0) {

		
		forca fan,fan_res,fan1_plan,fan2_plan,fan1_res,fan2_res; //fan(força de atração naves); _res (resultante); 1(nave1)

		//Atração entre as naves
		fan = atracao_nave(n1,n2->x,n2->y,n2->massa); 

		//Resultante de cada em relação ao planeta
		fan1_plan = atracao_planeta(plan,n1->x,n1->y,n1->massa);
		fan2_plan = atracao_planeta(plan,n2->x,n2->y,n2->massa);

		//Resultantes
		fan1_res = resultante(fan_res,fan);
		fan2_res = resultante(fan_res,fan);

		//Mover as naves
		empurra_nave(n1,fan1_res,t_simul);
		empurra_nave(n2,fan2_res,t_simul);
	
		//Atualizar naves
		atualiza_nave(n1,t_simul);
		atualiza_nave(n2,t_simul);
	
		printf("\n Iteracao numero: %d ",i);
		printf("\n Nave 1: %s ",n1->nome);
		printf("\n Massa: %f \n Posx1: %f \n Posy1: %f \n velX1: %f \n velY1: %f \n", n1->massa,n1->x,n1->y,n1->velx,n1->vely);

		printf("\n Nave 2: %s ",n2->nome);
		printf("\n Massa: %f \n Posx2: %f \n Posy2: %f \n velX2: %f \n velY2: %f \n", n2->massa,n2->x,n2->y,n2->velx,n2->vely);
	
		i--;
	}

	return 0;

}
