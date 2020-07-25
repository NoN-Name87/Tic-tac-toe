#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Empty ' '
//prototypes
void Menu(char field[5][5]);
void Player(char field[5][5]);
void Opponent(char field[5][5]);
void Player_and_Opponent(char field[5][5]);
void Player_and_computer(char field[5][5]);
void Win_for_computer(char field[5][5]);//function that searches for winning moves
void Block_computer(char field[5][5]);//function that blocks victorious enemy moves
void Input_comp(char field[5][5]);//computer randomly selects a cell on the field
void computer(char field[5][5]);//recursive function
char Results(char field[5][5]);//checks for winning combinations
void display_table(char field[5][5]);
int Det_Win(char det);//determine the winner,returns to menu
void Inf_func(char field[5][5]);

int main()
{
    srand(time(NULL));
    char field[5][5]=
    {
        {Empty,Empty,Empty,Empty,Empty},
        {Empty,Empty,Empty,Empty,Empty},
        {Empty,Empty,Empty,Empty,Empty},
        {Empty,Empty,Empty,Empty,Empty},
        {Empty,Empty,Empty,Empty,Empty}
    };
    Menu(field);
    return 0;
}
//game modes
void Menu(char field[5][5])//game modes
{
    int opt;
    printf("1-player vs opponent 2-player vs computer.\n");
    scanf("%d",&opt);

    if(opt==1)
        Player_and_Opponent(field);

    else if(opt==2)
        Player_and_computer(field);
}

void Player_and_computer(char field[5][5])
{
    Player(field);//player move
    computer(field);//computer move
}

void Player_and_Opponent(char field[5][5])
{
    Player(field);
    Opponent(field);//opponent move
}

void Player(char field[5][5])
{
    int coord1,coord2;
    printf("x=");
    scanf("%d",&coord1);
    printf("y=");
    scanf("%d",&coord2);
    if(field[coord2-1][coord1-1]!=Empty||coord1>5||coord2>5||coord1<1||coord2<1)//if the coordinates are abroad or fills a filled cell
    Player(field);//recursion
    else
    {
        field[coord2-1][coord1-1]='X';
        Inf_func(field);//view information about field
    }
}

void Opponent(char field[5][5])
{
    int coord1,coord2;
    printf("x=");
    scanf("%d",&coord1);
    printf("y=");
    scanf("%d",&coord2);
    if(field[coord2-1][coord1-1]!=Empty||coord1>5||coord2>5||coord1<1||coord2<1)//the same case
    Opponent(field);
    else
    {
        field[coord2-1][coord1-1]='O';
        Inf_func(field);
        Player_and_Opponent(field);//recursion(player's move)
    }
}

void Win_for_computer(char field[5][5])
{

  int count;
  int save_x,save_y;
  for(int i=0;i<5;i++)
  {
      count=0;
      //line
      for(int j=0;j<5;j++)
      {
          if(field[i][j]=='X')
          {
              count=0;
              break;
          }
          else if(field[i][j]==Empty)//if ' '
          {
              save_x=j;//save coordinates to the filling
              save_y=i;
          }
          else if(field[i][j]=='O')
          {
             count++;//counts the number of characters per line
          }

      }
      if(count==4)//if the number of characters is enough to win
      {
          field[save_y][save_x]='O';
          break;//loop exit
      }
      count=0;
      //columns(The same case)
      for(int j=0;j<5;j++)
      {
          if(field[j][i]=='X')
          {
              count=0;
              break;
          }
          else if(field[j][i]==Empty)
          {
              save_y=j;
              save_x=i;
          }
          else if(field[j][i]=='O')
          {
             count++;
          }

      }
      if(count==4)
      {
          field[save_y][save_x]='O';
          break;
      }
  }
      //diagonal
      for(int j=0;j<5;j++)
      {
          if(field[j][j]=='X')
          {
              count=0;
              break;
          }
          else if(field[j][j]==Empty)
          {
              save_y=j;
              save_x=j;
          }
          else if(field[j][j]=='O')
          {
             count++;
          }
      }

  if(count==4)
  {
      field[save_y][save_x]='O';//filling
      Inf_func(field);
      Player_and_computer(field);//recursive function
  }
  else
    Block_computer(field);//block moves

}

