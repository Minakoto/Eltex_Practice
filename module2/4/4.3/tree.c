#include "tree.h"

// int main() {
//     int m[] = {50,30,55,25,35,53,60,10,32,37,62,15,31,33,40, 9, 0};
//     btree* root = NULL;
//     for(int i = 0; m[i] != 0; i++) {
//         root = Add(m[i], &root);
//     }
//     Print(root, 0);
//     Del(50, &root);
//     Print(root, 0);
// }

void Add(Entry value, btree** leaf) {
    if(*leaf == NULL) {
        *leaf = malloc(sizeof(btree));
        (*leaf)->left = (*leaf)->right = NULL;
        (*leaf)->val = value;
        return;
    }
    if((*leaf)->val.id > value.id) Add(value, &(*leaf)->left);
    else Add(value, &(*leaf)->right);
}
char Del(short key, btree** leaf) {
    btree* tmp, *up;
    if(*leaf == NULL) return 0;
    if((*leaf)->val.id == key) {
        if((*leaf)->left == NULL && (*leaf)->right == NULL) {
            free(*leaf);
            *leaf = NULL;
            printf("Deleted leaf\n");
            return 1;
        }
        if((*leaf)->left == NULL) {
            tmp = *leaf;
            *leaf =(*leaf)->right;
            free(tmp);
            printf("Deleted left\n");
            return 1;
        }
        if((*leaf)->right == NULL) {
            tmp = *leaf;
            *leaf =(*leaf)->left;
            free(tmp);
            printf("Deleted right\n");
            return 1;
        }
        up = *leaf;
        tmp = (*leaf)->left;
        while(tmp->right != NULL) {
            up = tmp;
            tmp = tmp->right;
        }
        (*leaf)->val.id = tmp->val.id;
        if(up != (*leaf)) {
            if(tmp->left != NULL) up->right = tmp->left;
            else up->right = NULL;
        }
        else (*leaf)->left = tmp->left;
        free(tmp);
        printf("Deleted both\n");
        return 1;
    }
if((*leaf)->val.id < key) return Del(key, &(*leaf)->right);
else return Del(key, &(*leaf)->left);
}

void Print(btree* root, int space) {
    space += 8;
    if (root->right != NULL) Print(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) printf(" ");
    printf("%d\n", root->val.id);
    if (root->left != NULL) Print(root->left, space);
}
// btree* Find(int key, btree* leaf) {
//     btree* tmp = leaf;
//     if(leaf == NULL) {
//         return NULL;
//     }
//     if(leaf->val.id == key) return tmp;
//     if(tmp->val.id > key) tmp->left = Find(key, tmp->left);
//     else tmp->left = Find(key, tmp->right);
//     return NULL;
// }

btree* Search(btree* root, int key) {
    if (!root) return NULL;
    else if (root->val.id == key) return root;
    btree* search_child_result = NULL;
    if (root->left != NULL) {
        search_child_result = Search(root->left, key);
        if (search_child_result) return search_child_result;
    }

    if (root->right != NULL) {
        search_child_result = Search(root->right, key);
        if (search_child_result)
            return search_child_result;
    }

    return search_child_result;
}

// int balfactor(btree* leaf) {
//     return (leaf->right)->height - (leaf->left)->height;
// }
// void fixheight(btree* leaf) {
//     int hl = (leaf->left)->height;
//     int hr = (leaf->right)->height;
//     leaf->height = (hl > hr ? hl : hr) + 1;
// }
// btree* rotater(btree* leaf) {
//     btree* q = leaf->left;
//     leaf->left = q->right;
//     q->right = leaf;
//     fixheight(leaf);
//     fixheight(q);
//     return leaf;
// }
// btree* rotatel(btree* leaf) {
//     btree* q = leaf->right;
//     leaf->right = q->left;
//     q->left = leaf;
//     fixheight(leaf);
//     fixheight(q);
//     return leaf;
// }
// btree* balance(btree* leaf) {
//     fixheight(leaf);
//     if(balfactor(leaf) == 2) {
//         if(balfactor(leaf->right) < 0) leaf->right = rotater(leaf->right);
//         return rotatel(leaf);
//     }
//     if(balfactor(leaf) == -2) {
//         if(balfactor(leaf->left) > 0) leaf->left = rotatel(leaf->left);
//         return rotater(leaf);
//     }
//     return leaf;
// }