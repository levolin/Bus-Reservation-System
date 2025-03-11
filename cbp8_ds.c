#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#define MAX_SEATS 20
#define MAX_REVIEWS 5
#define MAX 29

// Structure for storing passenger details
struct node {
	char start[MAX];
	char stoploc[MAX];
    int bus_no;
    char passen_name[30];
    char passen_gender[10];
    int passen_age;
    int seat_no;
    float t;
    char busname[30];
    struct node *next;
    int line1;
    int line2;
};

// Structure for storing reviews
struct review {
    int rating;
    char rev[50];
    int busno;
}*stack[5];
// Enumerator
enum IN { 
    IN_BACK = 8, 
    IN_RET = 13 
};
int sno,rating;
// Global variables for bus data and counters
struct node *bus1 = NULL, *bus2 = NULL, *bus3 = NULL, *bus4 = NULL, *bus5 = NULL, *bus6 = NULL;
int top = -1;
int line1,line2;

// Function to clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void asterick_conv(char *passwd, char sp) {
    int index = 0;
    char ch;

    while (1) {
        ch = getch();

        // If Enter key is pressed
        if (ch==IN_RET) {
            printf("\n");
            passwd[index]='\0';
            return;
        }
        // If Backspace is pressed and password length is not zero
        else if (ch==IN_BACK && index!=0) {
            index--;
            passwd[index] = '\0';

            // Erase the character on the console
            printf("\b \b");
        }
        // If Backspace is pressed and password length is zero
        else if (ch==IN_BACK && index==0) {
            continue;
        }
        // For other characters
        else {
            passwd[index++]=ch;
            printf("%c", sp);
        }
    }
}

void reviews(int busnum){
		struct review*nn;
		nn=(struct review*)malloc(sizeof(struct review));
		printf("Please give your rating out of 5. ");
		scanf("%d",&nn->rating);
		printf("Please tell us about your experience. Enter $ to stop input ");
		scanf("%[^$]s",&nn->rev);
		nn->busno=busnum;
		clear_input_buffer();
		stack[++top]=nn;
	}
void review_display(){
		struct review*temp;
		int t=top;
		while(t!=-1)
		{
			temp=stack[t--];
			printf("*--*-*-*--*--*-*-*--*\n");
			printf("Bus Number: %d\n",temp->busno);
			printf("Rating: %d\n",temp->rating);
			printf("Review: %s\n",temp->rev);
			printf("*--*-*-*--*--*-*-*--*\n");
		}
	}
