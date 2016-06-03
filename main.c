#include <stdio.h>
#include <unistd.h>
#include "xwc.h"
#include "bibfis.h"
#include "nave.h"
#include "planeta.h"
#include "projetil.h"
#define TAM 256

void imprime (nave n1, nave n2, projetil* pjs, int psz) {
    int i;

    printf("Nave 1: (%s)\n",n1->nome);
    printf("Massa: %2.4f Pos_x1: %2.4f Pos_y1: %2.4f Vel_x1: %2.4f Vel_y1: %2.4f\n", n1->massa,n1->x,n1->y,n1->velx,n1->vely);

    printf("Nave 2: (%s)\n",n2->nome);
    printf("Massa: %2.4f Pos_x2: %2.4f Pos_y2: %2.4f Vel_x2: %2.4f Vel_y2: %2.4f\n", n2->massa,n2->x,n2->y,n2->velx,n2->vely);

    for (i = 0; i < psz; i++) {
        printf("Projetil %d: ", i);
        printf("Massa: %2.4f Pos_xp: %2.4f Pos_yp: %2.4f Vel_xp: %2.4f Vel_yp: %2.4f\n", pjs[i]->massa, pjs[i]->x, pjs[i]->y, pjs[i]->velx, pjs[i]->vely);
    }

    printf ("\n");
}

