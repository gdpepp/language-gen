//
// Created by utnso on 24/07/18.
//
#include "initList.h"

void listInit() {
    createLists();
    defOrthInit();
//    cOrthInit();
//    vOrthInit();
//    consetInit();
//    vowsetInit();
//    ressetInit();
//    ssetInit();
//    lsetInit();
//    fsetInit();
}

void createLists() {
    defOrthList = list_create();
    cOrthList = list_create();
    vOrthList = list_create();
    conset = list_create();
    vowset = list_create();
    resset = list_create();
    sset = list_create();
    lset = list_create();
    fset = list_create();
}

void defOrthInit() {
    FILE *file;
    char* fname = "./config/ortho/default";
    char line[32];
    char** keyvalue;
    int i;
    int lines = getFileLines(fname);
    t_orth* os = NULL;

    if (!fopen(fname, "r")) {
        exit(1);
    }

    for(i = 0; i < lines; i++) {
        memset(line, '\0', 32);
        if(fgets(line, i, file) != line) {
            printf("Error en fgets");
        }

        keyvalue = string_split(line, "=");
        os = malloc(sizeof(t_orth));
        os->letter = (wchar_t*) keyvalue[0];
        strcpy(os->sound, keyvalue[1]);
        list_add(defOrthList, os);
    }
    freeSplit(keyvalue);
    fclose(file);
}

// TODO transformar a unicode
//void cOrthInit() {
//
//    // default
//    t_orthset def = {.name = "Default", .orthset = list_create()};
//
//    // slavic
//    t_list *slavicList = list_create();
//    list_add(slavicList, &(t_orth) {.letter = L'ʃ', .sound = "š"});
//    list_add(slavicList, &(t_orth) {.letter = L'ʒ', .sound = "ž"});
//    list_add(slavicList, &(t_orth) {.letter = L'ʧ', .sound = "č"});
//    list_add(slavicList, &(t_orth) {.letter = L'ʤ', .sound = "ǧ"});
//    list_add(slavicList, &(t_orth) {.letter = 'j', .sound = "j"});
//    list_add(slavicList, &(t_orth) {.letter = L'ʧ', .sound = "č"});
//    t_orthset sla = {.name = "Slavic", .orthset = slavicList};
//
//    // german
//    t_list *germanList = list_create();
//    list_add(germanList, &(t_orth) {.letter = L'ʃ', .sound = "sch"});
//    list_add(germanList, &(t_orth) {.letter = L'ʒ', .sound = "zh"});
//    list_add(germanList, &(t_orth) {.letter = L'ʧ', .sound = "tsch"});
//    list_add(germanList, &(t_orth) {.letter = L'ʤ', .sound = "dz"});
//    list_add(germanList, &(t_orth) {.letter = 'j', .sound = "j"});
//    list_add(germanList, &(t_orth) {.letter = 'x', .sound = "ch"});
//    t_orthset ger = {.name = "German", .orthset = germanList};
//
//    // french
//    t_list *frenchList = list_create();
//    list_add(frenchList, &(t_orth) {.letter = L'ʃ', .sound = "ch"});
//    list_add(frenchList, &(t_orth) {.letter = L'ʒ', .sound = "j"});
//    list_add(frenchList, &(t_orth) {.letter = L'ʧ', .sound = "tch"});
//    list_add(frenchList, &(t_orth) {.letter = L'ʤ', .sound = "dj"});
//    list_add(frenchList, &(t_orth) {.letter = 'x', .sound = "kh"});
//    t_orthset fre = {.name = "French", .orthset = frenchList};
//
//    // chinese
//    t_list *chineseList = list_create();
//    list_add(chineseList, &(t_orth) {.letter = L'ʃ', .sound = "x"});
//    list_add(chineseList, &(t_orth) {.letter = L'ʧ', .sound = "q"});
//    list_add(chineseList, &(t_orth) {.letter = L'ʤ', .sound = "j"});
//    t_orthset chi = {.name = "Chinese", .orthset = chineseList};
//
//    list_add(cOrthList, &def);
//    list_add(cOrthList, &sla);
//    list_add(cOrthList, &ger);
//    list_add(cOrthList, &fre);
//    list_add(cOrthList, &chi);
//}
//
//void vOrthInit() {
//
//    // default
//    t_orthset def = {.name = "Ácutes", .orthset = list_create()};
//
//    // umlaut
//    t_list *umlautList = list_create();
//    list_add(umlautList, &(t_orth) {.letter = 'A', .sound = "ä"});
//    list_add(umlautList, &(t_orth) {.letter = 'E', .sound = "ë"});
//    list_add(umlautList, &(t_orth) {.letter = 'I', .sound = "ï"});
//    list_add(umlautList, &(t_orth) {.letter = 'O', .sound = "ö"});
//    list_add(umlautList, &(t_orth) {.letter = 'U', .sound = "ü"});
//    t_orthset uml = {.name = "Ümlauts", .orthset = umlautList};
//
//    // welsh
//    t_list *welshList = list_create();
//    list_add(welshList, &(t_orth) {.letter = 'A', .sound = "â"});
//    list_add(welshList, &(t_orth) {.letter = 'E', .sound = "ê"});
//    list_add(welshList, &(t_orth) {.letter = 'I', .sound = "y"});
//    list_add(welshList, &(t_orth) {.letter = 'O', .sound = "ô"});
//    list_add(welshList, &(t_orth) {.letter = 'U', .sound = "w"});
//    t_orthset wel = {.name = "Welsh", .orthset = welshList};
//
//    // diphthongs
//    t_list *dipthList = list_create();
//    list_add(dipthList, &(t_orth) {.letter = 'A', .sound = "au"});
//    list_add(dipthList, &(t_orth) {.letter = 'E', .sound = "ei"});
//    list_add(dipthList, &(t_orth) {.letter = 'I', .sound = "ie"});
//    list_add(dipthList, &(t_orth) {.letter = 'O', .sound = "ou"});
//    list_add(dipthList, &(t_orth) {.letter = 'U', .sound = "oo"});
//    t_orthset dip = {.name = "Diphthongs", .orthset = dipthList};
//
//    // doubles
//    t_list *doublList = list_create();
//    list_add(doublList, &(t_orth) {.letter = 'A', .sound = "aa"});
//    list_add(doublList, &(t_orth) {.letter = 'E', .sound = "ee"});
//    list_add(doublList, &(t_orth) {.letter = 'I', .sound = "ii"});
//    list_add(doublList, &(t_orth) {.letter = 'O', .sound = "oo"});
//    list_add(doublList, &(t_orth) {.letter = 'U', .sound = "uu"});
//    t_orthset dou = {.name = "Doubles", .orthset = doublList};
//
//    list_add(vOrthList, &def);
//    list_add(vOrthList, &uml);
//    list_add(vOrthList, &wel);
//    list_add(vOrthList, &dip);
//    list_add(vOrthList, &dou);
//}