void deletion(struct node*bus, int seat, int busno) {
    struct node *temp, *prev, *first = NULL;

    switch(busno) {
        case 1: first = bus1; break;
        case 2: first = bus2; break;
        case 3: first = bus3; break;
        case 4: first = bus4; break;
        case 5: first = bus5; break;
        case 6: first = bus6; break;
    }

    temp = first;
    prev = NULL;

    while (temp != NULL && temp->seat_no != seat) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid cancellation. Seat not booked.\n");
        printf("-----------------------------------------------------------\n");
    } else {
        if (prev == NULL) {
            first = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        printf("\nSeat number %d has been cancelled\n", seat);
        printf("-----------------------------------------------------------\n");
        switch(busno) {
            case 1: bus1 = first; break;
			case 2: bus2 = first;break;
            case 3: bus3 = first;break;
            case 4: bus4 = first; break;
            case 5: bus5 = first; break;
            case 6: bus6 = first; break;
        }
    }
}
void fare_amount(struct node*nn)
{
	float fare,sourcedist,destdist;
	FILE*fp=fopen("distances.txt","r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[256];
    int current_line = 1;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (current_line == line1) {
            // Convert buffer to float
            sourcedist = strtof(buffer, NULL);
            if (sourcedist == 0.0f && buffer[0] != '0') {
                printf("Error converting line %d to float.\n", line1);
            }
            fclose(fp);
            break;
        }
        current_line++;
    }

    // If we reach here, the line was not found
    if (current_line < line1) {
        printf("Line %d does not exist in the file.\n", line1);
    }

    fclose(fp);
    
    fp=fopen("distances.txt","r");
        if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    current_line = 1;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (current_line == line2) {
            // Convert buffer to float
            destdist = strtof(buffer, NULL);
            if (destdist == 0.0f && buffer[0] != '0') {
                printf("Error converting line %d to float.\n", line2);
            }
            fclose(fp);
            break;
        }
        current_line++;
    }

    // If we reach here, the line was not found
    if (current_line < line2) {
        printf("Line %d does not exist in the file.\n", line2);
    }

    fclose(fp);
    fare=fabs(destdist-sourcedist)*9;
    fare+=0.18*fare;
    printf("fare = %0.2f\n",fare);
    nn->t=fare;
}
int payment(){ //return flag
	int bank,t=3,flag =0;
	char bank_number[17],pwd[15];
	printf("Please enter your payment details. ");
	printf("select your bank:\n1.HDFC 2.SBI 3.ICICI 4.Kotak Mahindra 5.Axis 6.Mastercard 7.American Express ");
	clear_input_buffer;
	scanf("%d",&bank);
	if(bank<=7&&bank>0)
	{
		while(t--){
			clear_input_buffer();
			printf("Enter the 16 digit bank number: ");
			scanf("%s",bank_number);
			clear_input_buffer();
			printf("Enter the password: ");
			asterick_conv(pwd,'*');
			//scanf("%s",pwd);
		if ((strcmp(bank_number, "SBIN16843M893544") == 0 && strcmp(pwd, "Sunshine1999") == 0) ||
    	(strcmp(bank_number, "HDFC15836P794690") == 0 && strcmp(pwd, "Cryptic&88$") == 0) ||
    	(strcmp(bank_number, "ICIC25436T130504") == 0 && strcmp(pwd, "Jubilee36#") == 0) ||
    	(strcmp(bank_number, "KTMH13838H488480") == 0 && strcmp(pwd, "Cascade!2") == 0) ||
    	(strcmp(bank_number, "AXIS15836P578291") == 0 && strcmp(pwd, "75Echo!") == 0) ||
    	(strcmp(bank_number, "MAST73636A642370") == 0 && strcmp(pwd, "89Aurora") == 0) ||
    	(strcmp(bank_number, "AMEX42736L640198") == 0 && strcmp(pwd, "78Catnip") == 0))
			{
			printf("Please wait while we are processing your transaction\n\n");
			printf("Seat number: %d is booked successfully\n", sno);
    		printf("------------------------------------------------------------\n");
    		flag=1;
    		return flag;
			}
			else
				printf("The details you have entered are wrong. You have %d more tries.",t);
		}
		printf("\nYou have made three wrong attempts.\nExiting payment.");
		return flag;
	}
}
// Function to create a new passenger record
struct node *create(struct node *head, int bno) {
    struct node *nn, *temp, *prev;
    int i, op, stopno, f, totalstops, totalfare, b;
    nn = (struct node *)malloc(sizeof(struct node));
    char s_input[MAX];
    char d_input[MAX];
    char line[MAX];
    FILE *file;
    int flag=0;
    char source[MAX];
    char destination[MAX];
	//for the source location
	while(1)
	{
		fflush(stdin);
        line1 = 0;  // Reset line number for each new search
        flag = 0;  // Reset flag for each new search
        
		// Get the string from the user
    	printf("Enter your source location: ");
    	fgets(s_input, sizeof(s_input), stdin);
    	// Remove the newline character if it exists
    	s_input[strcspn(s_input, "\n")] = 0;
	
	    // Open the file for reading
	    file = fopen("sources.txt", "r");
	    if (file == NULL) {
	        perror("Unable to open the sources file");
	        continue;
    	}

	    // Read the file line by line and search for the string
    	while (fgets(line, sizeof(line), file)) {
            line1++;
            line[strcspn(line, "\n")] = 0;  // Remove trailing newline
            if (strstr(line, s_input) != NULL) {
                flag = 1;
                break;
            }
    	}
	
    	// Close the file
    	fclose(file);
    	if(flag)
		{
			strcpy(source,s_input);
			printf("Source = %s\n",source);	
			break;
		}
		else 
		{
       		printf("The Source you have selected is not available.\n");
       		printf("Would you like you select again? 0/1 ");
       		scanf("%d",&op);
            clear_input_buffer();
			if(op==0)
				break;
			else
				continue;
		}
	}
	nn->line1=line1;
	flag=0;
	//for destination
	while(1)
	{
		fflush(stdin);
        line2 = 0;  // Reset line number for each new search
        flag = 0;  // Reset flag for each new search
        
    	printf("Enter your destination location: ");
    	fgets(d_input, sizeof(d_input), stdin);
       	d_input[strcspn(d_input, "\n")] = 0;
	
	    file = fopen("sources.txt", "r");
	    if (file == NULL) {
	        perror("Unable to open the sources file");
    	}

    	while (fgets(line, sizeof(line), file)) {
            line2++;
            line[strcspn(line, "\n")] = 0;  // Remove trailing newline
            if (strstr(line, d_input) != NULL) {
                flag = 1;
                break;
            }
    	}
	
    	fclose(file);
    		if(flag && strcmp(source,d_input)!=0)
			{	strcpy(destination,d_input);
				printf("Destination = %s\n",destination);	
				break;
			}
			else if(flag && strcmp(source,d_input)==0)
			{
				printf("You cannot select the same location as source and destination\n");
				flag=0;
				continue;
			}
			else 
			{
        		printf("The destination you have selected is not available.\n");
        		printf("Would you like you select again? 0/1 ");
        		scanf("%d",&op);
	            clear_input_buffer();
				if(op==0)
					break;
				else
					continue;
   			}
		}
		nn->line2=line2;
		strcpy(nn->start,source);
		strcpy(nn->stoploc,destination);
   		nn->next = NULL;

