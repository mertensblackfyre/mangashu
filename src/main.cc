

#include "../includes/mangashu.h"


int main (int argc, char *argv[]) {
 
    Mangashu init;
    init.mangashu_create_dir("output");
    init.mangashu_traverse_dir("output","m");
    return 0;
}
