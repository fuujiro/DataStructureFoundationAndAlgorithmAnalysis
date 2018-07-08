#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>

using namespace std;

const int INF = 1000000000;
const int maxBit = 1 << 5;
const int maxNode = 1 << 10;
const int maxCode = 1 << 10;

// �ڵ���Ϣ�ṹ
struct Node {
    // ֵ
    string value;
    // Ȩֵ
    float weight;
    // ���ڵ�
    int parent;
    // ���ӽڵ�
    int lchild;
    // ���ӽڵ�
    int rchild;
};

// ������Ϣ�ṹ
struct Code {
    // �����ַ�
    int bit[maxBit];
    // ��ʼλ��
    int start;
    // ֵ
    string value;
};

// �ڵ�����
Node huffman[maxNode];
// ��������
Code huffmanCode[maxCode];

// n���ַ���
int n;

// ��ʼ��Huffman��
void initHuffmanTree() {
    for(int i = 0; i < (2 * n) - 1; i++) {
        huffman[i].weight = 0;
        huffman[i].value = "";
        huffman[i].parent = -1;
        huffman[i].lchild = -1;
        huffman[i].rchild = -1;
    }
}


// ̰�ķ�
// ����Huffman��
void huffmanTree() {
    // ѭ������Huffman��
    for(int i = 0; i < n - 1; i++) {
        // m1,m2������нڵ���Ȩֵ��С�������ڵ�Ȩֵ
        int m1 = INF;
        int m2 = INF;
        // x1,x2������нڵ���Ȩֵ��С�������ڵ��±�
        int x1 = 0;
        int x2 = 0;
        for(int j = 0; j < n + i; j++) {
            if(huffman[j].weight < m1 && huffman[j].parent == -1) {
                m2 = m1;
                x2 = x1;
                m1 = huffman[j].weight;
                x1 = j;
            } else if(huffman[j].weight < m2 && huffman[j].parent == -1) {
                m2 = huffman[j].weight;
                x2 = j;
            }
        }
        // �����ҵ��������ڵ��x1,x2�ĸ��ڵ���Ϣ
        huffman[x1].parent = n + i;
        huffman[x2].parent = n + i;
        huffman[n + i].weight = huffman[x1].weight + huffman[x2].weight;
        huffman[n + i].lchild = x1;
        huffman[n + i].rchild = x2;
    }
}

// huffman����
void huffmanEncoding() {
    // ��ʱ�ṹ
    Code cd;
    int child, parent;
    for(int i = 0; i < n; i++) {
        cd.value = huffman[i].value;
        cd.start = n - 1;
        child = i;
        parent = huffman[child].parent;
        // δ�����ڵ�
        while(parent != -1) {
            // ����
            if(huffman[parent].lchild == child) {
                cd.bit[cd.start] = 0;
            } else {
                // �Һ���
                cd.bit[cd.start] = 1;
            }
            cd.start--;
            // ������һѭ������
            child = parent;
            parent = huffman[child].parent;
        }

        // ���������ÿ��Ҷ�ӽڵ��Huffman����ṹ
        for(int j = cd.start + 1; j < n; j++) {
            huffmanCode[i].bit[j] = cd.bit[j];
        }
        huffmanCode[i].start = cd.start;
        huffmanCode[i].value = cd.value;
    }
}

// ��ӡÿ��Ҷ�ڵ��Huffman����ͱ�����ʼֵ
void printHuffmanCode() {
    for(int i = 0; i < n; i++) {
        cout << "��" << i + 1 << "���ַ� " << huffmanCode[i].value << " ��Huffman����Ϊ��";
        for(int j = huffmanCode[i].start + 1; j < n; j++) {
            cout << huffmanCode[i].bit[j];
        }
        cout << " ������ʼֵΪ��" << huffmanCode[i].start << endl;
    }
    cout << endl;
}

// ����Huffman����
void HuffmanDecoding(string s) {
    vector<string> v;
    // ��ʶλ
    int ok = 1;
    for(int i = 0; i < s.length();) {
        // ���ڵ�
        int x = (2 * n) - 1 - 1;
        // ��ΪҶ�ӽڵ�
        while(huffman[x].lchild != -1 && huffman[x].rchild != -1) {
            // ������
            if(s[i] == '0') {
                x = huffman[x].lchild;
            } else {
                // ������
                x = huffman[x].rchild;
            }
            i++;
            // ����0,1��������
            // �������һ���ǽ�β0,1�������ˣ��������һ���ַ�������ʧ��
            if(i == s.length() && huffman[x].lchild != -1) {
                ok = 0;
                break;
            }
        }

        if(ok) {
            v.push_back(huffman[x].value);
        }
    }
    if(ok) {
        for(int i = 0; i < v.size(); i++) {
            cout << v[i];
        }
        cout << endl << endl;
    } else {
        cout << "��������" << endl << endl;
    }
}

int main()
{
    while(true){
        system("color E9");
        char choice;
        system("cls");
        printf("--��������������--\n");
        printf("1. ����\n");
        printf("2. ����\n");
        printf("3. �˳�\n");
        printf("����������: ");
        printf("\n");
        printf("����ѡ��(1-5):");
        choice = getch();
        while(choice!='1'&&choice!='2'&&choice!='3')
            choice = getch();
        printf("%c\n",choice);
        fflush(stdin);

        if(choice=='1') /*����*/ 
        {
            system("cls");
            system("color BC");
            cout << "�������ַ�������(0: �˳�)��";
            cin >> n;
            if(n){
                char stop;
                // ��ʼ��Huffman��
                initHuffmanTree();

                for(int i = 0; i < n; i++) {
                    cout << "һ��" << n << "���ַ������������" << i + 1 << "���ַ�������Ȩֵ��";
                    cin >> huffman[i].value;
                    cin >> huffman[i].weight;
                }

                // ����Huffman��
                huffmanTree();

                // huffman����
                huffmanEncoding();

                // ��ӡÿ��Ҷ�ڵ��Huffman����ͱ�����ʼֵ
                printHuffmanCode();
                
                printf("��������������˵�>>>");
                fflush(stdin);
                stop = getchar();
            }
        }

        if(choice=='2') /*����*/ 
        {
            system("cls");
            system("color 3D");
            while(true){
                cout << "������һ�η������������0,1����(����q���˳�)��";
                string s;
                cin >> s;
                if(s[0] == 'q') {
                    cout << endl;
                    break;
                }
                cout << "ԭʼ0,1����Ϊ��" << s << endl;
                cout << "�����Ϊ��";
                // ����
                HuffmanDecoding(s);
            }
        }

        if(choice=='3') /*�˳�*/ 
        {
            printf("\n��ӭ�ٴ�ʹ��");
            int c = getchar();
            return 0;
        }
    }
    
}

