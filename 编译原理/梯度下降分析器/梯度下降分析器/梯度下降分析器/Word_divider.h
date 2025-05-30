#pragma once

#include<iostream>
#include<vector>
#include<string>
using namespace std;


vector<string> Reserved = { "restrict", "struct", "union", "enum", "typedef", "sizeof", "auto", "static", "register", "extern", "const",
        "volatitle", "break", "goto", "else", "switch", "case", "default", "continue", "do", "double", "float","int" };// �����ֱ�


void Word_divier(const string str,vector<string> &result)
{

    //init();


    //vector <string> result;//��¼���

    //��ʼ�������Ĵ���
    int length_str = str.length();
    string word;
    for (int i = 0; i < length_str; i++)
    {
        //�������ո����ʱ����������ִ��
        if (str[i] == ' ' || str[i] == '\n') continue;
        //ʶ����
        else if (isdigit(str[i]))
        {

            //���ַ�����ʽ��ʾ�������
            while (isdigit(str[i]))
            {
                word ="num";
                i++;
            }
            i--;
        }
        //ʶ������ֻ��ʶ��
        else if (isalpha(str[i]))
        {

            //���ַ�����ʽ��ʾ��������ֻ��߱�ʶ��
            while (isdigit(str[i]) || isalpha(str[i]))
            {
                word += str[i];
                i++;
            }
            i--;
            vector<string>::iterator it = find(Reserved.begin(), Reserved.end(), word);
            if (it == Reserved.end()) {
                word = "id";
            }

        }
        //ʶ�������
        else
        {

            switch (str[i])
            {

            case '+':
            {
                
                word = "+";
                break;
            }
            case '-':
            {
                
                word = "-";
                break;
            }
            case '*':
            {
               
                word = "*";
                break;
            }
            case '/': {

                word = "/";
                break;
            }
            case '=': {

                word = "=";
                break;
            }
            case '<': {
                i++;
                if (str[i] == '>')
                {

                    word = "<>";

                }
                else if (str[i] == '=')
                {

                    word = "<=";

                }
                else if (str[i] == '<')
                {
            
                    word = "<<";
                }
                else
                {
                    i--;
                  
                    word = "<";
                }
                break;
            }
            case '>': {
                i++;
                if (str[i] == '=')
                {
                
                    word = ">=";
                }
                else if (str[i] == '>') {
                  
                    word = ">>";
                }
                else

                {
                    i--;
                    
                    word = ">";
                }
                break;
            }
            case ':':
            {
       
                word = ":";
                break;
            }
            //�ָ���
            case '(':
            {
             
                word = "(";
                break;
            }
            case ')':
            {
             
                word = ")";
                break;
            }
            case ',':
            {
             
                word = ",";
                break;
            }
            case ';':
            {
            
                word = ";";
                break;
            }
            case '{':
            {
             
                word = "{";
                break;
            }
            case '}':
            {
             
                word = "}";
                break;
            }
            case '[':
            {
            
                word = "[";
                break;
            }
            case ']':
            {
            
                word = "]";
                break;
            }
           
            
            //������
            default:

                break;
            }
 
        }
        if (word != "") {

            result.push_back(word);

            word = "";
        }

    }

}