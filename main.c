#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//  Global declarations
int width=20, height=20, gameOver, CountTail=0;
int x, y, fruitX, fruitY, score, flag;
int tailX[100], tailY[100];

void menu()
{
    printf("\n\t\t\t\t****** SNAKE GAME ******\n\n");
    printf(":::Main Menu:::\n\n");
    printf(" 1) Controls:\n");
    printf("        w     \n");
    printf("      a   d   \n");
    printf("        s   \n\n");
    printf("\n  Press any key to start the game");
    getche();

}

// Function to draw the boundaries
void draw()
{
    int i, j, k;

    system("cls");

    for(i=0; i<height; i++)  // from 0 to 19 = 20
    {
       for(j=0; j<width; j++)
        {
            if(i==0 || i==width-1 || j==0 || j== height-1 )
            {
                printf("#");
            }
            else
            {
                if(i == x && j == y)        /// initializing snake  at (10,10)
                    printf("O");
                else if(i == fruitX && j == fruitY)  /// initializing fruit randomly
                    printf("F");
                else
                {
                    int c=0;
                    for(k=0; k<CountTail; k++)
                    {
                        if(i==tailX[k] && j==tailY[k])
                        {
                            printf("o");
                            c = 1;
                        }
                    }
                    if(c == 0)
                        printf(" ");
                }
            }
        }
        printf("\n");
     }
     // Print the score after the game ends
     printf("SCORE = %d",score);
}

// Function to generate the fruit within the boundary
void setup()
{
    gameOver=0;                 /// from where game will start at the middle snake will be generated (10,10)
    // Stores height and width
    x = width/2;
    y = height/2;

    label1:
        fruitX = rand()%20;   /// rand function generates the fruits randomly inside the box, it will generate 20 that is the size of box fruit so we divide it by 20 to generate only 1 at a time
        if(fruitX == 0)      /// if fruits generated at the boundary it will cancel that fruit until it comes under space
            goto label1;    // if fruit generated at the boundary it will that is jump without executing and generate again

    label2:
        fruitY = rand()%20;
        if(fruitY == 0)
            goto label2;

    score = 0;               /// starting with 0 score
}

// Function to take the input
void input()
{
    if(kbhit())
    {
        switch(getch())
        {
            case 'a':        /// left
                flag = 1;
                break;
            case 's':        /// down
                flag = 2;
                break;
            case 'w':        /// up
                flag = 3;
                break;
            case 'd':        /// right
                flag = 4;
                break;
            case 'X':        /// exit
                gameOver = 1;
                break;
        }
    }
}

// Function for the logic behind each movement
void logic()
{
    int i;
        /// creating & adding tails at (x,y) coordinates
       /// Suppose head to be 0 when it eats a fruit will generate a 1 adding behind zero.
      /// That is zero will become 1 and new 0 will be generated. Now 1 shall follow the same path as 0
     /// If 1 already exists it will become 2, similarly 2 will become 3 ->0123
    int prevX = tailX[0];  // 1 moving to 2 box as 2 from x direction
    int prevY = tailY[0]; // 1 moving to 2 box as 2 from y direction
    int prev2X, prev2Y;  // to store the tail before moving it, works like temp

    /// x,y are the heads coordinates, this coordinates will be given to tail 0 to follow it
    tailX[0] = x;
    tailY[0] = y;

    for(i=1; i<CountTail; i++) // 0 zero tail is already assigned so we will start from 1, this still means 0 -> Count tail - 1
    {
      /// storing 1 index tail to prev2X, cause we already stored 0 index tail to prevX
      prev2X = tailX[i];
      prev2Y = tailY[i];

      /// stored value at prevX will now be transfered to index 1 discarding the value at index 1, mention not we already stored the index 1 value at prev2X
      tailX[i] = prevX;
      tailY[i] = prevY;

      /// prev2X value is now transfered to prevX then prevX will transfered it to respective index. Now prev2X will take new value this will continue till Count tail - 1.
      prevX = prev2X;
      prevY = prev2Y;
    }

      /// So the game starts at (0,0) on X,Y quadrant rotated 90 degree clockwise.
     /// Clicking a, w, s, d takes the value and get incremented or decremented doing so changing their position.
    switch(flag)
    {
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            x--;
            break;
        case 4:
            y++;
            break;
        default:
            break;
    }

     /// if snakes touches the walls it will change gameOver value to 1 thus changing it from 1 to 0 in while loop and stopping the game
    if(x < 0 || x > width || y < 0 || y > height)
        gameOver = 1;

    for(i=0; i<CountTail; i++)      /// if snakes touches itself gameOver will execute
    {
        if(x==tailX[i] && y==tailY[i])
            gameOver = 1;
    }

    if(x == fruitX && y == fruitY)   /// relocating the fruit every time when snakes overlap it while increasing the score
    {
        label3:
            fruitX = rand()%20;
            if(fruitX == 0)
                goto label3;

        label4:
            fruitY = rand()%20;
            if(fruitY == 0)
                goto label4;
        score += 10;
        CountTail++;
    }
}

int main()
{
    system("Color A4");
    menu();
    char ch;
    do
    {
        int m,n;
        CountTail = 0;  // setting tail to 0
        setup();

         /// at start gameOver value is 0 so it will become 1 thus it will run infinitely.
        /// When the snake hit the walls it will become 0 globally, then passed into while loop in which it changes to 0, thus stopping the game.
        while(!gameOver)
        {
            draw();
            input();
            logic();
            for(m=0;m<1000;m++) /// this function will slow the game it works like mode
                {
                for(n=0;n<100000;n++)
                    {
                    }
                }
        }
        printf ("\n\nEnter Y/y to continue: ");
        scanf (" %c", &ch);
    }while(ch == 'y' || ch == 'Y');

    return 0;
}