    // Assign bus name based on user input
    switch (bno) {
        case 1: strcpy(nn->busname, "ABHIBUS"); break;
        case 2: strcpy(nn->busname, "REDBUS"); break;
        case 3: strcpy(nn->busname, "RAJDHANI"); break;
        case 4: strcpy(nn->busname, "GARUDA"); break;
        case 5: strcpy(nn->busname, "TSRTC"); break;
        case 6: strcpy(nn->busname, "LUXURY"); break;
    }

    // Accept passenger details
    printf("Enter passenger name: ");
    scanf("%s", nn->passen_name);

    printf("Enter passenger age (6-85): ");
    scanf("%d", &nn->passen_age);

    while (nn->passen_age < 6 || nn->passen_age > 85) {
        printf("Invalid age. Please enter a valid age between 6 and 85: ");
        scanf("%d", &nn->passen_age);
    }

    printf("Enter passenger gender (Male/Female/Other): ");
    scanf("%s", nn->passen_gender);
    strlwr(nn->passen_gender);

    while (strcmp(nn->passen_gender, "male") != 0 && strcmp(nn->passen_gender, "female") != 0 && strcmp(nn->passen_gender, "other") != 0) {
        printf("Invalid gender. Please enter 'male', 'female', or 'other': ");
        scanf("%s", nn->passen_gender);
        strlwr(nn->passen_gender);
    }

    // Input seat number
    printf("Enter seat number (1-20): ");
    scanf("%d", &nn->seat_no);

    // Validate seat number
    while (nn->seat_no < 1 || nn->seat_no > 20) {
        printf("Invalid seat number. Please enter a seat number between 1 and 20: ");
        scanf("%d", &nn->seat_no);
    }
	sno=nn->seat_no;
    // Insert the passenger record into the linked list in sorted order by seat number
    if (head == NULL || nn->seat_no < head->seat_no) {
        nn->next = head;
        head = nn;
    } else {
        temp = head;
        while (temp != NULL && nn->seat_no > temp->seat_no) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = nn;
        nn->next = temp;
    }
    fare_amount(nn);
    return head;
}

