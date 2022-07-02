#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tag {
    char website[100];
    char IP[17];
    struct tag* next;
    struct tag* previous;
}page_info;

int n_links = 0;

void menu();
void opening();
page_info *create_fill_node (char website[], char IP[]);
void open_browser (page_info **front, page_info **rear, FILE *home);
void dequeue (page_info **front, page_info **rear);
void enqueue (page_info **front, page_info **rear, page_info *new_node);
void confirm_entering (page_info *new_node);
void clicking_new_link (page_info **front, page_info **rear, FILE *history);
void previous (page_info *front, page_info *rear);
void forward (page_info *front, page_info *rear, page_info *current);
void save_favorite (FILE *favorite, page_info *front, page_info *rear);
void quit (page_info **front, page_info **rear, FILE *history);
void open_browser_first ();
void cls();

int main () {
    int menu_choice, open_flag = 0;
    page_info *front = NULL, *rear = NULL;
    FILE *home, *history, *favorite;
    do {
        menu();
        scanf("%d", &menu_choice);

        switch (menu_choice) {
            case 1:
                cls();
                open_flag = 1;
                if (n_links == 0) {
                    opening();
                }
                cls();
                open_browser(&front, &rear, home);
                break;
            case 2:
                if (open_flag == 1) {
                    cls();
                    clicking_new_link(&front, &rear, history);
                } else {
                    open_browser_first();
                }
                break;
            case 3:
                if (open_flag == 1) {
                    cls();
                    previous(front, rear);
                } else {
                    open_browser_first();
                }
                break;
            case 4:
                if (open_flag == 1) {
                    cls();
                    forward(front, rear, rear);
                } else {
                    open_browser_first();
                }
                break;
            case 5:
                if (open_flag == 1) {
                    cls();
                    save_favorite(favorite, front, rear);
                } else {
                    open_browser_first();
                }
                break;
            case 6:
                if (open_flag == 1) {
                    cls();
                    quit(&front, &rear, history);
                } else {
                    open_browser_first();
                }
                break;
            default:
                printf("\t\tWrong Choice!!\n");
        }
    } while (menu_choice != 6);
}

void menu() {
    printf("\t\t----------------------------------------\n");
    printf("\t\t|                                      |\n");
    printf("\t\t|          1. Open the Browser         |\n");
    printf("\t\t|          2. Click on a Link          |\n");
    printf("\t\t|             3. Click Back            |\n");
    printf("\t\t|           4. Click Forward           |\n");
    printf("\t\t|           5. Save Favorite           |\n");
    printf("\t\t|           6. Close Browser           |\n");
    printf("\t\t|                                      |\n");
    printf("\t\t----------------------------------------\n");
    printf("\n\t\tChoice: ");
}

void opening () {
    printf("\t\t----------------------------------------\n");
    printf("\t\t|                                      |\n");
    printf("\t\t|        Welcome to our browser!       |\n");
    printf("\t\t|  We are doing our best to give your  |\n");
    printf("\t\t|     the best experience possible.    |\n");
    printf("\t\t| We hope you're enjoying our browser! |\n");
    printf("\t\t|                                      |\n");
    printf("\t\t----------------------------------------\n");
    printf("\n\t\tPress Enter to Continue...\n");
    getchar();
    getchar();
}

page_info *create_fill_node (char website[], char IP[]) {
    page_info *new_node = (page_info *) malloc (sizeof(page_info));
    strcpy(new_node->website, website);
    strcpy(new_node->IP, IP);
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}

void open_browser (page_info **front, page_info **rear, FILE *home) {
    char website[100], IP[17];
    home = fopen("home_choice.txt", "r");
    if (home == NULL) {
        printf("\t\t----------------------------------------\n");
        printf("\t\t|                                      |\n");
        printf("\t\t|         Error Opening File!!         |\n");
        printf("\t\t|                                      |\n");
        printf("\t\t----------------------------------------\n");
        getchar();
        exit(1);
    }
    fscanf(home, "%s\n", website);
    fscanf(home, "%s", IP);
    fclose(home);
    page_info *new_node = create_fill_node(website, IP);
    if (n_links < 6) {
        enqueue(front, rear, new_node);
        confirm_entering(new_node);
    } else {
        dequeue(front, rear);
        enqueue(front, rear, new_node);
        confirm_entering(new_node);
    }
}

