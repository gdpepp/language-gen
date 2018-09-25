//
// Created by utnso on 24/07/18.
//
#include "initList.h"
#include "ortho.h"

void listInit() {
    createLists();
    defOrthInit();
    cOrthInit();
    vOrthInit();
    consetInit();
    vowsetInit();
    //ressetInit();
    ssetInit();
    lsetInit();
    fsetInit();
}

void createLists() {
    defOrthList = list_create();
    cOrthList = list_create();
    vOrthList = list_create();
}

void defOrthInit() {
    fillOrthoList(defOrthList, "config/ortho/default");
}

// TODO transformar a unicode
void cOrthInit() {
    fillOrthoListFromDirectory(cOrthList, "corth");
}

void vOrthInit() {
    fillOrthoListFromDirectory(vOrthList, "vorth");
}

void consetInit() {
     getAllLinesFromFile(conset, "config/consets");
}

void vowsetInit() {
    getAllLinesFromFile(vowset, "config/vowsets");
}

void lsetInit() {
    getAllLinesFromFile(lset, "config/lsets");
}

void fsetInit() {
    getAllLinesFromFile(fset, "config/fsets");
}

void ssetInit() {
    getAllLinesFromFile(sset, "config/ssets");
}

//void ressetInit() {
//    list_add(resset, &(t_rectifier) {.rectName = "None", .re = ""});
//    list_add(resset, &(t_rectifier) {.rectName = "Double sounds", .re = "/(.)\1/"});
//    list_add(resset, &(t_rectifier) {.rectName = "Doubles & hard clusters", .re = "/[sʃf][sʃ]/, /(.)\1/, /[rl][rl]/"});
//}
