/**
 * @file mazegame.c
 * @author (Mohammed Tahzim)
 * @brief Code for the maze game for COMP1921 Assignment 2
 * NOTE - You can remove or edit this file however you like - this is just a provided skeleton code
 * which may be useful to anyone who did not complete assignment 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// defines for max and min permitted dimensions
#define MAX_DIM 100
#define MIN_DIM 5

// defines for the required autograder exit codes
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3

typedef struct __Coord
{
    int x;
    int y;
} coord;

typedef struct __Maze
{
    char **map;
    int height;
    int width;
    coord start;
    coord end;
} maze;

/**
 * @brief Initialise a maze object - allocate memory and set attributes
 *
 * @param this pointer to the maze to be initialised
 * @param height height to allocate
 * @param width width to allocate
 * @return int 0 on success, 1 on fail
 */
int create_maze(maze *this, int height, int width)
{
    this->height = height;
    this->width = width;
    
    this->map = (char **)malloc(height * sizeof(char *));
    if (this->map == NULL)
    {
        return 3;
    }
    
    for (int i = 0; i < height; i++)
    {
        this->map[i] = (char *)malloc(width * sizeof(char));

        if (this->map[i] == NULL)
        {
            return 3;
        }
        
    }
    
    return 0;
}

/**
 * @brief Free the memory allocated to the maze struct
 *
 * @param this the pointer to the struct to free
 */
void free_maze(maze *this){

    for (int i = 0; i < this->height; i++)
    {
        free(this->map[i]);
    }
    free(this->map);
}

/**
 * @brief Validate and return the width of the mazefile
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid width (5-100)
 */
int get_width(FILE *file)
{
    int width = 0;
    char chr;
    while ((chr = fgetc(file)) != EOF)
    {
        width++;
    }

    if (width < MIN_DIM || width > MAX_DIM)
    {
        return 3;
    }
    return width;
}

/**
 * @brief Validate and return the height of the mazefile
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid height (5-100)
 */
int get_height(FILE *file)
{
    int height = 0;
    char chr;
    while ((chr = fgetc(file)) != EOF)
    {
        if (chr == '\n')
        {
            height++;
        }
        
    }

    
    if (height < MIN_DIM || height > MAX_DIM)
    {
        return 3;
    }
    return height;

}



/**
 * @brief read in a maze file into a struct
 *
 * @param this Maze struct to be used
 * @param file Maze file pointer
 * @return int 0 on success, 1 on fail
 */
int read_maze(maze *this, const char *file) {
    FILE *f = fopen(file, "r");
    
    if (f == NULL)
    {
        printf("Error: Failed to open file.\n");
        return 2;
    }
    
    int height = 0;
    int prev_width = -1;

    // Initializing starting and ending position
    int start_x = -1, start_y = -1; 
    int end_x = -1, end_y = -1; 
     
    char line[MAX_DIM];
    
    
    this->map = NULL;
    int max_height = 0;
    bool empty_line_encountered = false;
    while (fgets(line, sizeof(line), f) != NULL) 
    {
        int len = strlen(line);
        if (line[len - 1] == '\n')
        {
            line[len - 1] = '\0'; 
            len--;
        }
        
        // Check for empty line at the end of the file
        if (len == 0 && !empty_line_encountered) {
            empty_line_encountered = true;
            continue; 
        }

        
        if (len == 0 && empty_line_encountered) {
            printf("Error: Trailing newline found.\n");
            fclose(f);
            free(this->map);
            return 3;
        }

        // Check if every row has the same length
        if (prev_width == -1) {
            prev_width = len;
        } else if (prev_width != len) {
            printf("Error: Invalid row length.\n");
            fclose(f);
            free(this->map); 
            return 3;
        }
        
        // Check if every column has the same height
        height++;
        
        // Check for start and end positions
        for (int i = 0; i < len; i++) {
            if (line[i] == 'S') {
                start_x = i;
                start_y = height - 1;

            } else if (line[i] == 'E')
             {
                end_x = i;
                end_y = height - 1;
            } else if (line[i] != '#' && line[i] != ' ') {
                printf("Error: Invalid character in maze.\n");
                fclose(f);
                free(this->map); 
                return 3;
            }
            
        }

        // Resize map array if necessary
        if (height > max_height) {
            char **temp_map = realloc(this->map, height * sizeof(char *));
            if (temp_map == NULL) {
                printf("Error: Memory allocation failed.\n");
                fclose(f);
                free(this->map); 
                return 3;
            }
            this->map = temp_map;
            max_height = height;
        }

        // Allocate memory for the current row
        this->map[height - 1] = (char *)malloc((len + 1) * sizeof(char));
        if (this->map[height - 1] == NULL) {
            printf("Error: Memory allocation failed.\n");
            fclose(f);
            free(this->map); 
            return 3;
        }
        
        // Copy line to map
        strcpy(this->map[height - 1], line);
    }
    fclose(f);
    
    // Set maze dimensions
    this->height = height;
    this->width = prev_width;
    
    // Set start position in maze struct
    if (start_x != -1 && start_y != -1) {
        this->start.x = start_x;
        this->start.y = start_y;
    } else {
        printf("Error: Start position does not exist.\n");
        free(this->map); 
        return 3;
    }
    
    // Set end position in maze struct
    if (end_x != -1 && end_y != -1) {
        this->end.x = end_x;
        this->end.y = end_y;
    } else {
        printf("Error: End position does not exist.\n");
        free(this->map); 
        return 3;
    }
    
    // Check if dimensions are within limits
    if (prev_width < MIN_DIM || prev_width > MAX_DIM || height < MIN_DIM || height > MAX_DIM) {
        printf("Error: Maze dimensions out of bounds.\n");
        free(this->map); 
        return 3;
    }
    
    return 0;
}

