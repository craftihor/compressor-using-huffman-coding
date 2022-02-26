#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int roll;
int computer_roll;

int input;

int progress;

int player = 0;

int computer = 0;


int squares[99];

void board()
{
    cout << "----------------------------------------------------------------------------"<<endl<<endl;
         cout << squares[100]<<"\t"<<squares[99]<<"\t"<<squares[98]<<"\t"<<squares[97]<<"\t"<<squares[96]<<"\t"
         <<squares[95]<<"\t"<<squares[94]<<"\t"<<squares[93]<<"\t"<<squares[92]<<"\t"<<squares[91]<<endl<<endl;

         cout << squares[81]<<"\t"<<squares[82]<<"\t"<<squares[83]<<"\t"<<squares[84]<<"\t"<<squares[85]<<"\t"
         <<squares[86]<<"\t"<<squares[87]<<"\t"<<squares[88]<<"\t"<<squares[89]<<"\t"<<squares[90]<<endl<<endl;

         cout << squares[80]<<"\t"<<squares[79]<<"\t"<<squares[78]<<"\t"<<squares[77]<<"\t"<<squares[76]<<"\t"
         <<squares[75]<<"\t"<<squares[74]<<"\t"<<squares[73]<<"\t"<<squares[72]<<"\t"<<squares[71]<<endl<<endl;

         cout << squares[61]<<"\t"<<squares[62]<<"\t"<<squares[63]<<"\t"<<squares[64]<<"\t"<<squares[65]<<"\t"
         <<squares[66]<<"\t"<<squares[67]<<"\t"<<squares[68]<<"\t"<<squares[69]<<"\t"<<squares[70]<<endl<<endl;

         cout << squares[60]<<"\t"<<squares[59]<<"\t"<<squares[58]<<"\t"<<squares[57]<<"\t"<<squares[56]<<"\t"
         <<squares[55]<<"\t"<<squares[54]<<"\t"<<squares[53]<<"\t"<<squares[52]<<"\t"<<squares[51]<<endl<<endl;

         cout << squares[41]<<"\t"<<squares[42]<<"\t"<<squares[43]<<"\t"<<squares[44]<<"\t"<<squares[45]<<"\t"
         <<squares[46]<<"\t"<<squares[47]<<"\t"<<squares[48]<<"\t"<<squares[49]<<"\t"<<squares[50]<<endl<<endl;

         cout << squares[40]<<"\t"<<squares[39]<<"\t"<<squares[38]<<"\t"<<squares[37]<<"\t"<<squares[36]<<"\t"
         <<squares[35]<<"\t"<<squares[34]<<"\t"<<squares[33]<<"\t"<<squares[32]<<"\t"<<squares[31]<<endl<<endl;

         cout << squares[21]<<"\t"<<squares[22]<<"\t"<<squares[23]<<"\t"<<squares[24]<<"\t"<<squares[25]<<"\t"
         <<squares[26]<<"\t"<<squares[27]<<"\t"<<squares[28]<<"\t"<<squares[29]<<"\t"<<squares[30]<<endl<<endl;

         cout << squares[20]<<"\t"<<squares[19]<<"\t"<<squares[18]<<"\t"<<squares[17]<<"\t"<<squares[16]<<"\t"
         <<squares[15]<<"\t"<<squares[14]<<"\t"<<squares[13]<<"\t"<<squares[12]<<"\t"<<squares[11]<<endl<<endl;

         cout << squares[1]<<"\t"<<squares[2]<<"\t"<<squares[3]<<"\t"<<squares[4]<<"\t"<<squares[5]<<"\t"
         <<squares[6]<<"\t"<<squares[7]<<"\t"<<squares[8]<<"\t"<<squares[9]<<"\t"<<squares[10]<<endl<<endl;
    cout << "----------------------------------------------------------------------------"<<endl;
}

