#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdint.h>
#include <time.h>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

/*
  Code is writed by GynvaelColdwind (Yt: https://www.youtube.com/channel/UCjS2aGCvsnhExcWRAI8T4Pw )
  All thx to him, me just edited some things for my own use

  Do zmodyfikowania:
  - Dodać możliwość kontynuacji
  - Wprowadzanie danych parametrem
  - Może rozbić to na drobniejsze?
  -naprawić ten śmieszny bug z sprintf

*/

const sizr_t dumpingSpeed = 50; //50 is fine

const size_t W = 256;
const size_t H = 256;
const std::string pName = "sad.raw";
//sad: 256, 256
//bear: 500, 500
//small-bear: 350, 350 (70% z 500)
const size_t SZ = W * H;

uint8_t monalisa[SZ];

const size_t SPEC_CNT = 300;
const size_t BEST_CNT = 2;

uint8_t specimen[SPEC_CNT][SZ];
size_t best_spec[BEST_CNT][SZ];
size_t best[BEST_CNT];
int step = 0;

bool filexists(const char *filename) {
  std::ifstream ifile(filename);
  return (bool)ifile;
}

bool filexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}

bool direxists(const std::string& filename) {
  struct stat buffer;
  return ( stat(filename.c_str(), &buffer ) == 0);
}

void dump_best() {
  if (step % dumpingSpeed != 0 || step == 1) {
    return;
  }

  printf("   Dumping step %i\r", step); fflush(stdout);
  for (size_t i = 0; i < 1; i++) {
    char fname[256] = {0};
    sprintf(fname, "out\\bearst_%.6i_%.2i.raw", step, i);
    FILE *f = fopen(fname, "wb");
    fwrite(specimen[best[i]], SZ, 1, f);
    fclose(f);
  }
}

void mutate() {
  for (size_t i = 0; i < SPEC_CNT; i++) {
    int x = rand() % (W - 1);
    int y = rand() % (H - 1);
    int w = rand() % (((W - x - 1) / 6) + 1) + 1;
    int h = rand() % (((H - y - 1) / 6) +1) + 1;
    int c = rand() & 0xff;

    for (int n = y; n < y + h; n++) {
      for (int m = x; m < x + w; m++) {
        specimen[i][n * W + m] =
          (specimen[i][n * W + m] + c) >> 1;
      }
    }
  }
}

double score_me(uint8_t *sp) {
  double sc = 0.0;
  for (size_t j = 0; j < H; j++) {
    for (size_t i = 0; i < W; i++) {
      double a = sp[j * W + i];
      double b = monalisa[j * W + i];
      sc += (a - b) * (a - b);
    }
  }

  return sc;
}

struct scores_st {
  double score;
  size_t idx;
};

int score_sort_fnc(const void *a, const void *b) {
  const scores_st *sa = (const scores_st*)a;
  const scores_st *sb = (const scores_st*)b;  

  if (sa->score > sb->score) {
    return 1;
  }

  if (sa->score < sb->score) {
    return -1;
  }  

  return 0;
}

void score() {
  static scores_st scores[SPEC_CNT];

  for (size_t i = 0; i < SPEC_CNT; i++) {
    scores[i].idx = i;
    scores[i].score = score_me(specimen[i]);
  }

  qsort(scores, SPEC_CNT, sizeof(scores_st), score_sort_fnc);

  for (size_t i = 0; i < BEST_CNT; i++) {
    best[i] = scores[i].idx;
    //printf("%i %i %f\n", i, best[i], scores[i].score);
  }
}

void cross() {
  for (size_t i = 0; i < BEST_CNT; i++) {
    memcpy(best_spec[i], specimen[best[i]], SZ);
  }

  for (size_t i = BEST_CNT; i < SPEC_CNT; i++) {
    memcpy(specimen[i], best_spec[i % BEST_CNT], SZ);
  }
}

int main(void) {
  srand(time(NULL));


  if(!filexists(pName.c_str())) {
    puts("Błąd! Plik źródłowy nie istnieje x_x");
    return -777;
  }
  if(!direxists("out")) {
    mkdir("out");
  }

  FILE *f = fopen(pName.c_str(), "rb");
  fread(monalisa, SZ, 1, f);
  fclose(f);

  for (;; step++) {
    // printf("starting step %i\n", step);
    // puts("Stage 1");
    mutate();

    // puts("Stage 2");
    score();

    // Dump best.
    // puts("Stage 3");
    cross();
    dump_best();    

    ///break;
  }

  return 0;
}

