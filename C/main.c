#include <stdio.h>
#include <stdlib.h>

struct Father
{
    void **vptr;
    int x, y; /* data */
};
struct Son
{
    struct Father super;
    int z;
    /* data */
};
struct Child
{
    struct Son super;
    int a, b; /* data */
};
typedef struct Father Father;
typedef struct Child Child;
typedef struct Son Son;
int Father_add_all(void *self)
{
    return ((Father *)self)->x + ((Father *)self)->y;
}

int Son_add_all(void *self)
{
    return ((Father *)self)->x + ((Father *)self)->y + ((Son *)self)->z;
}

int Child_add_all(void *self)
{
    return ((Father *)self)->x + ((Father *)self)->y + ((Son *)self)->z + ((Child *)self)->a + ((Child *)self)->b;
}
void Father_say(void *self, const char *s)
{
    printf("Father say : %s  ", s);
}

void Child_say(void *self, const char *s)
{
    printf("Child say : %s  ", s);
}
void *v_table_Father[2];
void *v_table_Son[2];
void *v_table_Child[2];
Father *new_Father(int x, int y)
{
    Father *f = (Father*)malloc(sizeof(Father));
    f->vptr = v_table_Father;
    f->x = x;
    f->y = y;
    return f;

}
Son *new_Son(int x, int y,int z)
{
    Son *f = (Son*)malloc(sizeof(Son));
    f->super.vptr = v_table_Son;
    f->super.x = x;
    f->super.y = y;
    f->z = z;
    return f;

}
Child* new_Child(int x, int y, int z, int a, int b) {
    Child* f = (Child*)malloc(sizeof(Child));
    f->super.super.vptr = v_table_Child;
    f->super.super.x = x;
    f->super.super.y = y;
    f->super.z = z;
    f->a = a;
    f->b = b;
    return f;
}
void init()
{
    v_table_Father[0] = Father_add_all;
    v_table_Father[1] = Father_say;

    v_table_Son[0] = Son_add_all;
    v_table_Son[1] = Father_say;

    v_table_Child[0] = Child_add_all;
    v_table_Child[1] = Child_say;
}
int add_all(void *self){
    Father *f = (Father*) self;
    return ((int(*)(void*))(f->vptr[0]))(f);
}
void say(void *self,const char *s){
    Father *f = (Father*) self;
    return (((void(*)(void* ,const char *))(f->vptr[1])))(self,s);
}
void test() {
    init();
    Father* f = new_Father(1, 2);
    say(f, "this is Father");
    printf("%d\n", add_all(f));
    f = (Father*)new_Son(1, 2, 10);
    say(f, "this is Son");
    printf("%d\n", add_all(f));
    f = (Father*)new_Child(1, 2, 3, 4, 5);
    say(f, "this is Child");
    printf("%d\n", add_all(f));

    printf("%d %d %d", sizeof(Father), sizeof(Son), sizeof(Child));
}

int main()
{
    init();
    test();
    return 0;
}