int main(int argc, char* argv[]) {
    double tp, mp, passo, t_simul; //tamanho_planeta massa_planeta tempo_simulação
    char nome1[TAM], nome2[TAM]; //Nome dos planetas
    double m1, posx1, posy1, velx1, vely1; //massa1 pos_x1 pos_y1 vel_x1 vel_y1
    double m2, posx2, posy2, velx2, vely2; //massa2 pos_x2 pos_y2 vel_x2 vel_y2
    double temp_vida; //tempo_vida
    double m_proj, posx_proj, posy_proj, velx_proj, vely_proj,inc;	//Pros projeteis
    int i, j, k, num_proj; //i, j, k contadores numero_projeteis
    planeta plan; //planeta
    nave n1, n2; //naves
    projetil projeteis[TAM]; //lista de projeteis
	PIC MAPA, todo;	//NOVO
	MASK mbum, load_mask[TAM];
    WINDOW* w1;
    
    //Para testar rotação - Podem excluir depois
    int aux_inc_1, aux_inc_2=0;
    int num_inc_1,num_inc_2;
    double inc_nave_1[TAM], inc_nave_2[TAM];
	//Até aqui.
	
	//Para loading
	PIC loading[TAM];
	int cont_load = 0;
	

	printf("\n Aqui");

    if (argc < 2) {
        fprintf (stderr, "FALTA PARÂMETRO: dt\n");
        return 1;
    }
    
    printf("\n Saiu");

	w1 = InitGraph(800, 600, "Jogo");

	loading[0] = ReadPic(w1, "imagens/loading/loading-0.xpm", NULL);
    PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	loading[1] = ReadPic(w1, "imagens/loading/loading-1.xpm", NULL);
	PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	loading[2] = ReadPic(w1, "imagens/loading/loading-2.xpm", NULL);
	PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	loading[3] = ReadPic(w1, "imagens/loading/loading-3.xpm", NULL);
	PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	loading[4] = ReadPic(w1, "imagens/loading/loading-4.xpm", NULL);
	PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	loading[5] = ReadPic(w1, "imagens/loading/loading-5.xpm", NULL);
	PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	loading[6] = ReadPic(w1, "imagens/loading/loading-6.xpm", NULL);
	PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	loading[7] = ReadPic(w1, "imagens/loading/loading-7.xpm", NULL);
	PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	loading[8] = ReadPic(w1, "imagens/loading/loading-8.xpm", NULL);
	PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
	
    inc = 0;
	//MAPA = ReadPic(w1, "imagens/oficial-plan.xpm", NULL);
	MAPA = ReadPic(w1, "imagens/cenario.xpm", NULL);
	//PutPic(w1, MAPA, 0, 0, 800, 600, 0, 0);

    //PutPic(w1, bum, 0, 0, 800, 600, 50, 50);
	
    sscanf(argv[1], "%lf", &passo);
    scanf("%lf %lf %lf\n", &tp, &mp, &t_simul);
    scanf("%s %lf %lf %lf %lf %lf\n", nome1, &m1, &posx1, &posy1, &velx1, &vely1);
    scanf("%s %lf %lf %lf %lf %lf\n", nome2, &m2, &posx2, &posy2, &velx2, &vely2);
    scanf("%d %lf\n", &num_proj, &temp_vida);

    //Criação de todos os num_proj projeteis.
    for(i = 0; i < num_proj; i++) {
        scanf("%lf %lf %lf %lf %lf %lf \n", &m_proj, &posx_proj, &posy_proj, &velx_proj, &vely_proj, &inc); //agora lê a inclinação também.
        projeteis[i] = novo_projetil(m_proj, posx_proj, posy_proj, velx_proj, vely_proj, temp_vida, inc, w1);
        if(cont_load == 9) cont_load = 0;
        PutPic(w1,loading[cont_load],0,0,800,600,0,0); cont_load++;
    }
    
    //testando inclinação das naves - também pode ser excluido posteriormente.
    scanf("%d %d\n", &num_inc_1, &num_inc_2);
    
    for(i = 0; i < num_inc_1; i++) {
        scanf("%lf \n", &inc_nave_1[i]);
    }
    
    for(i = 0; i < num_inc_2; i++) {
        scanf("%lf \n", &inc_nave_2[i]);
    }
	//Até aqui.
    
    
    //--------------------------Termino da leitura do aquivo -----------------------------

    //Criação planeta
    plan = novo_planeta(mp, tp);
	
    //Criação das naves
    n1 = nova_nave(nome1, m1, posx1, posy1, velx1, vely1, w1,1,0);
    n2 = nova_nave(nome2, m2, posx2, posy2, velx2, vely2, w1,2,0);

    forca fan, fan1_plan, fan2_plan, fan1_res, fan2_res, fap, fap_res; //fan(força de atração naves); _res (resultante); 1(nave1)
	PutPic(w1, MAPA, 0, 0, 800, 600, 0, 0);
    // Imprimir estado inicial
    //printf("Estado inicial\n");
    //imprime(n1, n2, projeteis, num_proj);

    double tempo = 0;
    k = 0;
    while (tempo < t_simul) {
        //Atração entre as naves
        fan = atracao_nave(n1, n2->x, n2->y, n2->massa);

        //Resultante de cada em relação ao planeta
        fan1_plan = atracao_planeta(plan, n1->x, n1->y, n1->massa);
        fan2_plan = atracao_planeta(plan, n2->x, n2->y, n2->massa);

        //Resultantes
        fan1_res = resultante(fan1_plan, fan);
        fan2_res = resultante(fan2_plan, fan);

        //Mover as naves
        empurra_nave(n1, fan1_res, passo);
        empurra_nave(n2, fan2_res, passo);

        //Atualizar naves
        atualiza_nave(n1, passo);
        if (aux_inc_1 < num_inc_1) n1->inc = inc_nave_1[aux_inc_1] / 22.30;
        atualiza_nave(n2, passo);
        if (aux_inc_2 < num_inc_2) n2->inc = inc_nave_2[aux_inc_2] / 22.30;

        //Atracao dos projeteis
        for (i = 0; i < num_proj; i++) {
            if (projeteis[i]->morto) continue;
            //Atracao entre projetil i e planeta
            fap_res = atracao_planeta(plan, projeteis[i]->x, projeteis[i]->y, projeteis[i]->massa);

            //Atracao entre projetil i e outros projeteis
            for (j = 0; j < num_proj; j++) {
                if (i == j) continue;
                fap = atracao_projetil(projeteis[j], projeteis[i]->x, projeteis[i]->y, projeteis[i]->massa);
                fap_res = resultante(fap_res, fap);
            }

            //Atracao entre projetil i e naves
            fap = atracao_nave(n1, projeteis[i]->x, projeteis[i]->y, projeteis[i]->massa);
            fap_res = resultante(fap_res, fap);
            fap = atracao_nave(n2, projeteis[i]->x, projeteis[i]->y, projeteis[i]->massa);
            fap_res = resultante(fap_res, fap);

            //empurra_projetil
            empurra_projetil(projeteis[i], fap_res, passo);

            //atualiza projetil
            atualiza_projetil(projeteis[i], passo);
        }

		PutPic(w1, MAPA, 0, 0, 800, 600, 0, 0);
        todo = NewPic(w1, 800, 600);
        imprime_nave(n1, w1, todo);
        imprime_nave(n2, w1, todo);
		for (i = 0; i < num_proj; i++) {
            if (!projeteis[i]->morto)
                imprime_projetil(projeteis[i], w1, todo);
		}
		
		usleep(100000);
		WClear(w1);
		FreePic(todo);
		UnSetMask(w1);
		PutPic(w1, MAPA, 0, 0, 800, 600, 0, 0);

        //printf("Iteracao numero: %d\n",k);
        //imprime(n1, n2, projeteis, num_proj);

        tempo += passo;
        k++;
		aux_inc_1++;
		aux_inc_2++;
    }

    usleep(1000000000);

    destroi_nave(n1);
    destroi_nave(n2);
    destroi_planeta(plan);
    for (i = 0; i < num_proj; i++) destroi_projetil(projeteis[i]);

    return 0;
}
