#include <minishell.h>

 bool check_PARENTHESES(char *line)
 {
    int  flag;
    int i ;

    i = 0;
    flag = 0;
    
    while (line[i])
    {
        if (line[i] == '(')
            flag++;
        else if (line[i] == ')')
            flag--;
        if (flag < 0)
        {
            printf(RED"ERROR PARANTES");
            return(false);
        }
        i++;
    }
    return(true);
 }


//  bool check_SORTIE_and_ENTREE(char *line)
//  {
//     int  count_left;
//     int  count_right;
//     int i ;

//     i = 0;
//     count_left = 0;
//     count_right = 0;
    
//     while (line[i])
//     {
//         if (line[i] == '>')
//             count_right++;
//         else if (line[i] == '<')
//             count_left++;
//         i++;
//     }
//     if (count_left != count_right)
//     {
//         printf(RED"ERROR entre");void freeList(t_token *head) 
// {
//     t_token *current = head;
//     t_token *next;

//     while (current != NULL) {
//         next = current->next;
//         free(current->type); 
//         free(current);
//         current = next;
//     }
// }
//         return(false);
//     }
//     return(true);
//  }

 bool check_DOUBLE_QUOTATION(char *line)
 {
    int  count;
    int i ;

    i = 0;
    count = 0;

    
    while (line[i])
    {
        if (line[i] == '"')
            count++;
        i++;
    }
    if (count % 2 != 0)
    {
        printf(RED"ERROR DOUBLE_QUOTATION");
        return(false);
    }
    return(true);
 }

 bool check_SINGLE_QUOTATION(char *line)
 {
    int  count;
    int i ;

    i = 0;
    count = 0;

    
    while (line[i])
    {
        if (line[i] == '\'')
            count++;
        i++;
    }
    if (count % 2 != 0)
    {
        printf(RED"ERROR single_QUOTATION");
        return(false);
    }
    return(true);
 }
bool chech_Quoting(char *line)
{
    if (check_PARENTHESES(line) == false )
        return false;
    if (check_DOUBLE_QUOTATION(line) == false || check_SINGLE_QUOTATION(line))
        return false;
    return true;
}


 