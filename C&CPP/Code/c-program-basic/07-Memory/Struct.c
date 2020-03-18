/*
 ============================================================================

 Author      : Ztiany
 Description : C语言结构体

 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <mem.h>

static void defineStruct();

static void referenceStruct();

static void structArray();

static void structPointer();

static void functionPointerInStruct();

static void traverseStruct();

static void compoundLiteralStruct1();

static void compoundLiteralStruct2();

static void flexibleArrayMember();

#define MAXTITL  41
#define MAXAUTL  31

// 结构模版：标记是 book
struct book {
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};

int main() {
    //结构体示例
    //defineStruct();
    //引用结构体
    //referenceStruct();
    //结构体数组
    //structArray();
    //结构体数组遍历
    //traverseStruct();
    //结构体指针
    //structPointer();
    //结构体中的函数指针
    //functionPointerInStruct();
    //复合字面量和结构（C99）
    //compoundLiteralStruct1();
    //compoundLiteralStruct2();
    //伸缩型数组成员（flexible array member ）（C11）
    flexibleArrayMember();
    return 0;
}

static void flexibleArrayMember() {
    struct flex {
        int count;
        double average;
        // 伸缩型数组成员
        double scores[];
    };

    struct flex *pf1;    // 声明一个指针
    struct flex *pf2;    // 声明一个指针

    // 请求为一个结构和一个数组分配存储空间
    pf1 = malloc(sizeof(struct flex) + 5 * sizeof(double));
    // 可以为伸缩型数组成员分配不同的存储空间
    pf2 = malloc(sizeof(struct flex) + 9 * sizeof(double));

    pf1->scores[0] = 1.0F;
    pf2->scores[0] = 10.0F;

    printf(" pf1->scores[0]  = %f\n", pf1->scores[0]);
    printf(" pf2->scores[0]  = %f\n", pf2->scores[0]);

    free(pf1);
    free(pf2);
}

static void receiveCompoundLiteralStruct(struct book *structbook) {
    printf("book name: %s", structbook->title);
}

//如果函数接受一个地址，可以传递复合字面量的地址：
static void compoundLiteralStruct2() {
    receiveCompoundLiteralStruct(&(struct book) {"How to find a beautiful girl", "Ztiany", 2.0F});
}

//复合字面量
static void compoundLiteralStruct1() {

    struct book readFirst;
    int score;

    printf("Enter test score: ");
    scanf("%d", &score);

    if (score >= 84) {
        readFirst = (struct book) {"Crime and Punishment", "Fyodor Dostoyevsky", 11.25};
    } else {
        readFirst = (struct book) {"Mr. Bouncy's Nice Hat", "Fred Winsome", 5.99};
    }

    printf("Your assigned reading:\n");
    printf("%s by %s: $%.2f\n", readFirst.title, readFirst.author, readFirst.value);
}

//在结构体中声明指针变量
static void functionPointerInStruct() {
    struct Arr {
        int (*f)(int, int);

        int a;
        int b;
    };

    extern int maxValue(int, int);//这里声明方法，编译时自动查找

    int (*f)(int, int) = maxValue;
    struct Arr arr = {f, 3, 100};
    int max = arr.f(arr.a, arr.b);
    printf("max value = %d", max);
}

int maxValue(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

//结构体指针
static void structPointer() {
    //定义结构体指针
    struct Student {
        int num;                    //4
        char name[20];              //20
        char sex;                   //1
        int age;                    //4
        float score;                //4
        char address[20];           //20
    } student = {20, "张三", 'm', 30, 23.6F, "湖南"};

    struct Student *sp;
    sp = &student;
    student.num = 1;
    strcpy(student.name, "李四");
    printf("%s,%d\n", sp->name, sp->num);// 使用结构体指针引用结构体的数据时，直接使用 ->符号
    printf("%d\n", (*sp).num);
}

//定义结构体数组
static void structArray() {
    //使用结构体数组，这里定义了3个元素的数组
    struct Man {
        char name[20];              //20
        int num;                    //4
    } players[] = {"z", 0, "y", 0, "x", 0};

    char name[20];
    for (int i = 0; i < 10; ++i) {
        scanf("%s", name);
        for (int j = 0; j < 3; ++j) {
            if (strcmp(name, players[j].name) == 0) {
                players[j].num++;
            }
        }
    }
    for (int k = 0; k < 3; ++k) {
        printf("name : %s , num = %d \n", players[k].name, players[k].num);
    }
}

//结构体遍历
static void traverseStruct() {

    struct Man {
        char name[20];
        int age;
    };

    struct Man mans[] = {{"Jack", 20},
                         {"Rose", 19}};
    //遍历结构体数组

    //1.
    struct Man *p = mans;
    for (; p < mans + 2; p++) {
        printf("%s,%d \n", p->name, p->age);
    }

    //2.
    int i = 0;
    for (; i < sizeof(mans) / sizeof(struct Man); i++) {
        printf("%s,%d \n", mans[i].name, mans[i].age);
    }
}


//访问结构体的成员
static void referenceStruct() {
    struct Student {
        int num;            //4
        char name[20];      //20
        char sex;           //1
        int age;            //4
        float score;        //4
        char address[20];   //20
    } student = {20, "张三", 'm', 30, 23.6F, "湖南"};

    printf("student address is %p \n", &student);   //结构体首地址
    printf("student address is %p \n", &student.num);
}


//定义结构体
static void defineStruct() {

    //数组只能存储类型相同的元素，如果需要在一个数据结果中存储不同的数据类型，可以使用结构体
    struct Student {
        //下面元素可以称为：成员列表或域表
        int num;            //4
        char name[20];      //20
        char sex;           //1
        int age;            //4
        float score;        //4
        char address[20];   //20
    };

    printf("Student size is %d \n", sizeof(struct Student));//56

    //结构体嵌套：结构体中可以定义另一个结构体
    //嵌套1
    struct Date {
        int month;
        int year;
        int day;
    };

    struct Man {
        char name[20];
        struct Date birthday;
    };

    //嵌套2
    struct A {
        char name[20];
        int age;
        struct B {
            char name[20];
        } t;
    };

    //声明结构体只是定义了一种数据模型，并没有定义变量，其本身不占内存，现在定义一个结构体的实例，才会占用内存
    struct Student student = {20, "张三", 'm', 30, 23.6F, "湖南"};
    printf("student age = %d \n", student.age);

    //形式2
    struct Date1 {
        int month;
        int year;
        int day;
    } date1, date2;

    //形式3:匿名结构体
    struct {
        int month;
        int year;
        int day;
    } date3;

}