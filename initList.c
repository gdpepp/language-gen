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
    conset = NULL;
    sset = NULL;
    lset = NULL;
    fset = NULL;
    vowset = NULL;
    resset = NULL;

}

void defOrthInit() {
    fillOrthoList(defOrthList, "/home/gdpepp/CLionProjects/language-gen/config/ortho/default");
}

// TODO transformar a unicode
void cOrthInit() {
    fillOrthoListFromDirectory(cOrthList, "corth");
}

void vOrthInit() {
    fillOrthoListFromDirectory(vOrthList, "vorth");
}

void consetInit() {
     conset = getAllLinesFromFile("config/consets");
}

void vowsetInit() {
    vowset = getAllLinesFromFile("config/vowsets");
}

void lsetInit() {
    lset = getAllLinesFromFile("config/lsets");
}

void fsetInit() {
    fset = getAllLinesFromFile("config/fsets");
}

void ssetInit() {
    sset = getAllLinesFromFile("config/ssets");
}

//void ressetInit() {
//    list_add(resset, &(t_rectifier) {.rectName = "None", .re = ""});
//    list_add(resset, &(t_rectifier) {.rectName = "Double sounds", .re = "/(.)\1/"});
//    list_add(resset, &(t_rectifier) {.rectName = "Doubles & hard clusters", .re = "/[sʃf][sʃ]/, /(.)\1/, /[rl][rl]/"});
//}