void consetInit() {
    t_set* set = malloc(sizeof(t_set));
    set->setName = "Minimal", set->letters = "ptkmnls";
    list_add(conset, set);

    t_set* set1 = malloc(sizeof(t_set));
    set1->setName = "English", set->letters = "ptkbdgmnlrsʃzʒʧ";
    list_add(conset, set1);

    list_add(conset, &(t_set) {.setName = "Pirahã", .letters = "ptkmnh"});
    list_add(conset, &(t_set) {.setName = "Hawaiian", .letters = "hklmnpwʔ"});
    list_add(conset, &(t_set) {.setName = "Greenlandic", .letters = "ptkqvsgrmnŋlj"});
    list_add(conset, &(t_set) {.setName = "Arabic", .letters = "tksʃdbqɣxmnlrwj"});
    list_add(conset, &(t_set) {.setName = "Arabic-lite", .letters = "tkdgmnsʃ"});
    list_add(conset, &(t_set) {.setName = "English-lite", .letters = "ptkbdgmnszʒʧhjw"});
}

void vowsetInit() {
    list_add(vowset, &(t_set) {.setName = "Standard 5-vowel", .letters = "aeiou"});
    list_add(vowset, &(t_set) {.setName = "3-vowel a i u", .letters = "aiu"});
    list_add(vowset, &(t_set) {.setName = "Extra A E I", .letters = "aeiouAEI"});
    list_add(vowset, &(t_set) {.setName = "Extra U", .letters = "aeiouU"});
    list_add(vowset, &(t_set) {.setName = "5-vowel a i u A I", .letters = "aiuAI"});
    list_add(vowset, &(t_set) {.setName = "3-vowel e o u", .letters = "eou"});
    list_add(vowset, &(t_set) {.setName = "Extra A O U", .letters = "aeiouAOU"});
}

void ressetInit() {
    list_add(resset, &(t_rectifier) {.rectName = "None", .re = ""});
    list_add(resset, &(t_rectifier) {.rectName = "Double sounds", .re = "/(.)\1/"});
    list_add(resset, &(t_rectifier) {.rectName = "Doubles & hard clusters", .re = "/[sʃf][sʃ]/, /(.)\1/, /[rl][rl]/"});
}

void ssetInit() {
    list_add(sset, &(t_set) {.setName = "Just s", .letters = "s"});
    list_add(sset, &(t_set) {.setName = "s ʃ", .letters = "sʃ"});
    list_add(sset, &(t_set) {.setName = "s ʃ f", .letters = "sʃf"});
}

void lsetInit() {
    list_add(sset, &(t_set) {.setName = "r l", .letters = "rl"});
    list_add(sset, &(t_set) {.setName = "Just r", .letters = "r"});
    list_add(sset, &(t_set) {.setName = "Just l", .letters = "l"});
    list_add(sset, &(t_set) {.setName = "w j", .letters = "wj"});
    list_add(sset, &(t_set) {.setName = "r l w j", .letters = "rlwj"});
}

void fsetInit() {
    list_add(fset, &(t_set) {.setName = "m n", .letters = "mn"});
    list_add(fset, &(t_set) {.setName = "s k", .letters = "sk"});
    list_add(fset, &(t_set) {.setName = "m n ŋ", .letters = "mnŋ"});
    list_add(fset, &(t_set) {.setName = "s ʃ z ʒ", .letters = "sʃzʒ"});
}