void clicking_new_link (page_info **front, page_info **rear, FILE *history) {
    char website[100], IP[17], lines[30] = "------------------------";
    char temp[100];
    int flag = 0;
    printf("Enter the link you want to visit: ");
    scanf("%s", temp);
    history = fopen("history.txt", "r");
    if (history == NULL) {
        printf("\t\t----------------------------------------\n");
        printf("\t\t|                                      |\n");
        printf("\t\t|         Error Opening File!!         |\n");
        printf("\t\t|                                      |\n");
        printf("\t\t----------------------------------------\n");
        getchar();
        exit(1);
    }
    while (fscanf(history, "%s\n", website) != EOF) {
        fscanf(history, "%s\n", IP);
        fscanf(history, "%s\n", lines);
        if (strcmp(temp, website) == 0) {
            flag = 1;
            page_info *new_node = create_fill_node(website, IP);
            if (n_links < 6) {
                enqueue(front, rear, new_node);
                confirm_entering(new_node);
            } else {
                dequeue(front, rear);
                enqueue(front, rear, new_node);
                confirm_entering(new_node);
            }
            fclose(history);
            history = fopen("history.txt", "a");
            fprintf(history, "%s\n", new_node->website);
            fprintf(history, "%s\n", new_node->IP);
            fprintf(history, "%s\n", lines);
            fclose(history);
            break;
        }
    }
    if (flag == 0) {
        strcpy(website, temp);
        printf("Enter the IP address of the website: ");
        scanf("%s", IP);
        page_info *new_node = create_fill_node(website, IP);
        if (n_links < 6) {
            enqueue(front, rear, new_node);
            confirm_entering(new_node);
        } else {
            dequeue(front, rear);
            enqueue(front, rear, new_node);
            confirm_entering(new_node);
        }
        history = fopen("history.txt", "a");
        fprintf(history, "%s\n", website);
        fprintf(history, "%s\n", IP);
        fprintf(history, "%s\n", lines);
        fclose(history);
    }
}

void confirm_entering (page_info *new_node) {
    printf("\t\t----------------------------------------\n");
    printf("\t\t|                                      |\n");
    printf("\t\t|      You are now on %s       |\n", new_node->website);
    printf("\t\t|                                      |\n");
    printf("\t\t----------------------------------------\n");
    printf("\n\t\tPress Enter to Continue...\n");
    getchar();
    if (n_links != 0) {
        getchar();
    }
}

void enqueue (page_info **front, page_info **rear, page_info *new_node) {
    if (*front == NULL) {
        *front = new_node;
    } else {
        (*rear)->next = new_node;
        new_node->previous = *rear;
    }
    *rear = new_node;
    n_links++;
}

void dequeue (page_info **front, page_info **rear) {
    if (*front == NULL) {
        return;
    } else {
        page_info *temp = *front;
        *front = (*front)->next;
        if (*front != NULL) {
            (*front)->previous = NULL;
        }
        free(temp);
    }
    n_links--;
}

void previous (page_info *front, page_info *rear) {
    page_info *current;
    int flag = 0;
    char temp_website[100];
    page_info *walker_back;
    if (front == NULL) {
        return;
    } else if (front == rear) {
        return;
    } else {
        printf("\t\t----------------------------------------\n");
        printf("\t\t|                                      |\n");
        printf("\t\t|   Enter the URL of the web page you  |\n");
        printf("\t\t|         want to get back to:         |\n");
        printf("\t\t|                                      |\n");
        printf("\t\t----------------------------------------\n");
        printf("\n\t\tThe URL is: ");
        getchar();
        scanf("%s", temp_website);
        cls();
        walker_back = rear;
        while (walker_back != NULL) {
            if (strcmp(temp_website, walker_back->website) == 0) {
                flag = 1;
                confirm_entering(walker_back);
                current = walker_back;
                break;
            }
            walker_back = walker_back->previous;
        }
        if (flag == 0) {
            if (rear->previous != NULL) {
                confirm_entering(rear->previous);
                current = rear->previous;
            } else {
                printf("\t\t----------------------------------------\n");
                printf("\t\t|                                      |\n");
                printf("\t\t|        Error: Page Not Found         |\n");
                printf("\t\t|                                      |\n");
                printf("\t\t----------------------------------------\n");
                printf("\n\t\tPress Enter to Continue...\n");
                getchar();
            }
        }
    }
}