// Main function to drive the program
void bookingtickets() {
    int ch, b, stopno,flag,op;
    struct node *ptr;

    // Display available services (excluding bus numbers)
    printf("Available services:\n");
    printf("1. ABHIBUS\n");
    printf("2. REDBUS\n");
    printf("3. RAJDHANI\n");
    printf("4. GARUDA\n");
    printf("5. TSRTC\n");
    printf("6. LUXURY\n");

    // Input service choice
    printf("Enter your choice: ");
    scanf("%d", &b);

    switch (b) {
        case 1: bus1 = create(bus1, b); break;
        case 2: bus2 = create(bus2, b); break;
        case 3: bus3 = create(bus3, b); break;
        case 4: bus4 = create(bus4, b); break;
        case 5: bus5 = create(bus5, b); break;
        case 6: bus6 = create(bus6, b); break;
        default: printf("Invalid choice!\n");
    }
	flag=payment();
    if(flag){
		printf("\nWould you like to leave a review? 1/0 ");
	    while(1){
	    scanf("%d",&op);
	    if(op==1)
	    {
	    reviews(b);
		return;	    	
		}
	    else if(op==0)
	    return;
	    else
		printf("Invalid option. Please enter 1 or 0 ");
		}    	
	}
	if(flag==0)
	{
    switch(b) {
        case 1: deletion(bus1,sno,b); break;
        case 2: deletion(bus2,sno,b); break;
        case 3: deletion(bus3,sno,b); break;
        case 4: deletion(bus4,sno,b); break;
        case 5: deletion(bus5,sno,b); break;
        case 6: deletion(bus6,sno,b); break;
		}
	}
}
void timefun() {
    // Get the current UTC time
    time_t rawtime;
    struct tm *utc_timeinfo, ist_timeinfo;

    time(&rawtime);
    utc_timeinfo = gmtime(&rawtime); // Convert to UTC time format

    // Adjust UTC time to IST time (UTC + 5 hours 30 minutes)
    ist_timeinfo = *utc_timeinfo;
    ist_timeinfo.tm_hour = (ist_timeinfo.tm_hour + 5) % 24;
    ist_timeinfo.tm_min = (ist_timeinfo.tm_min + 30) % 60;
    if (ist_timeinfo.tm_min < 30) {
        ist_timeinfo.tm_hour = (ist_timeinfo.tm_hour + 1) % 24;
    }

    // Buffer to hold the formatted time string
    char buffer[80];

    // Format the time as 12-hour time with AM/PM
    strftime(buffer, sizeof(buffer), "\t\ Receipt printed at %I:%M:%S %p", &ist_timeinfo);

    // Print the formatted time
    printf("%s\n", buffer);
}

void ticket(){      //function to print the ticket
	int busno,seat,flag=0;
	struct node *temp;
	printf("Choose bus service and seat number\n");
	scanf("%d %d",&busno,&seat);
	switch(busno){
		case 1:temp=bus1;
	
		break;
		case 2:temp=bus2;
		
		break;
		case 3:temp=bus3;
		
		break;
		case 4:temp=bus4;
			
		break;
		case 5:temp=bus5;
		
		break;
		case 6:temp=bus6;
		
		break;
	}
	while(temp!=NULL){
		if(seat==temp->seat_no){
			flag=1;
			break;
		}
		else{
			temp=temp->next;
		}
	}
	if(flag==1){
	printf("\t*****************************************\n");
	printf("\t\tVJ BUS SERVICES\n");
	printf("\t\tYOUR TICKET\n");
	printf("\t-----------------------------------------\n\n\t Your Ticket Details");
	printf("\n\t\tName: %s\n\t\tAge: %d\n\t\tGender: %s\n\t\tSource: %s\n\t\tDestination: %s\n\t\tBus Service: %s\n\t\tSeat number: %d\n\t\tTotal fare: %0.2f\n",temp->passen_name,temp->passen_age,temp->passen_gender,temp->start,temp->stoploc,temp->busname,temp->seat_no,temp->t);
	printf("\t-----------------------------------------\n\n");
	timefun();
	printf("\t-----------------------------------------\n\n");
	printf("\t\t\tTHANK YOU!\n");
	printf("\t*****************************************\n");
	}
	else{
	printf("Ticket not booked\n");
	}
}
void cancel_ticket() {
    int busno, seat;
    struct node *temp, *prev, *first = NULL;

  	printf("Select the service : \n");
    printf("1. ABHIBUS\n");
    printf("2. REDBUS\n");
    printf("3. RAJDHANI\n");
    printf("4. GARUDA\n");
    printf("5. TSRTC\n");
    printf("6. LUXURY\n");

    scanf("%d", &busno);
    while (busno > 6 || busno < 1) {
	printf("Invalid Bus number. Please enter a number from 1-6\n");
        scanf("%d",&busno);
    }
        switch(busno) {
        case 1: first = bus1; break;
        case 2: first = bus2; break;
        case 3: first = bus3; break;
        case 4: first = bus4; break;
        case 5: first = bus5; break;
        case 6: first = bus6; break;
    }

    printf("Enter seat number to cancel (1-20)\n");
    scanf("%d", &seat);
      while (seat > 20 || seat < 1) {
        printf("Invalid seat number.Please enter a number from 1-20\n");
        scanf("%d",&seat);
	}

    temp = first;
    prev = NULL;

    while (temp != NULL && temp->seat_no != seat) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid cancellation. Seat not booked.\n");
        printf("-----------------------------------------------------------\n");
    } else {
        if (prev == NULL) {
            first = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        printf("Seat number: %d is cancelled successfully\n", seat);
        printf("-----------------------------------------------------------\n");
        switch(busno) {
            case 1: bus1 = first; break;
			case 2: bus2 = first; break;
            case 3: bus3 = first; break;
            case 4: bus4 = first; break;
            case 5: bus5 = first; break;
            case 6: bus6 = first; break;
        }
    }
}

