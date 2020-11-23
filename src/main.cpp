#include <iostream>
#include "A_BrutForce.h"
#include "B_AlgoSequentiel.h"
#include "C_Kmeans.h"
#include "D_AproxImgBrutForce.h"
#include "E_AproxImgAdaptatif.h"

using namespace std;

int main(int argc, char** argv)
{
    if(!strcmp(argv[1], "A")) {
        return brutForce();
    } else if (!strcmp(argv[1], "B")) {
        return algoSequentiel();
    } else if (!strcmp(argv[1], "C")) {
        return kmeans();
    } else if (!strcmp(argv[1], "D")) {
        return aproxImgBrutForce();
    } else if (!strcmp(argv[1], "E")) {
        return aproxImgAdaptatif();
    }
    return EXIT_FAILURE;
}
