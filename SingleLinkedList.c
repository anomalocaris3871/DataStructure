#include <stdio.h>
#include <malloc.h>
#include <sec_api/string_s.h>

typedef struct USERDATA {
    int age;
    char name[32];
    char phone[32];
    struct USERDATA *pNext;
} USERDATA;

USERDATA *g_pHeadNode = NULL;

void addNewNode(int age, const char *pszName, const char *pszPhone) {

    USERDATA *pNewNode = (USERDATA *) malloc(sizeof(USERDATA));
    pNewNode->age = age;
    strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
    strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
    pNewNode->pNext = NULL;

    if (g_pHeadNode == NULL) {
        g_pHeadNode = pNewNode;
    } else {
        USERDATA *pTail = g_pHeadNode;
        while (pTail->pNext != NULL) {
            pTail = pTail->pNext;
        }
        pTail->pNext = pNewNode;
    }
}

void deleteNode(const char *pszName) {

    USERDATA *deletedNode = g_pHeadNode;
    USERDATA *prevNode = NULL;

    while (deletedNode != NULL) {
        if (strcmp(deletedNode->name, pszName) == 0) {
            break;
        }
        prevNode = deletedNode;
        deletedNode = deletedNode->pNext;
    }

    if (deletedNode != NULL) {
        printf("\"%s\" is deleted\n", deletedNode->name);
        if (prevNode == NULL) {
            g_pHeadNode = deletedNode->pNext;
            free(deletedNode);
        } else {
            prevNode->pNext = deletedNode->pNext;
            free(deletedNode);
        }

    } else {
        puts("Not found");
        return;
    }
}

void releaseList(void) {
    puts("=================Release==================");
    USERDATA *pTmp = g_pHeadNode;
    USERDATA *pDelete;
    while (pTmp != NULL) {
        pDelete = pTmp;
        pTmp = pTmp->pNext;

        printf("Delete [%p] %d, %s, %s, [next: %p]\n",
               pDelete, pDelete->age, pDelete->name, pDelete->phone, pDelete->pNext);
        free(pDelete);
    }

    g_pHeadNode = NULL;
}

void initDummyData(void) {
    addNewNode(10, "hoon", "011-111-111");
    addNewNode(15, "kim", "011-111-112");
    addNewNode(14, "de", "021-111-112");
}

USERDATA *findNodeByName(const char *pszName) {
    USERDATA *pTmp = g_pHeadNode;
    while (pTmp != NULL) {
        if (strcmp(pTmp->name, pszName) == 0) {
            printf("\"%s\" : Found\n", pszName);
            return pTmp;
        }

        pTmp = pTmp->pNext;
    }
    printf("\"%s\" : Not found\n", pszName);
    return NULL;
}

void printData(void) {

    USERDATA *pTmp = g_pHeadNode;
    while (pTmp != NULL) {
        printf("[%p] %d, %s, %s, [next: %p]\n", pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
        pTmp = pTmp->pNext;
    }
    putchar('\n');
}


int main() {
    initDummyData();

    printData();
    deleteNode("hoon");
    printData();

    addNewNode(13, "hoon", "111-111-111");
    printData();
    deleteNode("de");
    printData();

    addNewNode(13, "de", "333-333-333");
    printData();
    deleteNode("de");
    printData();


    releaseList();
    return 0;
}