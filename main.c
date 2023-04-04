/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           : main.c
 *   Deskripsi           :
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklarasi struktur data tree
typedef struct tree {
	char data[8];
	int child_count;
	struct tree **children;
} tree;

// Fungsi untuk menambahkan child dari suatu node dari tree
void append_child(tree **root, char *data) {
	// Untuk node root
	if (*root == NULL) {
		*root = (tree*)malloc(sizeof(tree));
		strcpy((*root)->data, data);
		(*root)->child_count = 0;
		(*root)->children = NULL;
	}
	// Untuk node selain root
	else {
		tree *temp = (tree*)malloc(sizeof(tree));
		strcpy(temp->data, data);
		temp->child_count = 0;
		temp->children = NULL;
		
		(*root)->child_count++;
		if ((*root)->children == NULL) {
			(*root)->children = (tree**)malloc(sizeof(tree*));
			*((*root)->children) = temp;
		}
		else {
			(*root)->children = (tree**)realloc((*root)->children, ((*root)->child_count)*sizeof(tree*));
			*((*root)->children + (*root)->child_count - 1) = temp;
		}
	}
}

// Fungsi untuk melakukan pencarian (menggunakan algoritma DFS)
void find_path(tree *root, char *target, char *result) {
	static int found;
	if (found)
		return;	// jika sudah ditemukan, tidak perlu melakukan pencarian lagi

	char temp[64];	// untuk menyimpan path sementara, berguna ketika masuk ke path yang salah
	strcpy(temp, result);
	if (strcmp(root->data, "root") != 0)
		strcat(result, "/");
	strcat(result, root->data);
	
	if (strcmp(root->data, target) == 0) {
		found = 1;	// file ditemukan
	}
	else {	// jika belum ditemukan, dari ke setiap node children (depth first)
		int i;
		for (i = 0; i < root->child_count; i++) {
			find_path(*(root->children + i), target, result);
		}
	}

	if (!found)
		strcpy(result, temp);	// saat masuk ke path yang salah, kembalikan result ke sebelumnya
}

int main() {
	tree *root = NULL;	// Pointer ke root dari file hierarchy
	tree *ptr = NULL;	// Pointer sementara untuk menunjuk node yang akan dilakukan append_child
	
	/* Proses pembuatan file hierarchy (sesuai gambar) */
	
	// Masukkan data root
	append_child(&root, "root");
	
	// Ubah ptr ke node yang akan di append_child, lakukan append_child sesuai file hierarchy
	// append_child node root
	ptr = root;
	append_child(&ptr, "folder1");
	append_child(&ptr, "folder3");
	append_child(&ptr, "folder7");
	
	// append_child node folder1
	ptr = *(root->children);
	append_child(&ptr, "file1");
	append_child(&ptr, "file2");
	append_child(&ptr, "folder2");
	
	// append_child node folder2
	ptr = *((*(root->children))->children + 2);
	append_child(&ptr, "file3");
	append_child(&ptr, "folder4");
	
	// append_child node folder4
	ptr = *((*((*(root->children))->children + 2))->children + 1);
	append_child(&ptr, "file4");
	
	// append_child node folder3
	ptr = *(root->children + 1);
	append_child(&ptr, "file5");
	append_child(&ptr, "folder5");

	// append_child node folder5
	ptr = *((*(root->children + 1))->children + 1);
	append_child(&ptr, "folder6");
	
	// append_child node folder6
	ptr = *((*((*(root->children + 1))->children + 1))->children);
	append_child(&ptr, "file6");
	
	// append_child node folder7
	ptr = *(root->children + 2);
	append_child(&ptr, "file7");
	
	
	// Variabel input dan output
	char input[8], output[64];
	memset(output, 0, 64);	// Agar tidak ada garbage di dalam variabel output
	
	// Template input
	printf("Masukkan nama file atau folder yang ingin dicari: ");
	scanf("%s", input);
	
	// Pencarian
	find_path(root, input, output);
	
	// Template output
	printf("Lokasi dari %s: %s", input, output);
	
	return 0;
}
