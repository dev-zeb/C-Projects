/** Data Structure LAB Project
    By - Sufi Aurangzeb Hossain
       ID : 011 172 125   */

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct USERS
{
    char name[30];
    char city[20];
    int birth_year;
    int common_friend_counter;
    struct USERS *next, *down, *back;
}*head = NULL, *temp = head, *prev = head, *temp_last, *common_friend_list = NULL, *temp_common = common_friend_list;

typedef struct USERS users;

int add_user()
{
    int c = 0;
    users *temp_check;
    if(head == NULL)
    {
        head = new users();
        printf(" ~ Please enter data of the user\n");
        printf(" ~ Enter User Name : ");
        getchar();
        gets(head->name);
        printf(" ~ Enter City Name : ");
        gets(head->city);
        printf(" ~ Enter BirthYear : ");
        scanf("%d", &head->birth_year);
        if(head->birth_year > 2005)
        {
            head = NULL;
            return 0;
        }
        else
        {
            head->next = NULL;
            head->back = NULL;
            head->down = NULL;
            prev = head;
            head->common_friend_counter = 0;///
            return 1;
        }
    }
    else
    {
        temp = new users();
        printf(" ~ Please enter data of the user\n");
        printf(" ~ Enter User Name : ");
        getchar();
        gets(temp->name);
        printf(" ~ Enter City Name : ");
        gets(temp->city);
        printf(" ~ Enter BirthYear : ");
        scanf("%d", &temp->birth_year);
        getchar();

        temp_check = head;
        while(temp_check != NULL)
        {
            if(!strcmp(temp_check->city, temp->city) && !strcmp(temp_check->name, temp->name) && (temp_check->birth_year == temp->birth_year))
            {
                c++;
                break;
            }
            temp_check = temp_check->next;
        }
        if(c == 1)
            return -1;
        if(temp->birth_year > 2005)
        {
            delete(temp);
            return 0;
        }
        else
        {
            prev->next = temp;
            temp->back = prev;
            temp->next = NULL;
            temp->down = NULL;
            prev = temp;
            temp->common_friend_counter = 0;///
            return 1;
        }
    }
}
void remove_from_friend_lists(char name[])
{
    users *temp = head, *temp_d, *temp_to_del;
    while(temp != NULL)
    {
        temp_d = temp;
        while(temp_d->down != NULL)
        {
            if(!strcmp(temp_d->down->name, name))
            {
                temp_to_del = temp_d->down;
                temp_d->down = temp_d->down->down;
                delete(temp_to_del);
                temp->common_friend_counter -= 2;///
                break;
            }
            temp_d = temp_d->down;
        }
        temp = temp->next;
    }
}
bool remove_user(char name[])
{
    users *temp = head, *temp1, *to_be_removed;

    if(!strcmp(temp->name, name))
    {
        head = head->next;
        delete(temp);
        return true;
    }
    else
    {
        while(temp->next != NULL && strcmp(temp->next->name, name))
            temp = temp->next;

        if(temp->next != NULL)
        {
            temp1 = temp->next;
            temp->next = temp->next->next;
            delete(temp1);
            return true;
        }
        else
            return false;
    }
}
int total_users()
{
    int total_no = 0;
    users *temp = head;
    while(temp != NULL)
    {
        total_no++;
        temp = temp->next;
    }
    return total_no;
}
/**void get_users()
{
    if(head == NULL)
    {
        printf("\n\t< The user list is Empty >\n\t   < Add user First >\n");
        return;
    }
    users *temp = head;
    int i = 1;
    printf("\n ~ The list of all users :");
    printf("\n\t\t______________\n\t\t| All Users  |\n\t\t|____________|\n");
    while(temp != NULL)
    {
        printf("\t     %d. %s\n", i++, temp->name);
        temp = temp->next;
    }
    printf("\n");
}*/
void get_users()
{
    if(head == NULL)
    {
        printf("\n< The user list is Empty >\n   < Add user First >\n");
        return;
    }
    users *temp = head, *temp_D;
    int i = 1;
    printf("\n\tUsers\t\t   Friends\n");
    while(temp != NULL)
    {
        temp_D = temp->down;
        printf("      %d.  %s\t\t   ", i++, temp->name);
        while(temp_D != NULL)
        {
            printf("%s", temp_D->name);
            if(temp_D->down != NULL)
                printf(", ");
            temp_D = temp_D->down;
        }
        printf("\n");
        temp = temp->next;
    }
    printf("\n");
}
void user_with_most_friends()
{
    if(head == NULL)
    {
        printf("\n< The user list is Empty >\n   < Add user First >\n");
        return;
    }
    users *temp = head, *temp2, *max_friend;
    int c = 0, max_no = 0;
    while(temp != NULL)
    {
        temp2 = temp->down;
        while(temp2 != NULL)
        {
            c++;
            temp2 = temp2->down;
        }
        if(c > max_no)
        {
            max_no = c;
            max_friend = temp;
        }
        c = 0;
        temp = temp->next;
    }
    printf("\n ~ The user with the most friend is : %s\n", max_friend->name);
}
void user_with_the_oldest_friend()
{
    if(head == NULL)
    {
        printf("\n\t< The user list is Empty >\n\t   < Add user First >\n");
        return;
    }
    users *temp = head, *temp_d, *user_with_oldest_friend;
    int C, oldest_no = 2005;
    while(temp != NULL)
    {
        temp_d = temp->down;
        while(temp_d != NULL)
        {
            if(temp_d->birth_year < oldest_no)
            {
                oldest_no = temp_d->birth_year;
                user_with_oldest_friend = temp;
            }
            temp_d = temp_d->down;
        }
        temp = temp->next;
    }
    printf("\n\n ~ The user with the oldest friend is : %s\n", user_with_oldest_friend->name);

}
void common_friends()
{
    users *temp01 = head;
    int i = 1;
    if(head == NULL)
    {
        printf("\n\t< The user list is Empty >\n\t   < Add user First >\n");
        return;
    }
    printf("\n     List of Common Friends\n");
    while(temp01 != NULL)
    {
        if(temp01->common_friend_counter > 2)
            printf("  %d.  %s\n", i++, temp01->name);

        temp01 = temp01->next;
    }
}
bool add_friend(char user_name[], char friend_name[])
{
    users *temp = head, *temp_u, *temp_f;
    int c = 0;
    while(temp != NULL)
    {
        if(!strcmp(temp->name, user_name))
        {
            temp_u = temp;
            temp->common_friend_counter++;
            c++;
        }
        else if(!strcmp(temp->name, friend_name))
        {
            temp_f = temp;
            temp->common_friend_counter++;
            c++;
        }
        if(c == 2)
            break;

        temp = temp->next;
    }
    if(temp == NULL)
    {
        printf("\n\t\t< Invalid Input!!! >\n   < User name OR Friend name OR Both are wrong >\n");
        return false;
    }

    users *u = temp_u, *temp00;

    while(u->down != NULL)
    {
        if(!strcmp(u->down->name, friend_name))
        {
            printf("\n\t\tFriend Already exist \n");
            return false;
        }
        u = u->down;
    }
    temp00 = new users();
    strcpy(temp00->name, temp_f->name);
    strcpy(temp00->city, temp_f->city);
    temp00->birth_year = temp_f->birth_year;
    temp00->down = NULL;
    u->down = temp00;

    return true;
}
int main()
{
    int choice, total_no_of_users;
    char friend_name[50], user_name[50], user_to_remove[50];
    int r;
    bool c, re;
    while(1)
    {
        printf("________________________\n");
        printf("|      1.Add User      |\n|______________________|\n|     2.Add Friend     |\n|______________________|\n|    3.Total Users     |\n|______________________|\n|      4.Get Users     |\n|______________________|\n");
        printf("|    5.Most Friends    |\n|______________________|\n|    6.Oldest Friend   |\n|______________________|\n|   7.Common Friends   |\n|______________________|\n|     8.Remove User    |\n|______________________|\n|        0.Exit        |\n|______________________|\n");
        printf("\n ~ Please Enter your choice : ");
        scanf("%d", &choice);
        if(choice == 1) /// Add Users  /// DONE
        {
            r = add_user();
            if(r == 1)
                printf("\n ~ User successfully added to Friend-list ~ \n");
            else if(r == 0)
                printf("\n<The user must be at least 13 years old, Can't add >\n");
            else if(r == -1)
                printf("\n< The user is already added to Friend-List, Can't add >\n");

        }
        else if(choice == 2) /// Add Friend  /// DONE
        {
            if(head == NULL || head->next == NULL)
            {
                printf("\n\n< Insufficient members to add as friends >\n\n\t< Add users first >\n\n");
            }
            else
            {
                fflush(stdin);
                printf("\n\n ~ Enter the name of the user   : ");

                gets(user_name);
                printf("\n ~ Enter the name of the friend : ");
                gets(friend_name);
                c = add_friend(user_name, friend_name);
                if(c)
                {
                    add_friend(friend_name, user_name);
                    printf("\n ~ Friend successfully added ~ \n");
                }
            }
        }
        else if(choice == 3) /// Total Users Number
        {
            total_no_of_users = total_users(); /// DONE
            printf(" ~ The total Number of user is : %d\n", total_no_of_users);
        }
        else if(choice == 4) /// Print User names along with their friend's names
        {
            get_users(); /// DONE
        }
        else if(choice == 5) /// User with Most Friends
        {
            user_with_most_friends(); /// DONE
        }
        else if(choice == 6) /// User with the Oldest Friend
        {
            user_with_the_oldest_friend(); /// DONE
        }
        else if(choice == 7) /// List of Common Friends /// DONE
        {
            common_friends();
        }
        else if(choice == 8) /// Remove User /// DONE
        {
            if(head == NULL)
            {
                printf("\n\n< No user to remove >\n\n\n< Add users first >\n");
            }
            else
            {
                printf(" ~ Enter the name of the user to be removed : ");
                fflush(stdin);
                gets(user_to_remove);
                re = remove_user(user_to_remove);

                if(re)
                {
                    printf("\t\"%s\" Successfully removed from Friend-List\n", user_to_remove);
                    remove_from_friend_lists(user_to_remove);
                }
                else
                    printf("\n< There's no user named \"%s\" >\n< Please enter correctly ! >\n", user_to_remove);

            }
        }
        else if(choice == 0)
            break;
        else
        {
            fflush(stdin);
            printf("< Invalid Input >\n< Please enter correctly >\n");
        }
    }
    printf(" ~ Program Terminated ~ \n");
    return 0;
}
