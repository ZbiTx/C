#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ANIMALS 100

struct Animal {
    char name[50];
    char sound[10];
    char description[200];
};

void ignoreCase(char *user_input) {
    for (int i = 0; user_input[i]; i++) {
        user_input[i] = tolower(user_input[i]);
    }
    if (user_input[0]) {
        user_input[0] = toupper(user_input[0]);
    }
}

int main() {
    struct Animal animals[MAX_ANIMALS] = {
        {"Dog", "Woof", "Household animal that shits all of the time."},
        {"Cat", "Meow", "Household animal that pisses all of the time."},
        {"Horse", "Nei", "Annoying as fuck, but fun to ride."},
        {"Penguin", "Noot", "Funny as fuck, generally great people to talk to."},
        {"Shark", "Click", "Scary as shit."},
        {"Dickhead", "Posh", "Annoying as fuck, but fun to ride."},
        {"Soraya", "Brummy", "Big eyed angry Spanish lady (approach with caution)."},
        {"Grace", "Mean", "Very sarcastic, but very kind and considerate."},
        {"Bear", "Growl", "Usually nonchalant."},
        {"Elephant", "Trumpet", "Will shit on you, if agitated."}
    };
    int animalCount = 10;

    char user_input[50];
    int user_int = 0;

    while (1) {
        printf("1 Animal Interface | 2 Animal Dictionary | 3 Add Animal | 4 Exit\n");
        printf("Enter: ");

        while (scanf("%d", &user_int) != 1) {
            printf("Incorrect data type. Please try again.\n");
            user_int = 0;
            while (getchar() != '\n');

            printf("Enter: ");
        }

        if (user_int == 1) {
            printf("Hi Grace, what animal would you like today? ");
            scanf("%s", user_input);
            ignoreCase(user_input);

            int found = 0;
            for (int i = 0; i < animalCount; i++) {
                if (strcmp(user_input, animals[i].name) == 0) {
                    for (int j = 0; j < 5; j++) {
                        printf("%s, %s!\n", animals[i].sound, animals[i].sound);
                    }
                    printf("\n");
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Sorry, I don't know that animal.\n\n");
            }
        }

        else if (user_int == 2) {
            printf("Animal   | Sound   | Description\n");
            printf("--------------------------------\n");
            for (int i = 0; i < animalCount; i++) {
                printf("%-9s| %-8s| %s\n", animals[i].name, animals[i].sound, animals[i].description);
            }
            printf("\n");
        }

        else if (user_int == 3) {
            if (animalCount >= MAX_ANIMALS) {
                printf("Sorry, you've reached the maximum number of animals.\n");
                continue;
            }

            struct Animal newAnimal;

            printf("What is the name of your animal? ");
            scanf("%s", newAnimal.name);
            ignoreCase(newAnimal.name);

            printf("What sound does your animal make? ");
            scanf("%s", newAnimal.sound);

            while (getchar() != '\n');

            printf("Provide a brief description of your animal: ");
            fgets(newAnimal.description, sizeof(newAnimal.description), stdin);
            newAnimal.description[strcspn(newAnimal.description, "\n")] = '\0';

            animals[animalCount++] = newAnimal;
            printf("Animal added successfully!\n\n");
        }
        else if (user_int == 4) {
            printf("Goodbye, Grace!\n");
            break;
        }
        else {
            printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}