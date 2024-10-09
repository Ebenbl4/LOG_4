#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;

        if (data > root->data)    root->left = r;
        else root->right = r;
        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);
    return root;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL)
    {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
    {
        printf(" ");
    }

    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

struct Node* search(struct Node* root, int value)
{
    if (root == NULL || root->data == value)
        return root;

    if (value > root->data)
        return search(root->left, value);

    return search(root->right, value);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int D, start = 1;
    root = NULL;
    printf("Для окончания построения дерева необходимо ввести -1\n");
    while (start)
    {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1)
        {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, root, D);
    }

    print_tree(root, 0);
    while (1)
    {
        printf("\nВведите значение для поиска (-1 для выхода): ");
        scanf_s("%d", &D);
        if (D == -1)
            break;

        struct Node* result = search(root, D);
        if (result != NULL)
            printf("Значение %d найдено в дереве.\n", D);
        else
            printf("Значение %d не найдено в дереве.\n", D);
    }
    return 0;
}