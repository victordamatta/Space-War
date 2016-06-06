#include <stdio.h>
#include <unistd.h>
#include "xwc.h"
#include "bibfis.h"
#include "graficos.h"
#include "planeta.h"
#include "projetil.h"
#include "nave.h"
#define TAM 1000000
#define NOME_TAM 256

void debug (nave n1, nave n2, projetil* pjs, int psz) {
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
    char nome1[NOME_TAM], nome2[NOME_TAM]; //Nome dos planetas
    double m1, posx1, posy1, velx1, vely1; //massa1 pos_x1 pos_y1 vel_x1 vel_y1
    double m2, posx2, posy2, velx2, vely2; //massa2 pos_x2 pos_y2 vel_x2 vel_y2
    double temp_vida; //tempo_vida
    int i, j, k, num_proj, perdeu1, perdeu2; //i, j, k contadores numero_projeteis, indicadores se a nave perdeu ou não
    planeta plan; //planeta
    nave n1, n2; //naves
    projetil projeteis[TAM]; //lista de projeteis
	PIC MAPA, mascara_proj, pic_proj;
    WINDOW* w1;

    if (argc < 2) {
        fprintf (stderr, "FALTA PARÂMETRO: dt\n");
        return 1;
    }

	w1 = InitGraph(WIDTH, HEIGHT, "Jogo");
	MAPA = ReadPic(w1, "imagens/cenario.xpm", NULL);
    InitKBD(w1);

    /*
	PIC loading[10];
	int cont_load = 0;

    char sel[] = "imagens/loading/loading-0.xpm";
    for (i = 0; i < 8; i++) {
        sel[24] = i + 48;
        loading[i] = ReadPic(w1, sel, NULL);
        PutPic(w1, loading[cont_load], 0, 0, WIDTH, HEIGHT, 0, 0);
        cont_load = (cont_load + 1) % 8;
    }
    */

    sscanf(argv[1], "%lf", &passo);
    scanf("%lf %lf %lf\n", &tp, &mp, &t_simul);
    scanf("%s %lf %lf %lf %lf %lf\n", nome1, &m1, &posx1, &posy1, &velx1, &vely1);
    scanf("%s %lf %lf %lf %lf %lf\n", nome2, &m2, &posx2, &posy2, &velx2, &vely2);
    scanf("%d %lf\n", &num_proj, &temp_vida);

    //--------------------------Termino da leitura do aquivo -----------------------------

    num_proj = 0;
    perdeu1 = 0;
    perdeu2 = 0;

    //Criação planeta
    plan = novo_planeta(mp, tp);

    //Criação das naves
    n1 = nova_nave(nome1, m1, posx1, posy1, velx1, vely1, w1, 1, 0);
    n2 = nova_nave(nome2, m2, posx2, posy2, velx2, vely2, w1, 2, 8);

    mascara_proj = NewMask (MAPA, 32, 32);
    pic_proj = ReadPic (w1, "imagens/projeteis/projetil.xpm", mascara_proj);

    forca fan, fan1_plan, fan2_plan, fan1_res, fan2_res, fap, fap_res; //fan(força de atração naves); _res (resultante); 1(nave1)
	PutPic(w1, MAPA, 0, 0, WIDTH, HEIGHT, 0, 0);

    double tempo = 0;
    k = 0;
    while (tempo < t_simul) {
        //Deteccao de colisao
        if (colisao (n1, n2->x, n2->y, NAVE_RAIO)){
            perdeu1 = 1;
            perdeu2 = 1;
        }
        if (colisao (n1, 0, 0, PLANETA_RAIO)) perdeu1 = 1;
        if (colisao (n2, 0, 0, PLANETA_RAIO)) perdeu2 = 1;
        for (i = 0; i < num_proj; i++) {
            if (projeteis[i]->morto) continue;
            if (colisao (n1, projeteis[i]->x, projeteis[i]->y, 0)) perdeu1 = 1;
            if (colisao (n2, projeteis[i]->x, projeteis[i]->y, 0)) perdeu2 = 1;
        }

        //Game Over
        if (perdeu1 && perdeu2) {
            printf ("Empate!\n");
            return 0;
        }
        else if (perdeu1) {
            printf ("%s ganhou (Azul)!\n", n2->nome);
            return 0;
        }
        else if (perdeu2) {
            printf ("%s ganhou (Vermelho)!\n", n1->nome);
            return 0;
        }

        //Input do teclado
        while (WCheckKBD (w1)) {
            int k = WGetKey (w1);
            if (k == 25) {
                componentes comp = decomposicao (NAVE_VELOCIDADE, n1->inc);
                n1->velx += comp.x;
                n1->vely += comp.y;
            }
            else if (k == 38) {
                rotaciona_nave (n1, -1);
            }
            else if (k == 39) {
                projeteis[num_proj++] = atira (n1, mascara_proj, pic_proj);
            }
            else if (k == 40) {
                rotaciona_nave (n1, 1);
            }
            else if (k == 111) {
                componentes comp = decomposicao (NAVE_VELOCIDADE, n2->inc);
                n2->velx += comp.x;
                n2->vely += comp.y;
            }
            else if (k == 113) {
                rotaciona_nave (n2, -1);
            }
            else if (k == 116) {
                projeteis[num_proj++] = atira (n2, mascara_proj, pic_proj);
            }
            else if (k == 114) {
                rotaciona_nave (n2, 1);
            }
        }


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
                if (projeteis[i]->morto) continue;
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

            double dist = amplia_distancia (PLANETA_RAIO);
            if (projeteis[i]->x * projeteis[i]->x + projeteis[i]->y * projeteis[i]->y < dist * dist)
                projeteis[i]->morto = 1;
        }

        //Fase de impressao
        PutPic(w1, MAPA, 0, 0, WIDTH, HEIGHT, 0, 0);

        imprime_nave(n1, w1);
        imprime_nave(n2, w1);
        for (i = 0; i < num_proj; i++) {
            if (!projeteis[i]->morto) imprime_projetil(projeteis[i], w1);
        }

        tempo += passo;
        k++;

        usleep(100000);

        WClear(w1);
    }

    destroi_nave(n1);
    destroi_nave(n2);
    destroi_planeta(plan);
    for (i = 0; i < num_proj; i++) destroi_projetil(projeteis[i]);
    FreePic (w1);

    printf ("Empate - falta de tempo\n");
    return 0;
}