/**
 * @brief Prints the maze out - code provided to ensure correct formatting
 *
 * @param this pointer to maze to print
 * @param player the current player location
 */
void print_maze(maze *this, coord *player)
{

    printf("\n");
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
    
            if (player->x == j && player->y == i)
            {
                printf("X");
            }
            else
            {
                printf("%c", this->map[i][j]);
            }
        }
        
        printf("\n");
    }

}

/**
 * @brief Validates and performs a movement in a given direction
 *
 * @param this Maze struct
 * @param player The player's current position
 * @param direction The desired direction to move in
 */
void move(maze *this, coord *player, char direction)
{
    switch (direction) {
        // For moving up
        case 'W':
        case 'w':
            if(player->y - 1 >= 0 && this->map[player->y-1][player->x]!='#'){
                player->y--;
            } 
            break;

        // For moving left
        case 'A':
        case 'a':
            if(player->x - 1 >= 0 && this->map[player->y][player->x-1]!='#'){
                player->x--;
            } 
            break;

        // For moving down
        case 'S':
        case 's':
            if(player->y + 1 < this->height && this->map[player->y+1][player->x]!='#'){
                player->y++;
            }  
            break;

        // For moving right
        case 'D':
        case 'd':
            if(player->x + 1 < this->width && this->map[player->y][player->x+1]!='#'){
                player->x++;
            } 
            break;
        // Printing maze
        case 'M':
        case 'm':
            print_maze(this, player);
            break;

        // Quit game
        case 'Q':
        case 'q':
            exit(0);

        default:
            printf("Invalid direction.\n");
            return;
    }
}



/**
 * @brief Check whether the player has won and return a pseudo-boolean
 *
 * @param this current maze
 * @param player player position
 * @return int 0 for false, 1 for true
 */
int has_won(maze *this, coord *player)
{
    if (player->x == this->end.x && player->y == this->end.y)
    {

        return true; 
    }
    return false;  
}

int main(int argc, char *argv[])
{

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    maze *this_maze = malloc(sizeof(maze));
    coord *player = malloc(sizeof(coord)); 
    
    
    if (player == NULL) 
    {
        printf("Error: Memory allocation for player failed.\n");
        return 2;
    }


    // reading the maze file
    if(read_maze(this_maze, argv[1]) != 0){
        printf("Error: Failed to read file.\n");
        return 2;
    }    

    // Initializing player positions
    player->x = this_maze->start.x;
    player->y = this_maze->start.y;

    
    char direction;
    // loop of the maze game
    while (true)
    {
        print_maze(this_maze, player);
        
        if (has_won(this_maze, player))
         {
            printf("You Won!\n");
            break;
        }
        
        // player movement input
        printf("Enter move (WASD) Q to quit, m to display maze: ");
        scanf(" %c", &direction);

        move(this_maze, player, direction);
    }

    // return, free, exit
    free_maze(this_maze);
    free(player); 

    return 0; 
}
