#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

// File structure
struct File {
    int id;
    char name[MAX_FILENAME_LENGTH];
};

// Directory structure
struct Directory {
    struct File files[MAX_FILES];
    int fileCount;
};

// Function prototypes
void initializeDirectory(struct Directory *dir);
void addFile(struct Directory *dir, int fileId, const char *fileName);
void deleteFile(struct Directory *dir, int fileId);
void listFiles(struct Directory *dir);

int main() {
    struct Directory dir;
    int choice, fileId;
    char fileName[MAX_FILENAME_LENGTH];

    // Initialize directory
    initializeDirectory(&dir);

    // Menu
    while (1) {
        printf("\nSingle-Level Directory Operations\n");
        printf("1. Add File\n");
        printf("2. Delete File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file ID and name: ");
                scanf("%d %s", &fileId, fileName);
                addFile(&dir, fileId, fileName);
                break;
            case 2:
                printf("Enter file ID to delete: ");
                scanf("%d", &fileId);
                deleteFile(&dir, fileId);
                break;
            case 3:
                listFiles(&dir);
                break;
            case 4:
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

// Initialize directory
void initializeDirectory(struct Directory *dir) {
    dir->fileCount = 0;
}

// Add file to directory
void addFile(struct Directory *dir, int fileId, const char *fileName) {
    if (dir->fileCount < MAX_FILES) {
        struct File *file = &dir->files[dir->fileCount++];
        file->id = fileId;
        strcpy(file->name, fileName);
        printf("File '%s' added with ID %d\n", fileName, fileId);
    } else {
        printf("Cannot add file. Directory is full.\n");
    }
}

// Delete file from directory
void deleteFile(struct Directory *dir, int fileId) {
    int i, found = 0;
    for (i = 0; i < dir->fileCount; i++) {
        if (dir->files[i].id == fileId) {
            printf("File '%s' with ID %d deleted\n", dir->files[i].name, fileId);
            found = 1;
            break;
        }
    }

    if (found) {
        for (int j = i; j < dir->fileCount - 1; j++) {
            dir->files[j] = dir->files[j + 1];
        }
        dir->fileCount--;
    } else {
        printf("File with ID %d not found\n", fileId);
    }
}

// List all files in directory
void listFiles(struct Directory *dir) {
    if (dir->fileCount == 0) {
        printf("No files in directory\n");
    } else {
        printf("Files in Directory:\n");
        for (int i = 0; i < dir->fileCount; i++) {
            printf("File ID: %d, Name: %s\n", dir->files[i].id, dir->files[i].name);
        }
    }
}

