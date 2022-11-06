// sparse with linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    int row;
    int column;
    struct Node *next;
} * node;

node head = NULL;

node sparse(node head, int value, int m, int n)
{
    node ptr = malloc(sizeof(struct Node)), prev=head;
    if (head == NULL)
    {
        ptr->data = value;
        ptr->row = m;
        ptr->column = n;
        ptr->next = NULL;
        head = ptr;
        prev = head;
    }
    else
    {
        ptr->data = value;
        ptr->row = m;
        ptr->column = n;
        while(prev->next!=NULL)
        {
            prev=prev->next;
        }
        prev->next = ptr;
        ptr->next = NULL;
    }
    return head;
}

node insert(node start, int value, int row, int column)
{
    node ptr = malloc(sizeof(struct Node)), temp = start;
    if (start == NULL)
    {
        ptr->row = row;
        ptr->column = column;
        ptr->data = value;
        ptr->next = NULL;
        start = ptr;
    }
    else
    {
        ptr->row = row;
        ptr->column = column;
        ptr->data = value;
        ptr->next = NULL;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = ptr;
    }
    return start;
}

node addition(node head1, node head2)
{
    node add = NULL, temp1 = head1, temp2 = head2;
    while (temp1 && temp2)
    {
        if ((temp1->row == temp2->row) && (temp1->column == temp2->column))
        {
            add = insert(add, temp1->data + temp2->data, temp1->row, temp2->column);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->row == temp2->row)
        {
            if (temp1->column < temp2->column)
            {
                add = insert(add, temp1->data, temp1->row, temp1->column);
                temp1 = temp1->next;
                add = insert(add, temp2->data, temp2->row, temp2->column);
                temp2 = temp2->next;
            }
            else
            {
                add = insert(add, temp2->data, temp2->row, temp2->column);
                temp2 = temp2->next;
                add = insert(add, temp1->data, temp1->row, temp1->column);
                temp1 = temp1->next;
            }
        }
        else
        {
            if (temp1->row < temp2->row)
            {
                add = insert(add, temp1->data, temp1->row, temp1->column);
                temp1 = temp1->next;
                add = insert(add, temp2->data, temp2->row, temp2->column);
                temp2 = temp2->next;
            }
            else
            {
                add = insert(add, temp2->data, temp2->row, temp2->column);
                temp2 = temp2->next;
                add = insert(add, temp1->data, temp1->row, temp1->column);
                temp1 = temp1->next;
            }
        }
    }
    for (; temp1 != NULL; temp1 = temp1->next)
    {
        add = insert(add, temp1->data, temp1->row, temp1->column);
    }
    for (; temp2 != NULL; temp2 = temp2->next)
    {
        add = insert(add, temp2->data, temp2->row, temp2->column);
    }
    return add;
}

void display(node start)
{
    node ptr = start;
    while (ptr != NULL)
    {
        printf("%d\t%d\t%d\n", ptr->row, ptr->column, ptr->data);
        ptr = ptr->next;
    }
}

node multiply(node head1,node head2)
{
    head2=transpose(head2);
    node temp1=head1,temp2=head2,mul;
    while(temp1&&temp2)
    {
        
        mul=insert(mul,,temp1->row,temp2->row);
    }
}

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

node transpose(node start)
{
    node ptr=start;
    int t,i=0;
    while(ptr!=NULL)
    {
        swap(ptr->column,ptr->row);
        ptr=ptr->next;
        i++;
    }
    start=sort(start,i);
}

node sort(node start,int total)
{
    node ptr=start,temp;
    for(int i=0;i<total;i++)
    {
        if(ptr->row>ptr->next->row)
        {
            if(ptr==start)
            {
                start=ptr->next;
            }
            temp=ptr->next->next;
            ptr->next->next=ptr;
            ptr->next=temp;
        }
        ptr=ptr->next;
    }
    return start;
}

int main()
{
    int m, n;
    node head1=NULL, head2=NULL;
    printf("Enter Rows And Columns: ");
    scanf("%d%d", &m, &n);
    int a[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter %d,%d Element: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
            {
                head1 = sparse(head1, a[i][j], i, j);
            }
        }
    }
    head = NULL;
    display(head1);
    printf("Enter Rows And Columns: ");
    scanf("%d%d", &m, &n);
    int d[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter %d,%d Element: ", i, j);
            scanf("%d", &d[i][j]);
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (d[i][j] != 0)
            {
                head2 = sparse(head2, d[i][j], i, j);
            }
        }
    }
    head = NULL;
    display(head2);
    printf("\nAddition:\n");
    node add;
    add = addition(head1, head2);
    display(add);
    printf("\nMultiplication:\n");
    node mul=NULL;
    mul=multiply(head1,head2);
    display(mul);
    return 0;
}