void forward (page_info *front, page_info *rear, page_info *current) {
    int flag = 0;
    char temp_website[100];
    page_info *walker_forward;
    if (front == NULL) {
        return;
    } else if (front == rear) {
        return;
    } else {
        printf("\t\t----------------------------------------\n");
        printf("\t\t|                                      |\n");
        printf("\t\t|   Enter the URL of the web page you  |\n");
        printf("\t\t|         want to get forward to:       |\n");
        printf("\t\t|                                      |\n");
        printf("\t\t----------------------------------------\n");
        printf("\n\t\tThe URL is: ");
        getchar();
        scanf("%s", temp_website);
        cls();
        walker_forward = current;
        while (walker_forward != NULL) {
            if (strcmp(temp_website, walker_forward->website) == 0) {
                flag = 1;
                confirm_entering(walker_forward);
                break;
            }
            walker_forward = walker_forward->next;
        }
        if (flag == 0) {
            if (current->next != NULL) {
                confirm_entering(current->next);
            } else {
                printf("\t\t----------------------------------------\n");
                printf("\t\t|                                      |\n");
                printf("\t\t|        Error: Page Not Found         |\n");
                printf("\t\t|                                      |\n");
                printf("\t\t----------------------------------------\n");
                printf("\n\t\tPress Enter to Continue...\n");
                getchar();
            }
        }
    }
}

void save_favorite (FILE *favorite, page_info *front, page_info *rear) {
    char temp_website[100];
    char temp_IP[17];
    char lines[30] = "------------------------";
    int flag = 0;
    printf("\t\t----------------------------------------\n");
    printf("\t\t|                                      |\n");
    printf("\t\t|   Enter the URL of the web page you  |\n");
    printf("\t\t|      want to save as a favorite:     |\n");
    printf("\t\t|                                      |\n");
    printf("\t\t----------------------------------------\n");
    printf("\n\t\tThe URL is: ");
    getchar();
    scanf("%s", temp_website);
    cls();
    page_info *walker = rear;
    while (walker != NULL) {
        if (strcmp(temp_website, walker->website) == 0) {
            flag = 1;
            printf("\t\t----------------------------------------\n");
            printf("\t\t|                                      |\n");
            printf("\t\t|   %s is in your bookmarks now   |\n", walker->website);
            printf("\t\t|                                      |\n");
            printf("\t\t----------------------------------------\n");
            printf("\n\t\tPress Enter to Continue...\n");
            getchar();
            favorite = fopen("bookmark.txt", "a");
            fprintf(favorite, "%s\n", walker->website);
            fprintf(favorite, "%s\n", walker->IP);
            fprintf(favorite, "%s\n", lines);
            fclose(favorite);
            break;
        }
        walker = walker->previous;
    }
    if (flag == 0) {
        printf("\t\t----------------------------------------\n");
        printf("\t\t|                                      |\n");
        printf("\t\t|        Error: Page Not Found         |\n");
        printf("\t\t|                                      |\n");
        printf("\t\t----------------------------------------\n");
        printf("\n\t\tPress Enter to Continue...\n");
        getchar();
        getchar();
    }
}

void quit (page_info **front, page_info **rear, FILE *history) {
    page_info *walker = *front;
    while (walker != NULL) {
        free (walker);
        walker = walker->next;
    }
    *front = *rear = NULL;
    history = fopen("history.txt", "w");
    fprintf(history, "");
    fclose(history);
    cls();
    printf("\t\t----------------------------------------\n");
    printf("\t\t|                                      |\n");
    printf("\t\t|        Thank you for using           |\n");
    printf("\t\t|     Our browser. Have a nice day!    |\n");
    printf("\t\t|                                      |\n");
    printf("\t\t----------------------------------------\n");
    printf("\n\t\tPress Enter to Continue...\n");
    getchar();
    exit(0);
}

void open_browser_first () {
    cls();
    printf("\t\t----------------------------------------\n");
    printf("\t\t|                                      |\n");
    printf("\t\t|    Please Open the Browser First!!   |\n");
    printf("\t\t|                                      |\n");
    printf("\t\t----------------------------------------\n");
    printf("\nPress Enter to Continue...\n");
    getchar();
    getchar();
}

void cls () {
    for (int i = 0; i < 100; i++) {
        printf("\n");
    }
}