void Block_computer(char field[5][5])
{

  int count;
  int save_x,save_y;
  for(int i=0;i<5;i++)
  {
      count=0;

      for(int j=0;j<5;j++)
      {
          if(field[i][j]=='O')
          {
              count=0;
              break;
          }
          else if(field[i][j]==Empty)
          {
              save_x=j;
              save_y=i;
          }
          else if(field[i][j]=='X')
          {
             count++;
          }

      }
      if(count==4)
      {
          field[save_y][save_x]='O';
          break;
      }
      count=0;

      for(int j=0;j<5;j++)
      {
          if(field[j][i]=='O')
          {
              count=0;
              break;
          }
          else if(field[j][i]==Empty)
          {
              save_y=j;
              save_x=i;
          }
          else if(field[j][i]=='X')
          {
             count++;
          }

      }
      if(count==4)
      {
          field[save_y][save_x]='O';
          break;
      }

  }

      for(int j=0;j<5;j++)
      {
          if(field[j][j]=='O')
          {
              count=0;
              break;
          }
          else if(field[j][j]==Empty)
          {
              save_y=j;
              save_x=j;
          }
          else if(field[j][j]=='X')
          {
             count++;
          }
      }

  if(count==4)
  {
      field[save_y][save_x]='O';
      Inf_func(field);
      Player_and_computer(field);
  }
  else
    Input_comp(field);//randomly filling a cell
}

void Input_comp(char field[5][5])
{
    int coord,coord2;
    coord2=rand()%5;
    coord=rand()%5;
    if(field[coord][coord2]==Empty)//(player(),opponent())
    {
        field[coord][coord2]='O';
        Inf_func(field);//check results
        Player_and_computer(field);//recursive function
    }
    else
        Input_comp(field);
}

void computer(char field[5][5])
{
  Win_for_computer(field);//search winning moves
}

void Inf_func(char field[5][5])
{
    char det;//value
    display_table(field);
    det=Results(field);//get value
    Det_Win(det);//determine the winner
}

void display_table(char field[5][5])
{
    printf("      1      2     3     4    5 \n");//columns(x)
    for(int i=0;i<5;i++)
    {
        printf("----------------------------------\n");
        printf("%d",i+1);//lines(y)
        for(int j=0;j<5;j++)
        {

            printf("   |%c ",field[i][j]);
        }
        printf("\n");
    }
     printf("----------------------------------\n");
}

char Results(char field[5][5])
{
    char flag,flag2,flag3,flag4;
    int em;
    for(int i=0;i<5;i++)
    {
        flag=field[i][0];//take the initial symbol of the row
        for(int j=0;j<5;j++)
        {
          if(field[i][j]!=flag||flag==Empty)//if the first element is empty or the next element is not equal to the first
          {
            flag=' ';//skip it
            break;
          }
        }
        if(flag!=' ')//otherwise
        {
            return flag;//returns the first element
        }
        flag2=field[0][i];//...of the column

       for(int j=0;j<5;j++)
        {
          if(field[j][i]!=flag2||flag2==Empty)
          {
            flag2=' ';
            break;
          }
        }
        if(flag2!=' ')
        {
            return flag2;
        }
       }
       flag3=field[0][0];//of the diagonal
       flag4=field[0][5-1];
       for(int i=0;i<5;i++)
       {
           if(field[i][i]!=flag3||flag3==Empty)
           {
               flag3=' ';
               break;
           }
       }
       if(flag3!=' ')
       {
           return flag3;
       }

       for(int i=0;i<5;i++)
       {
           if(field[i][5-1-i]!=flag4||flag4==Empty)
           {
               flag4=' ';
               break;
           }
       }
       if(flag4!=' ')
       {
           return flag4;
       }
       else//check that the array is full
        {
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    if(field[i][j]==Empty)
                    {
                        em='E';
                        break;
                    }
                    else
                        em='T';//symbol 'Tie'
                }
            }
        }
        return em;
}


int Det_Win(char det)
{
    if(det=='X')
    {
        printf("Win!\n");
        return main();//returns to the menu
    }
    else if(det=='O')
    {
        printf("Lose\n");
        return main();
    }
    else if(det=='T')
    {
        printf("Tie\n");
        return main();
    }
    return 0;
}
