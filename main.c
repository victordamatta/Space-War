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
    double m_proj, posx_proj, posy_proj, velx_proj, vely_proj;	//Pros projeteis
    int i, j, k, num_proj, inc; //i, j, k contadores numero_projeteis
    planeta plan; //planeta
    nave n1, n2; //naves
    projetil projeteis[TAM]; //lista de projeteis
	PIC MAPA, todo;	//NOVO
    WINDOW* w1;

    if (argc < 2) {
        fprintf (stderr, "FALTA PARÂMETRO: dt\n");
        return 1;
    }

    //NOVO
	w1 = InitGraph(800, 600, "Jogo");
    inc = 0;
	MAPA = ReadPic(w1, "imagens/oficial-plan.xpm", NULL);
	PutPic(w1, MAPA, 0, 0, 800, 600, 0, 0);

    sscanf(argv[1], "%lf", &passo);
    scanf("%lf %lf %lf\n", &tp, &mp, &t_simul);
    scanf("%s %lf %lf %lf %lf %lf\n", nome1, &m1, &posx1, &posy1, &velx1, &vely1);
    scanf("%s %lf %lf %lf %lf %lf\n", nome2, &m2, &posx2, &posy2, &velx2, &vely2);
    scanf("%d %lf\n", &num_proj, &temp_vida);

    //Criação de todos os num_proj projeteis.
    for(i = 0; i < num_proj; i++) {
        scanf("%lf %lf %lf %lf %lf %d\n", &m_proj, &posx_proj, &posy_proj, &velx_proj, &vely_proj, &inc);
        projeteis[i] = novo_projetil(m_proj, posx_proj, posy_proj, velx_proj, vely_proj, temp_vida, inc, w1);
    }

    //--------------------------Termino da leitura do aquivo -----------------------------

    //Criação planeta
    plan = novo_planeta(mp, tp);

    //Criação das naves
    n1 = nova_nave(nome1, m1, posx1, posy1, velx1, vely1);
    n2 = nova_nave(nome2, m2, posx2, posy2, velx2, vely2);

    forca fan, fan1_plan, fan2_plan, fan1_res, fan2_res, fap, fap_res; //fan(força de atração naves); _res (resultante); 1(nave1)

    // Imprimir estado inicial
    printf("Estado inicial\n");
    imprime(n1, n2, projeteis, num_proj);

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
        atualiza_nave(n2, passo);

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

        //NOVO
		PutPic(w1, MAPA, 0, 0, 800, 600, 0, 0);
        todo = NewPic(w1, 800, 600);
		for (i = 0; i < num_proj; i++) {
			imprime_projetil(projeteis[i], w1, todo);
		}
		usleep(100000);
		WClear(w1);
		FreePic(todo);
		UnSetMask(w1);
		PutPic(w1, MAPA, 0, 0, 800, 600, 0, 0);

        printf("Iteracao numero: %d\n",k);
        imprime(n1, n2, projeteis, num_proj);

        tempo += passo;
        k++;
    }

    destroi_nave(n1);
    destroi_nave(n2);
    destroi_planeta(plan);
    for (i = 0; i < num_proj; i++) destroi_projetil(projeteis[i]);

    return 0;
}