void bus_status() {
    int busno, c=0,line1,line2;
    struct node *nn;
    char s_input[MAX];
    char d_input[MAX];
    char line[MAX];
    FILE *file;
    int flag=0,op;
    char source[MAX];
    char destination[MAX];
    printf("Available services:\n");
    printf("1. ABHIBUS\n");
    printf("2. REDBUS\n");
    printf("3. RAJDHANI\n");
    printf("4. GARUDA\n");
    printf("5. TSRTC\n");
    printf("6. LUXURY\n");

    scanf("%d", &busno);

    switch(busno) {
        case 1: nn = bus1; break;
        case 2: nn = bus2; break;
        case 3: nn = bus3; break;
        case 4: nn = bus4; break;
        case 5: nn = bus5; break;
        case 6: nn = bus6; break;
        default: printf("Invalid Bus Number. Choose any route between 1-6 .\n"); return;
    }
	//for the source location
	while(1)
	{
		fflush(stdin);
        flag = 0;  // Reset flag for each new search
        
		// Get the string from the user
    	printf("Enter your source location: ");
    	fgets(s_input, sizeof(s_input), stdin);
    	// Remove the newline character if it exists
    	s_input[strcspn(s_input, "\n")] = 0;
	
	    // Open the file for reading
	    file = fopen("sources.txt", "r");
	    if (file == NULL) {
	        perror("Unable to open the sources file");
	        continue;
    	}

		line1=0;
	    // Read the file line by line and search for the string
    	while (fgets(line, sizeof(line), file)) {
            line1++;
            line[strcspn(line, "\n")] = 0;  // Remove trailing newline
            if (strstr(line, s_input) != NULL) {
                flag = 1;
                break;
            }
    	}
    	fclose(file);
    	if(flag)
    		break;
    	else
    		printf("The source you have selected is not available. \n");
	}
	while(1)
	{
		fflush(stdin);
        flag = 0;  // Reset flag for each new search
        
		// Get the string from the user
    	printf("Enter your destination location: ");
    	fgets(d_input, sizeof(d_input), stdin);
    	// Remove the newline character if it exists
    	d_input[strcspn(d_input, "\n")] = 0;
	
	    // Open the file for reading
	    file = fopen("sources.txt", "r");
	    if (file == NULL) {
	        perror("Unable to open the sources file");
	        continue;
    	}

		line2=0;
	    // Read the file line by line and search for the string
    	while (fgets(line, sizeof(line), file)) {
            line2++;
            line[strcspn(line, "\n")] = 0;  // Remove trailing newline
            if (strstr(line, d_input) != NULL) {
                flag = 1;
                break;
            }
    	}	
    	// Close the file
    	fclose(file);
    	if(flag)
		{
			break;
		}
		else 
		{
       		printf("The destination you have selected is not available.\n");
		}
	}
	
	while(nn!=NULL)
	{
		if(nn->line1==line1&&nn->line2==line2)
		{
			c++;
			printf("Seat no.: %d\n",nn->seat_no);
		}
		nn=nn->next;
	}
	printf("Available number of seats: %d\n",20-c);
}
void main()
{
    int op;                                         
    printf("* WELCOME TO VJ BUS SERVICES *\n");
    do { 
        printf("Please select your choice :\n\t1: Book tickets\n\t2: Bus status\n\t3: Cancel ticket\n\t4: See reviews\n\t5: Online Ticket\n\t6: Exit\n");
        scanf("%d", &op);
        clear_input_buffer();
        switch(op) 
		{
            case 1: bookingtickets(); break;
            case 2: bus_status(); break;
            case 3: cancel_ticket(); break;
            case 4: review_display();break;
            case 5: ticket();break;
            case 6: printf("Thank you for choosing VJ BUS SERVICES \nExiting the program\n"); break; 
            default: printf("Invalid option\n");
        }
    } while (op != 6);
}
