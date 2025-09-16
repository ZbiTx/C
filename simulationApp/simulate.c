#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer_utils.h" 
#include <termios.h>
#include <unistd.h>

int detect_at_symbol(char* foo, size_t size) {
    int counter = 0;
    for (int i=0; i < size; i++) {
        if(foo[i] == '@') {
            counter++;
            if (i == 0 || foo[i+1] == '\0') {
                printf("\033[31m'@' in the wrong position!\033[0m\n");
                return 1;
            }
        }
    }

    if (counter == 0) {
        printf("\033[31m'@' is missing!\033[0m\n");
        return 1;
    }
    else if (counter > 1) {
        printf("\033[31m'@' appears more than once!\033[0m\n");
        return 1;
    }

    return 0;
}

void detect_gaps(char* foo, size_t size) {
    if(fgets(foo, size, stdin) != NULL) {
        foo[strcspn(foo, "\n")] = '\0';
        rplcgaps(foo); // rplc = replace (if you didn't read the header file)
    }
    else {
        printf("Error processing: %s\n", foo);
    }
}

// I didn't create this function, but I will try to explain it the best I can!
void get_password(char* bar, size_t size) {
    struct termios oldt, newt; // Defines the old and new terminal settings 
    tcgetattr(STDIN_FILENO, &oldt); // Gets the current terminal setting to store in the old
    newt = oldt; // Makes a copy of the old terminal settings
    newt.c_lflag &= ~(ECHO); // Disables echo (stops characters from being printed automattically)
    newt.c_lflag &= ~(ICANON); // Disables icanon (stops line buffering, so input is available char-by-char)
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Applies new settings immediately

    size_t i = 0;
    int ch; 
    // The while loop condition: while i < size of password-1 (index size 0...n) and enter key isn't pressed and character isn't overwritten
    while (i < size-1 && (ch = getchar()) != '\n' && ch != '\r') {
        if (ch == 127 || ch == '\b') { // 127 = ascii delete key and \b is the C backspace 
            if (i > 0) { // ensures you can't delete when no characters are present
                i--; // deletes characters (back-end)
                printf("\b \b"); // visually deletes the asterisk symbol (front-end)
                fflush(stdout); // flush the standard output
            }
        }
        else { // if backspace is not pressed
            bar[i++] = (char)ch; // accept printable ascii chars
            printf("•"); // visually show user input as the asterisk symobl
            fflush(stdout); // flush the standard output
        }
    }
    bar[i] = '\0'; // Null-terminate the string

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore original terminal settings before exit (safety reasons)
    printf("\n");
}

int main() {
	int buffer;

	char ad[5][50] = {"Free iPhone 13 Pro Max!!",
    "Learn C today, and become a low level god!",
    "Buy one, get one free!",
    "Your parcel is 4km away!", 
    "Enhance your security, use linux today!"};

    char error[5][50] = {"\033[31mError has occured.\033[0m",
    "\033[31mError 404\033[0m",
    "\033[31mUnknown Error.\033[0m",
    "\033[31mEnter in the format: name@example.com\033[0m",
    "\033[31mInvalid Integer Error.\033[0m"};

	while(1) {	
	    int rd = rand() % 5; // random integer between 0-4
		printf("1. Simulate Erorr Message\n"
               "2. Simulate Ad Message\n"
               "3. Simulate Email\n"
               "4. Simulate Password Login\n"
               "5. Exit\n"
               "Enter: ");

		scanf("%d", &buffer);
        clear_buffer();

        switch (buffer) {
            case 1:
                printf(error[rd]);
                break;
            case 2:
                printf(ad[rd], "\a");
                break;
            case 3:
                char sender[50];
			    char recipient[50];
			    char msg[1000];

			    do {
                    printf("Your email address: ");
                    if (scanf("%99s", sender) != 1) {
                        return 1;
                    }
                } while (detect_at_symbol(sender, sizeof sender) == 1);

                do {
                    printf("Recipient email address: ");
                    if (scanf("%99s", recipient) != 1) {
                        return 1;
                    }               
                    if (strcmp(recipient, sender) == 0) {
                        printf("\033[31mYou can't send an email to yourself!\033[0m\n");
                    }
                } while (detect_at_symbol(recipient, sizeof recipient) == 1 || strcmp(recipient, sender) == 0);

                clear_buffer();

                printf("Your message: ");
			    fgets(msg, 1000, stdin);
            
	            printf("Email sent from: %s\nRecipient: %s\n%s\a", sender, recipient, msg);
                break;
             case 4:
                char username[64];
                char passwd[64];
                char temp_username[64];
                char temp_passwd[64];

                printf("Register terminal\n"
                        "Username: ");
                detect_gaps(username, sizeof username);

                printf("Password: ");
                detect_gaps(passwd, sizeof passwd);

                printf("\nLogin terminal\n");
                while (strcmp(temp_username, username) != 0) {
                    printf("Username: ");
                    detect_gaps(temp_username, sizeof temp_username);

                    if (strcmp(temp_username, username) != 0) {
                        printf("\033[31mUser %s is not found on the database\033[0m\n", temp_username);
                    }
                }
                while (strcmp(temp_passwd, passwd) != 0) {
                    printf("Password: ");
                    get_password(temp_passwd, sizeof temp_passwd);
                    // detect_gaps(temp_passwd, sizeof temp_passwd);

                    if (strcmp(temp_passwd, passwd) != 0) {
                        printf("\033[31mIncorrect password for user: %s, please try again.\033[0m\n", username);
                    }
                }

                printf("\033[1;32mSuccessfully logged into account:\033[0m %s", username);

                strcpy(temp_username, "");
                strcpy(temp_passwd, "");
                break;
             case 5:
                return 0;
             default:
                printf(error[4]); // prints "Invalid Integer Error"
        }	
        printf("\n\n");
    }
}
