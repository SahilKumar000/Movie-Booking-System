#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold movie details
struct Movie {
    char name[100];
    char genre[50];
    char director[50];
    int duration;
    float price;
};

// Structure to hold booking details
struct Booking {
    char movie_name[100];
    char customer_name[50];
    int num_tickets;
};

// Function to display available movies
void displayMovies() {
    FILE *fp;
    struct Movie movie;

    fp = fopen("movies.dat", "rb");
    if (fp == NULL) {
        printf("No movies available\n");
        return;
    }

    printf("Available Movies:\n");
    while (fread(&movie, sizeof(struct Movie), 1, fp)) {
        printf("%s (%s, %s) - Duration: %d min, Price: %.2f\n", movie.name, movie.genre, movie.director, movie.duration, movie.price);
    }

    fclose(fp);
}

void addMovie() {
    struct Movie movie;

    printf("Enter movie name: ");
    scanf("%s", movie.name);
    printf("Enter director name: ");
    scanf("%s", movie.director);
    printf("Enter genre: ");
    scanf("%s", movie.genre);
    printf("Enter price: ");
    scanf("%f", &movie.price);
    printf("Enter Movie Duration:");
    scanf("%d",&movie.duration);

    FILE *fp = fopen("movies.dat", "ab");
    fwrite(&movie, sizeof(struct Movie), 1, fp);
    fclose(fp);

    printf("Movie added successfully\n");
}


// Function to book tickets
void bookTicket() {
    FILE *fp;
    struct Movie movie;
    struct Booking booking;

    char movie_name[100];
    char customer_name[50];
    int num_tickets;

    printf("Enter movie name: ");
    scanf("%s", movie_name);

    fp = fopen("movies.dat", "rb");
    if (fp == NULL) {
        printf("No movies available\n");
        return;
    }

    int found = 0;
    while (fread(&movie, sizeof(struct Movie), 1, fp)) {
        if (strcmp(movie.name, movie_name) == 0) {
            found = 1;
            printf("Enter customer name: ");
            scanf("%s", customer_name);
            printf("Enter number of tickets: ");
            scanf("%d", &num_tickets);

            if (num_tickets <= 0) {
                printf("Invalid number of tickets\n");
                return;
            }

            float total_price = num_tickets * movie.price;
            printf("Total Price: %.2f\n", total_price);

            strcpy(booking.movie_name, movie.name);
            strcpy(booking.customer_name, customer_name);
            booking.num_tickets = num_tickets;

            // Save booking details to file
            FILE *fp2 = fopen("bookings.dat", "ab");
            fwrite(&booking, sizeof(struct Booking), 1, fp2);
            fclose(fp2);

            printf("Booking Successful!\n");
            break;
        }
    }

    if (!found) {
        printf("Movie not found\n");
    }

    fclose(fp);
}

// Function to view booking records
void viewBookings() {
    FILE *fp;
    struct Booking booking;

    fp = fopen("bookings.dat", "rb");
    if (fp == NULL) {
        printf("No bookings found\n");
        return;
    }

    printf("Booking Records:\n");
    while (fread(&booking, sizeof(struct Booking), 1, fp)) {
        printf("%s - %s (%d tickets)\n", booking.customer_name, booking.movie_name, booking.num_tickets);
    }

    fclose(fp);
}

// Function to cancel tickets
void cancelTicket() {
    FILE *fp;
    struct Booking booking;
    char customer_name[50];
    int found = 0;

    printf("Enter customer name: ");
    scanf("%s", customer_name);

    fp = fopen("bookings.dat", "rb");
    if (fp == NULL) {
        printf("No bookings found\n");
        return;
    }

    // Open a temporary file for writing
    FILE *temp = fopen("temp.dat", "wb");

while (fread(&booking, sizeof(struct Booking), 1, fp)) {
    if (strcmp(booking.customer_name, customer_name) == 0) {
        found = 1;
        printf("Cancelled booking for %s - %s (%d tickets)\n", booking.customer_name, booking.movie_name, booking.num_tickets);
    } else {
        fwrite(&booking, sizeof(struct Booking), 1, temp);
    }
}

if (!found) {
    printf("No bookings found for customer '%s'\n", customer_name);
}

fclose(fp);
fclose(temp);

// Replace original file with temporary file
remove("bookings.dat");
rename("temp.dat", "bookings.dat");
}
int main() {
int choice;
while (1) {
    printf("\n");
    printf("1. Display Movies\n");
    printf("2. Book Ticket\n");
    printf("3. View Bookings\n");
    printf("4. Cancel Ticket\n");
    printf("5. Add new Movie\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            displayMovies();
            break;
        case 2:
            bookTicket();
            break;
        case 3:
            viewBookings();
            break;
        case 4:
            cancelTicket();
            break;
        case 5:
            addMovie();
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("Invalid choice\n");
    }
}

return 0;
}