int check_progress()
{
    if ( squares[100] == 200 || squares[100] == 300)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int roll_dice()
{
    return rand() % (7-1) + 1;
}

int main()
{
    srand( time(NULL) );

    string alert = "";
    string computer_alert = "";

    cout << "Welcome to snakes and ladders, enter any number to roll dice, press 0 to quit\n\n";
    cout << "SNAKES\tLADDERS\n99-5\t4-36\n93-25\t8-28\n77-9\t20-41\n52-6\t35-67\n30-2\t45-66\n\n";

    for ( int i = 1; i <= 100; i++)
        {
            squares[i] = i;
        }

    do
    {
        cout << "enter: ";
        cin >> input;

        roll = roll_dice();

        if( (roll + player) > 100)
        {
            player = player;
        }
        else
        {
            squares[player] = player;
            player = player + roll;
        }

        computer_roll = roll_dice();

        if( (computer_roll + computer) > 100)
        {
            computer = computer;
        }
        else
        {
            squares[computer] = computer;
            computer = computer + computer_roll;
        }

        switch(player)
        {
            case 99:
            player = 5;
            alert = "OOPS... You ran into a SNAKE!";
            break;

            case 93:
            player = 25;
            alert = "OOPS... You ran into a SNAKE!";
            break;

            case 77:
            player = 9;
            alert = "OOPS... You ran into a SNAKE!";
            break;

            case 52:
            player = 6;
            alert = "OOPS... You ran into a SNAKE!";
            break;

            case 30:
            player = 2;
            alert = "OOPS... You ran into a SNAKE!";
            break;

            case 45:
            player = 66;
            alert = "YAY! you climbed a ladder!!!";
            break;

            case 35:
            player = 67;
            alert = "YAY! you climbed a ladder!!!";
            break;

            case 20:
            player = 41;
            alert = "YAY! you climbed a ladder!!!";
            break;

            case 8:
            player = 28;
            alert = "YAY! you climbed a ladder!!!";
            break;

            case 4:
            player = 36;
            alert = "YAY! you climbed a ladder!!!";
            break;

            default:
            alert = "";

        }

        switch(computer)
        {
            case 99:
            computer = 5;
            computer_alert = "OOPS... Computer ran into a SNAKE!";
            break;

            case 93:
            computer = 25;
            computer_alert = "OOPS... Computer ran into a SNAKE!";
            break;

            case 77:
            computer = 9;
            computer_alert = "OOPS... Computer ran into a SNAKE!";
            break;

            case 52:
            computer = 6;
            computer_alert = "OOPS... Computer ran into a SNAKE!";
            break;

            case 30:
            computer = 2;
            computer_alert = "OOPS... Computer ran into a SNAKE!";
            break;

            case 45:
            computer = 66;
            computer_alert = "HAHA! computer climbed a ladder!!!";
            break;

            case 35:
            computer = 67;
            computer_alert = "HAHA! computer climbed a ladder!!!";
            break;

            case 20:
            computer = 41;
            computer_alert = "HAHA! computer climbed a ladder!!!";
            break;

            case 8:
            computer = 28;
            computer_alert = "HAHA! computer climbed a ladder!!!";
            break;

            case 4:
            computer = 36;
            computer_alert = "HAHA! computer climbed a ladder!!!";
            break;

            default:
            computer_alert = "";
        }

        squares[player] = 200;
        squares[computer] = 300;

        if ( input != 0)
        {
            cout<<"You rolled "<<roll<<"\nComputer rolled "<<computer_roll<<endl;
            cout<<"Your Position: "<<player<<"\nComputer's Position: "<<computer<<endl;
            cout <<alert<<endl;
            cout <<computer_alert<<endl;

            board();
            cout << "SNAKES\tLADDERS\n99-5\t4-36\n93-25\t8-28\n77-9\t20-41\n52-6\t35-67\n30-2\t45-66\n\n";
        }

        progress = check_progress();

    }
    while ( progress == 0 && input != 0 );

    if ( squares[100] == 200)
    {
        cout << "||You Win!||"<<endl;
    }
    else if ( squares[100] == 300)
    {
        cout << "||Game Over Computer Wins!"<<endl;
    }
    else
    {
        cout << "You Quit!";
    }

    cin.get();
    cin.ignore();
}
