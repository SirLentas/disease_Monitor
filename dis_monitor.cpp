#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "hash_t.h"

using namespace std;

long int datetoint(char *s)
{
    int inDate;
    char *temp;
    int doubl = 0;
    temp = strtok(s, "-");
    inDate = atoi(temp);
    temp = strtok(NULL, "-");
    inDate = inDate + 31 * atoi(temp);
    temp = strtok(NULL, "\0");

    inDate = inDate + 31 * 12 * atoi(temp);

    return inDate;
}

int main(int argc, char *argv[])
{
    int ok = 0;
    FILE *infile;
    int dsize;
    int csize;
    int max;
    if (argc != 9)
    {
        cout << "./diseaseMonitor -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize" << endl;
        return -3;
    }
    for (int c = 1; c < 9; c++)
    {
        if (strcmp(argv[c], "-p") == 0)
        {
            infile = fopen(argv[c + 1], "r");
            ok++;
        }
        else if (strcmp(argv[c], "-h1") == 0)
        {
            dsize = atoi(argv[c + 1]);
            ok++;
        }
        else if (strcmp(argv[c], "-h2") == 0)
        {
            csize = atoi(argv[c + 1]);
            ok++;
        }
        else if (strcmp(argv[c], "-b") == 0)
        {
            max = atoi(argv[c + 1]);
            ok++;
        }
    }
    if (ok < 4)
    {
        return -4;
    }
    int ch;

    max = max - sizeof(pNode *) - sizeof(int);
    max = max / sizeof(AVL *);
    cout << "Bucket capacity: " << max << endl;

    List Data_list;
    HashChain DisHash[dsize];
    HashChain CntHash[csize];

    for (int i = 0; i < dsize; i++)
    {
        DisHash[i].max = max;
    }

    for (int i = 0; i < csize; i++)
    {
        CntHash[i].max = max;
    }

    char *key;
    char *fn;
    char *ln;
    char *dis;
    char *cntr;
    char *postal;
    char *temp;
    char *temp2;
    int inDate = 0;
    int outDate = 0;

    DataNode *aa;

    char line[120];

    while (fgets(line, sizeof(line), infile))
    {
        key = strtok(line, " ");
        fn = strtok(NULL, " ");
        ln = strtok(NULL, " ");
        dis = strtok(NULL, " ");
        cntr = strtok(NULL, " ");
        temp = strtok(NULL, "-");
        inDate = atoi(temp);
        temp = strtok(NULL, "-");
        inDate = inDate + 31 * atoi(temp);
        temp = strtok(NULL, " ");
        inDate = inDate + 31 * 12 * atoi(temp);
        temp = strtok(NULL, "\n");
        if (strcmp(temp, "-") == 0)
        {
            outDate = 800000;
        }
        else
        {
            temp2 = strtok(temp, "-");
            outDate = atoi(temp2);
            temp2 = strtok(NULL, "-");
            outDate = outDate + 31 * atoi(temp2);
            temp2 = strtok(NULL, " ");
            outDate = outDate + 31 * 12 * atoi(temp2);
            if (inDate > outDate)
            {
                // cout << "Exit day before entry" << endl;
                cout << "error" << endl;
                return -1;
            }
        }

        if (Data_list.searchKey(key))
        {
            // cout << "Duplicate ID" << endl;
            cout << "error" << endl;
            return -2;
        }
        aa = Data_list.add_node(key, fn, ln, dis, cntr, inDate, outDate);

        if (DisHash[hashFunction(aa->dis, dsize)].findKey(aa, 1) == 0)
        {
            DisHash[hashFunction(aa->dis, dsize)].add_node(aa);
        }
        if (CntHash[hashFunction(aa->cntr, csize)].findKey(aa, 0) == 0)
            CntHash[hashFunction(aa->cntr, csize)].add_node(aa);
    }

    pNode *ttr;
    AVL *ax;
    long int in, out;

    bool done = false;
    char command[120];
    char *c1;
    char *c2;
    char *c3;
    char *c4;
    char *c5;
    char *c6;
    char *c7;
    char *c8;

    while (done == false)
    {
        //cout << "TYPE YOUR COMMAND (TYPE help FOR MENU)\n> ";
        fgets(command, 120, stdin);
        //printf("\nCOMMAND > %s\n", command);
        c1 = strtok(command, "  \n\0");
        if (strcmp(c1, "/globalDiseaseStats") == 0)
        {
            c2 = strtok(NULL, " \0");
            c3 = strtok(NULL, " \0");
            if (c2 == NULL)
            {
                for (int i = 0; i < dsize; i++)
                {
                    ttr = DisHash[i].head;
                    while (ttr != NULL)
                    {
                        for (int j = 0; j < DisHash[0].max; j++)
                        {
                            if (ttr->treeHead[j] != NULL)
                            {
                                ax = DisHash[hashFunction(ttr->treeHead[j]->Data_ptr->dis, dsize)].ret_root(ttr->treeHead[j]->Data_ptr->dis);
                                // cout << "Patients with " << ttr->treeHead[j]->Data_ptr->dis << " virus : " << count(ax, 0, 800000) << endl;
                                cout << ttr->treeHead[j]->Data_ptr->dis << " " << count(ax, 0, 800000) << endl;
                            }
                        }
                        ttr = ttr->pNext;
                    }
                }
            }
            else
            {

                if (c3 == NULL)
                {
                    cout << "error" << endl;
                }
                else
                {
                    in = datetoint(c2);
                    out = datetoint(c3);
                    for (int i = 0; i < dsize; i++)
                    {
                        ttr = DisHash[i].head;
                        while (ttr != NULL)
                        {
                            for (int j = 0; j < DisHash[0].max; j++)
                            {
                                if (ttr->treeHead[j] != NULL)
                                {

                                    ax = DisHash[hashFunction(ttr->treeHead[j]->Data_ptr->dis, dsize)].ret_root(ttr->treeHead[j]->Data_ptr->dis);
                                    // cout << "Patients with " << ttr->treeHead[j]->Data_ptr->dis << " virus : " << count(ax, in, out) << endl;
                                    cout << ttr->treeHead[j]->Data_ptr->dis << " " << count(ax, in, out) << endl;
                                }
                            }
                            ttr = ttr->pNext;
                        }
                    }
                }
            }
        }
        else if (strcmp(c1, "/diseaseFrequency") == 0)
        {
            c2 = strtok(NULL, " \0");
            c3 = strtok(NULL, " \0");
            c4 = strtok(NULL, " \0");
            c5 = strtok(NULL, " \n\0");

            if (c5 == NULL)
            {
                // cout << "Patients with " << c2 << " virus between " << c3 << " and " << c4 << " : ";

                in = datetoint(c3);
                out = datetoint(c4);

                ax = DisHash[hashFunction(c2, dsize)].ret_root(c2);

                cout << c2 << " " << count(ax, in, out) << endl;
            }
            else
            {
                // cout << "Patients with " << c2 << " virus in "<<c5<<" between " << c3 << " and " << c4 << " : ";
                in = datetoint(c3);
                out = datetoint(c4);

                ax = DisHash[hashFunction(c2, dsize)].ret_root(c2);

                cout << c2 << " " << dis_f(ax, c5, in, out) << endl;
            }
        }
        else if (strcmp(c1, "/topk-Diseases") == 0)
        {
            c2 = strtok(NULL, "  ");
            c3 = strtok(NULL, "  \n\0");
            c4 = strtok(NULL, "  \0\n");
            c5 = strtok(NULL, "  \0\n");
            if (c4 == NULL)
            {
                ax = CntHash[hashFunction(c3, csize)].ret_root(c3);
                //cout << endl << "Top " << atoi(c2) << " Diseases in "<<c3<< endl;
                create_m_h(ax, atoi(c2), 0, 800000);
            }
            else
            {
                if (c5 == NULL)
                {
                    cout << "No exit given" << endl;
                }
                else
                {
                    //cout << endl << "Top " << atoi(c2) << " Diseases in "<<c3<<" between " << c4 << " and " << c5 << endl;
                    in = datetoint(c4);
                    out = datetoint(c5);
                    ax = CntHash[hashFunction(c3, csize)].ret_root(c3);
                    create_m_h(ax, atoi(c2), in, out);
                }
            }
        }
        else if (strcmp(c1, "/topk-Countries") == 0)
        {
            c2 = strtok(NULL, "  ");
            c3 = strtok(NULL, "  \n\0");
            c4 = strtok(NULL, "  \0\n");
            c5 = strtok(NULL, "  \0\n");
            if (c4 == NULL)
            {
                ax = DisHash[hashFunction(c3, dsize)].ret_root(c3);
                //cout << endl << "Top " << atoi(c2) << " Countries with "<<c3<<" patients" << endl;
                create_m_h_d(ax, atoi(c2), 0, 800000);
            }
            else
            {
                if (c5 == NULL)
                {
                    cout << "No exit given" << endl;
                }
                else
                {
                    //cout << endl << "Top " << atoi(c2) << " Countries with "<<c3<<" patientsbetween " << c4 << " and " << c5 << endl;
                    in = datetoint(c4);
                    out = datetoint(c5);
                    ax = DisHash[hashFunction(c3, dsize)].ret_root(c3);
                    create_m_h_d(ax, atoi(c2), in, out);
                }
            }
        }
        else if (strcmp(c1, "/insertPatientRecord") == 0)
        {
            c2 = strtok(NULL, "  ");
            c3 = strtok(NULL, "  ");
            c4 = strtok(NULL, "  ");
            c5 = strtok(NULL, "  ");
            c6 = strtok(NULL, "  ");
            c7 = strtok(NULL, "  \n\0");
            c8 = strtok(NULL, "  \n\0");
            if(c8==NULL){
                 out = 800000;
            }
            else if (strcmp(c8, "-") == 0)
            {
                out = 800000;
            }
            else
            {
                out = datetoint(c8);
            }
            in = datetoint(c7);

            if (Data_list.searchKey(c2))
            {
                cout << "Duplicate ID: Insertion Cancelled" << endl;
            }
            else
            {
                aa = Data_list.add_node(c2, c3, c4, c5, c6, in, out);

                if (DisHash[hashFunction(aa->dis, dsize)].findKey(aa, 1) == 0)
                    DisHash[hashFunction(aa->dis, dsize)].add_node(aa);
                if (CntHash[hashFunction(aa->cntr, csize)].findKey(aa, 0) == 0)
                    CntHash[hashFunction(aa->cntr, csize)].add_node(aa);

                cout << "Record added" << endl;
            }
        }
        else if (strcmp(c1, "/recordPatientExit") == 0)
        {
            c2 = strtok(NULL, "  ");
            c3 = strtok(NULL, "  \n\0");
            //scout << c1 << " " << c2 << " " << c3 << endl;
            out = datetoint(c3);
            Data_list.changeED(c2, out);
            //cout << "Record updated" << endl;
        }
        else if (strcmp(c1, "/numCurrentPatients") == 0)
        {
            c2 = strtok(NULL, "  \n\0");
            if (c2 == NULL)
            {
                for (int i = 0; i < dsize; i++)
                {
                    ttr = DisHash[i].head;
                    while (ttr != NULL)
                    {
                        for (int j = 0; j < DisHash[0].max; j++)
                        {
                            if (ttr->treeHead[j] != NULL)
                            {

                                ax = DisHash[hashFunction(ttr->treeHead[j]->Data_ptr->dis, dsize)].ret_root(ttr->treeHead[j]->Data_ptr->dis);
                                cout << ttr->treeHead[j]->Data_ptr->dis << " " << count_cur(ax) << endl;
                            }
                        }
                        ttr = ttr->pNext;
                    }
                }
            }
            else
            {
                ax = DisHash[hashFunction(c2, dsize)].ret_root(c2);
                if (ax == NULL)
                {
                    cout << c2 << " 0" << endl;
                }
                else
                {

                    ax = DisHash[hashFunction(ax->Data_ptr->dis, dsize)].ret_root(ax->Data_ptr->dis);
                    cout << c2 << " " << count_cur(ax) << endl;
                }
            }
        }
        else if (strcmp(c1, "/printDiseasesHashTable") == 0)
        {
            for (int i = 0; i < dsize; i++)
            {
                cout << "Disease Hash position [" << i << "]" << endl;
                ttr = DisHash[i].head;
                while (ttr != NULL)
                {
                    cout << "   |" << endl;
                    cout << "   v" << endl;
                    for (int j = 0; j < DisHash[0].max; j++)
                    {
                        if (ttr->treeHead[j] != NULL)
                            InOrder(ttr->treeHead[j]);
                        cout << endl;
                    }
                    ttr = ttr->pNext;
                }
            }
        }
        else if (strcmp(c1, "/printCountriesHashTable") == 0)
        {
            for (int i = 0; i < csize; i++)
            {
                cout << "Country Hash position [" << i << "]" << endl;
                ttr = CntHash[i].head;
                while (ttr != NULL)
                {
                    cout << "   |" << endl;
                    cout << "   v" << endl;
                    for (int j = 0; j < CntHash[0].max; j++)
                    {
                        if (ttr->treeHead[j] != NULL)
                            InOrder(ttr->treeHead[j]);
                        cout << endl;
                    }
                    ttr = ttr->pNext;
                }
            }
        }
        else if (strcmp(c1, "/exit") == 0)
        {
            cout << "exiting" << endl;
            done = true;
        }
        else if (strcmp(c1, "help") == 0)
        {
            cout << "------------------------------------------------" << endl
                 << "/globalDiseaseStats [date1 date2]" << endl
                 << "/diseaseFrequency virusName date1 date2 [country]" << endl
                 << "/topk-Diseases k country [date1 date2]" << endl
                 << "/topk-Countries k disease [date1 date2]" << endl
                 << "/insertPatientRecord recordID patientFirstName patientLastName diseaseID country entryDate [exitDate]" << endl
                 << "/recordPatientExit recordID exitDate" << endl
                 << "/numCurrentPatients [disease]" << endl
                 << "/printDiseasesHashTable" << endl
                 << "/printCountriesHashTable" << endl
                 << "/exit" << endl
                 << "------------------------------------------------" << endl;
        }
        else
        {
            cout << "error" << endl;
        }
    }
}